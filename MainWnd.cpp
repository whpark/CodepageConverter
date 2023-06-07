﻿#include "pch.h"
#include "wxDesktopApp.h"
#include "wx/msw/private.h"
#include "MainWnd.h"

#include "gtl/string/convert_codepage.h"
#include "gtl/archive.h"

template < bool bCaseSensitive = false >
bool FilterFileMultiFilter(std::wstring_view pszFilters, std::wstring_view pszName, std::wstring_view szSpliter);

xMainWnd::xMainWnd( wxWindow* parent ) : ui::IMainWnd( parent ) {
	wxIcon icon;
	icon.SetHandle(::LoadIcon(wxGetInstance(), MAKEINTRESOURCEW(IDI_CODEPAGE_CONVERTER)));
	this->SetIcon(icon);
	// Get last Folder from reg
	auto& app = wxGetApp();
	wxString strFolder;
	wxRegKey reg(app.m_reg, L"misc");
	if (reg.Exists() and reg.QueryValue(L"LastFolder", strFolder)) try {
		m_browser->SetPath(strFolder);
		m_dir->ExpandPath(strFolder);
	}
	catch (...) {}

	// style for wxStyledTextCtrl
	m_code->StyleClearAll();
	m_code->SetLexer(wxSTC_LEX_CPP);

	//enum { MARGIN_LINE_NUMBERS, MARGIN_FOLD };
	//m_code->SetMarginWidth(MARGIN_LINE_NUMBERS, 50);
	//m_code->StyleSetForeground (wxSTC_STYLE_LINENUMBER, wxColour (75, 75, 75) );
	//m_code->StyleSetBackground (wxSTC_STYLE_LINENUMBER, wxColour (220, 220, 220));
	//m_code->SetMarginType (MARGIN_LINE_NUMBERS, wxSTC_MARGIN_NUMBER);

	//// ---- Enable code folding
	//m_code->SetMarginType (MARGIN_FOLD, wxSTC_MARGIN_SYMBOL);
	//m_code->SetMarginWidth(MARGIN_FOLD, 15);
	//m_code->SetMarginMask (MARGIN_FOLD, wxSTC_MASK_FOLDERS);
	//m_code->StyleSetBackground(MARGIN_FOLD, wxColor(200, 200, 200) );
	//m_code->SetMarginSensitive(MARGIN_FOLD, true);

	//// Properties found from http://www.scintilla.org/SciTEDoc.html
	//m_code->SetProperty (wxT("fold"),         wxT("1") );
	//m_code->SetProperty (wxT("fold.comment"), wxT("1") );
	//m_code->SetProperty (wxT("fold.compact"), wxT("1") );

	//wxColor grey( 100, 100, 100 );
	//m_code->MarkerDefine (wxSTC_MARKNUM_FOLDER, wxSTC_MARK_ARROW );
	//m_code->MarkerSetForeground (wxSTC_MARKNUM_FOLDER, grey);
	//m_code->MarkerSetBackground (wxSTC_MARKNUM_FOLDER, grey);

	//m_code->MarkerDefine (wxSTC_MARKNUM_FOLDEROPEN,    wxSTC_MARK_ARROWDOWN);
	//m_code->MarkerSetForeground (wxSTC_MARKNUM_FOLDEROPEN, grey);
	//m_code->MarkerSetBackground (wxSTC_MARKNUM_FOLDEROPEN, grey);

	//m_code->MarkerDefine (wxSTC_MARKNUM_FOLDERSUB,     wxSTC_MARK_EMPTY);
	//m_code->MarkerSetForeground (wxSTC_MARKNUM_FOLDERSUB, grey);
	//m_code->MarkerSetBackground (wxSTC_MARKNUM_FOLDERSUB, grey);

	//m_code->MarkerDefine (wxSTC_MARKNUM_FOLDEREND,     wxSTC_MARK_ARROW);
	//m_code->MarkerSetForeground (wxSTC_MARKNUM_FOLDEREND, grey);
	//m_code->MarkerSetBackground (wxSTC_MARKNUM_FOLDEREND, _T("WHITE"));

	//m_code->MarkerDefine (wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_ARROWDOWN);
	//m_code->MarkerSetForeground (wxSTC_MARKNUM_FOLDEROPENMID, grey);
	//m_code->MarkerSetBackground (wxSTC_MARKNUM_FOLDEROPENMID, _T("WHITE"));

	//m_code->MarkerDefine (wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_EMPTY);
	//m_code->MarkerSetForeground (wxSTC_MARKNUM_FOLDERMIDTAIL, grey);
	//m_code->MarkerSetBackground (wxSTC_MARKNUM_FOLDERMIDTAIL, grey);

	//m_code->MarkerDefine (wxSTC_MARKNUM_FOLDERTAIL,    wxSTC_MARK_EMPTY);
	//m_code->MarkerSetForeground (wxSTC_MARKNUM_FOLDERTAIL, grey);
	//m_code->MarkerSetBackground (wxSTC_MARKNUM_FOLDERTAIL, grey);
	//// ---- End of code folding part

	m_code->SetWrapMode (wxSTC_WRAP_WORD); // other choice is wxSCI_WRAP_NONE

	m_code->StyleSetForeground (wxSTC_C_STRING,            wxColour(150,0,0));
	m_code->StyleSetForeground (wxSTC_C_PREPROCESSOR,      wxColour(165,105,0));
	m_code->StyleSetForeground (wxSTC_C_IDENTIFIER,        wxColour(40,0,60));
	m_code->StyleSetForeground (wxSTC_C_NUMBER,            wxColour(0,150,0));
	m_code->StyleSetForeground (wxSTC_C_CHARACTER,         wxColour(150,0,0));
	m_code->StyleSetForeground (wxSTC_C_WORD,              wxColour(0,0,150));
	m_code->StyleSetForeground (wxSTC_C_WORD2,             wxColour(0,150,0));
	m_code->StyleSetForeground (wxSTC_C_COMMENT,           wxColour(150,150,150));
	m_code->StyleSetForeground (wxSTC_C_COMMENTLINE,       wxColour(150,150,150));
	m_code->StyleSetForeground (wxSTC_C_COMMENTDOC,        wxColour(150,150,150));
	m_code->StyleSetForeground (wxSTC_C_COMMENTDOCKEYWORD, wxColour(0,0,200));
	m_code->StyleSetForeground (wxSTC_C_COMMENTDOCKEYWORDERROR, wxColour(0,0,200));
	m_code->StyleSetBold(wxSTC_C_WORD, true);
	m_code->StyleSetBold(wxSTC_C_WORD2, true);
	m_code->StyleSetBold(wxSTC_C_COMMENTDOCKEYWORD, true);

	// a sample list of keywords, I haven't included them all to keep it short...
	m_code->SetKeyWords(0, wxT("return for while break continue"));
	m_code->SetKeyWords(1, wxT("const int float void char double"));

}

bool xMainWnd::AnalyzePath(wxTreeListCtrl& lst, wxTreeListItem const& parent,
	std::filesystem::path const& path0, xMainWnd::FILTER const& filter)
{
	std::error_code ec;
	//std::vector<int> lines;
	if (ec.clear(); stdfs::is_regular_file(path0, ec)) {
		auto item = lst.AppendItem(parent, path0.filename().wstring());
		if (!item)
			return false;

		auto e = gtl::ReadFileBOM(path0);	// Check BOM
		std::wstring strEncoding;
		std::wstring strComments;
		switch (e) {
			using enum gtl::eFILE_TYPE;
		case utf8: strEncoding = L"UTF-8 BOM"; break;
		case utf16le: strEncoding = L"UTF-16LE BOM"; break;
		case utf16be: strEncoding = L"UTF-16BE BOM"; break;
		case utf32le: strEncoding = L"UTF-32LE BOM"; break;
		case utf32be: strEncoding = L"UTF-32BE BOM"; break;
		case unknown:
		default:
			strEncoding = wxString(gtl::DetectCodepage(path0));
			break;
		}
		lst.SetItemText(item, std::to_underlying(eLST_COL::encoding), strEncoding);
		lst.SetItemText(item, std::to_underlying(eLST_COL::comments), strComments);
	}
	else if (ec.clear(); stdfs::is_directory(path0, ec)) {
		ec.clear();
		for (auto entry : stdfs::directory_iterator(path0, ec)) {
			auto const& path = entry.path();
			if (entry.is_directory()) {
				if (!FilterFileMultiFilter(filter.filtersFolder, path.filename().c_str(), L";"))
					continue;
				if (FilterFileMultiFilter(filter.filtersFolderExclude, path.filename().c_str(), L";"))
					continue;
				auto item = lst.AppendItem(parent, path.filename().wstring());
				AnalyzePath(lst, item, path, filter);
			} else {
				if (!FilterFileMultiFilter(filter.filters, path.filename().c_str(), L";"))
					continue;
				if (FilterFileMultiFilter(filter.filtersExclude, path.filename().c_str(), L";"))
					continue;
				AnalyzePath(lst, parent, path, filter);
			}
		}
		lst.Expand(parent);
	}

	return true;
}

void xMainWnd::SaveCurrentFolderPath(wxString const& strFolder) {
	auto& app = wxGetApp();
	wxRegKey reg(app.m_reg, L"misc");
	reg.Create();
	reg.SetValue(L"LastFolder", strFolder);
}

std::filesystem::path xMainWnd::GetSelectedFilePath(wxTreeListItem item) {
	stdfs::path path;
	stdfs::path folder = m_folderCurrent;
	if (folder.empty() or !std::filesystem::is_directory(folder))
		return path;

	if (!item) {
		wxTreeListItems items;
		m_lst->GetSelections(items);
		if (items.size() != 1)
			return path;
		item = items[0];
	}
	if (!item)
		return path;

	auto strFilename = m_lst->GetItemText(item, std::to_underlying(eLST_COL::filename));
	auto strEncoding = m_lst->GetItemText(item, std::to_underlying(eLST_COL::encoding));
	auto strComments = m_lst->GetItemText(item, std::to_underlying(eLST_COL::comments));
	for (auto parent = m_lst->GetItemParent(item), root = m_lst->GetRootItem(); parent and parent != root; parent = m_lst->GetItemParent(parent)) {
		strFilename = m_lst->GetItemText(parent, std::to_underlying(eLST_COL::filename)) + L'/' + strFilename;
	}

	path = folder / strFilename.ToStdWstring();
	return path;
}

bool xMainWnd::ConvertFileEncoding(std::filesystem::path const& path, int codepage, bool bWriteBOM, bool bBackup, bool bPreserveTimestamps) {
	std::error_code ec;
	auto t0 = std::filesystem::last_write_time(path, ec);
	if (ec)
		return false;
	auto pathD = path;
	pathD.replace_extension(path.extension().wstring() + L"._tmp_");

	switch (codepage) {
	case 65001:
		{
			auto str = ReadFileAs<char8_t>(path, ec);
			if (ec)
				return false;
			gtl::xOFArchive ar(pathD);
			if (bWriteBOM)
				ar.WriteCodepageBOM(gtl::eCODEPAGE::UTF8);
			ar.Write(str.c_str(), str.size());
		}
		break;
	case 1200:
		{
			auto str = ReadFileAs<wchar_t>(path, ec);
			if (ec)
				return false;
			gtl::xOFArchive ar(pathD);
			if (bWriteBOM)
				ar.WriteCodepageBOM(gtl::eCODEPAGE::UCS2);
			ar.Write(str.c_str(), str.size()*sizeof(wchar_t));
		}
		break;
	}
	if (bPreserveTimestamps) {
		std::filesystem::last_write_time(pathD, t0, ec);
		if (ec)
			return false;
	}

	if (bBackup) {
		auto pathD = path;
		pathD.replace_extension(path.extension().wstring() + L"_org");
		for (int i{}; std::filesystem::exists(pathD); i++) {
			pathD.replace_extension(std::format(L"{}_org{}", path.extension().wstring(), i++));
		}
		std::filesystem::rename(path, pathD, ec);
		if (ec)
			return false;
	} else {
		std::filesystem::remove(path);
	}
	std::filesystem::rename(pathD, path, ec);
	if (ec)
		return false;
	return true;
}

void xMainWnd::OnButtonClick_Analyze(wxCommandEvent& event) {
	auto strFolder = m_dir->GetPath();
	stdfs::path path = strFolder.ToStdWstring();
	if (path.empty())
		return;

	m_folderCurrent = path;
	SaveCurrentFolderPath(path.wstring());

	m_lst->DeleteAllItems();

	auto filters = m_cmbFilter->GetValue().ToStdWstring();
	auto filtersExclude = m_cmbFilterExclude->GetValue().ToStdWstring();
	FILTER filter;
	auto Splitter = [](std::wstring const& str, std::wstring& filter, std::wstring& filterFolder) -> void {
		for (auto f : std::ranges::split_view(str, L';')) {
			std::wstring_view sv(f);
			if (sv.ends_with('/') or sv.ends_with('\\')) {
				if (sv.remove_suffix(1); !sv.empty()) {
					filterFolder += sv;
					filterFolder += L';';
				}
			}
			else {
				filter += sv;
				filter += ';';
			}
		}
		gtl::Trim(filter, L';');
		gtl::Trim(filterFolder, L';');
	};
	Splitter(filters, filter.filters, filter.filtersFolder);
	Splitter(filtersExclude, filter.filtersExclude, filter.filtersFolderExclude);

	AnalyzePath(*m_lst, m_lst->GetRootItem(), path, filter);

}

void xMainWnd::OnButtonClick_Convert(wxCommandEvent& event) {
	std::vector<stdfs::path> paths;
}

void xMainWnd::OnButtonClick_Browse(wxCommandEvent& event) {
	auto const strFolder = m_browser->GetPath();
	if (strFolder.empty())
		return;
	m_dir->ExpandPath(strFolder);
	m_dir->SelectPath(strFolder);

	SaveCurrentFolderPath(strFolder);
}

void xMainWnd::OnTreelistSelectionChanged_Lst(wxTreeListEvent& event) {
	auto path = GetSelectedFilePath(event.GetItem());
	//auto type = gtl::ReadFileBOM(path);
	std::error_code ec;
	auto size = std::filesystem::file_size(path, ec);
	if (ec) {
		auto w = ec.message();
		return;
	}
	wxString str;
	gtl::xIFArchive ar(path);
	auto bom = ar.ReadCodepageBOM(gtl::eCODEPAGE::ANSI_WINDOWS);
	switch (bom) {
	case gtl::eCODEPAGE::UTF8:
		while (auto r = ar.ReadLineU8()) {
			str += wxString(gtl::ToStringW(*r));
			str += "\r\n";
		}
		break;
	case gtl::eCODEPAGE::UTF16LE:
	case gtl::eCODEPAGE::UTF16BE:
	case gtl::eCODEPAGE::UTF32LE:
	case gtl::eCODEPAGE::UTF32BE:
		while (auto r = ar.ReadLineW()) {
			str += wxString(*r);
			str += L"\r\n";
		}
		break;
	default:
		{
			std::string s;
			s.resize(size);
			ar.Read<char>(s.data(), s.size());
			auto codepage = gtl::DetectCodepage(std::string_view(s));
			m_cmbEncoding->SetValue(codepage);
			// using ICU, convert string to wstring
			gtl::Ticonv<wchar_t, char> conv(nullptr, codepage.c_str());
			str = conv.Convert(s).value_or(L"");
		}
		break;
	}

	m_code->SetText(str);
}

void xMainWnd::OnCombobox_Encoding(wxCommandEvent& event) {
}

void xMainWnd::OnButtonClick_ConvertSelectedFile(wxCommandEvent& event) {
	auto path = GetSelectedFilePath();
	auto strCodepage = m_cmbCodepageDest->GetValue().ToStdString();
	if (strCodepage.empty())
		return;
	int codepage = std::stoi(strCodepage);

	std::error_code ec;
	ConvertFileEncoding(path, codepage, m_chkWriteBOM->IsChecked(), m_chkBackupOriginalFiles->IsChecked(), m_chkPreserveModifiedTime->IsChecked());
	//auto size_char = GetCharSizeFromCodepage(strCodepage);
}

//=================================================================================================================================
//


template <typename TCHAR>
int TFindOneOf(const TCHAR* pszSource, const TCHAR* pszDelimiters) {
	for (const TCHAR* psz = pszSource; psz && *psz; psz++) {
		for (const TCHAR* pszDelimiter = pszDelimiters; *pszDelimiter; pszDelimiter++) {
			if (*pszDelimiter == *psz)
				return (int)(psz - pszSource);
		}
	}
	return -1;
}

template <typename TCHAR, bool bCaseSensitive = false>
bool TFilterString(std::basic_string_view<TCHAR> svSRC, std::basic_string_view<TCHAR> svFilter, std::vector<std::basic_string<TCHAR>>& strParams) {
	auto szSRC = svSRC.begin(), szFilter = svFilter.begin();
	int inc = 1;
	for (; szSRC != svSRC.end() && szFilter != svFilter.end(); szSRC+=inc, szFilter++) {
		inc = 1;
		switch (*szFilter) {
		case '?' :
			{
				std::vector<std::basic_string<TCHAR>> strParamsNew;
				if (TFilterString<TCHAR, bCaseSensitive>({szSRC+1, svSRC.end()}, {szFilter+1, svFilter.end()}, strParamsNew)) {
					std::basic_string<TCHAR> s;
					s.push_back(*szSRC);
					strParams.emplace_back(std::move(s));
					for (const auto& str : strParamsNew)
						strParams.emplace_back(str);
					return true;
				}
			}
			break;

		case '*' :
			{
				std::basic_string<TCHAR> str{szSRC, svSRC.end()};
				for (size_t nPos = 0; nPos <= str.size(); nPos++) {
					std::vector<std::basic_string<TCHAR>> strParamsNew;
					if (TFilterString<TCHAR, bCaseSensitive>({szSRC+nPos, svSRC.end()}, {szFilter+1, svFilter.end()}, strParamsNew)) {
						strParams.emplace_back(str.substr(0, nPos));
						for (const auto& str : strParamsNew)
							strParams.emplace_back(str);
						return true;
					}
				}
				inc = 0;
			}
			break;

		default :
			if constexpr (bCaseSensitive) {
				if (*szSRC != *szFilter)
					return false;
			} else {
				if (std::tolower(*szSRC) != std::tolower(*szFilter))
					return false;
			}
			break;
		}
	}

	return (szSRC == svSRC.end()) && (szFilter == svFilter.end());	// both reached to end
}

template < bool bCaseSensitive >
bool FilterFileMultiFilter(std::wstring_view pszFilters, std::wstring_view pszName, std::wstring_view szSpliter) {
	if (pszFilters.empty() || pszName.empty())
		return true;

	//std::vector<std::wstring> strsFilter;
	//TSplitString<wchar_t>(pszFilters, szSpliter, strsFilter);
	for (auto f : std::ranges::split_view(pszFilters, ';')) {
		std::wstring_view filter(f.begin(), f.end());
		std::vector<std::wstring> strings;
		if (TFilterString<wchar_t, bCaseSensitive>(pszName, filter, strings))
			return true;
	}

	return false;
}

