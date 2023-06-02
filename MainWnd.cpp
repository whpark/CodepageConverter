#include "pch.h"
#include "wxDesktopApp.h"
#include "wx/msw/private.h"
#include "MainWnd.h"

#include "gtl/string/convert_codepage.h"
#include "gtl/archive.h"

#include "Codepage.h"

bool FilterFileMultiFilter(wchar_t const* pszFilters, wchar_t const* pszName, bool bCaseSensitive, wchar_t const* szSpliter);

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
}

void xMainWnd::OnButtonClick_Check(wxCommandEvent& event) {
	auto strFolder = m_dir->GetPath();
	stdfs::path path = (LPCWSTR)strFolder;
	std::error_code ec;
	m_list->Clear();
	std::vector<int> lines;
	wxArrayString strs;
	if (ec.clear(); stdfs::is_regular_file(path, ec)) {
		auto e = gtl::CheckCodepage(path, lines);
		if (e == gtl::eFILE_TYPE::unknown) {
			if (lines.empty()) {
				strs.Add(std::format(L"{}", path.filename().wstring()));
			} else {
				for (auto line : lines)
					strs.Add(std::format(L"{} : {}", path.filename().wstring(), line));
			}
		}
	}
	else if (ec.clear(); stdfs::is_directory(path, ec)) {
		std::wstring filters = m_cmbFilter->GetValue().ToStdWstring();

		ec.clear();
		for (auto entry : stdfs::recursive_directory_iterator(path, ec)) {
			if (entry.is_directory())
				continue;
			auto path = entry.path();

			if (!FilterFileMultiFilter(filters.c_str(), path.filename().c_str(), false, L";"))
				continue;

			std::vector<int> lines;
			auto e = gtl::CheckCodepage(path, lines);
			if (e != gtl::eFILE_TYPE::unknown)
				continue;
			std::wstring str;
			str = path.wstring();
			for (auto line : lines)
				str += std::format(L", {}", line);
			strs.Add(str);
		}
	}
	if (!strs.empty())
		m_list->InsertItems(strs, m_list->GetCount());
}

void xMainWnd::OnButtonClick_Convert(wxCommandEvent& event) {
}

void xMainWnd::OnButtonClick_Browse(wxCommandEvent& event) {
	auto strFolder = m_browser->GetPath();
	m_dir->ExpandPath(strFolder);
	m_dir->SelectPath(strFolder);
	auto& app = wxGetApp();
	wxRegKey reg(app.m_reg, L"misc");
	reg.Create();
	reg.SetValue(L"LastFolder", strFolder);
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

template <typename TCHAR>
int TSplitString(std::basic_string<TCHAR> strSRC, const TCHAR* pszDelimiters, std::vector<std::basic_string<TCHAR>>& strs, int nInitialSize = 0) {
	strs.clear();
	if (nInitialSize > 0)
		strs.reserve(nInitialSize);
	if (strSRC.empty())
		return 0;
	const TCHAR* pszSRC = strSRC.c_str();
	while (true) {
		int index = TFindOneOf<TCHAR>(pszSRC, pszDelimiters);
		if (index < 0) {
			strs.push_back(pszSRC);
			break;
		} else if (index == 0) {
			strs.push_back(std::basic_string<TCHAR>());
		} else {
			std::basic_string<TCHAR> str;
			str.assign(index, 0);
			TCHAR* psz = str.data();
			memcpy(psz, pszSRC, index*sizeof(TCHAR));
			//str.ReleaseBuffer();
			strs.push_back(str);
		}
		pszSRC += index+1;
	}
	return strs.size();
}

template <typename TCHAR>
bool TFilterString(const TCHAR* szSRC, const TCHAR* szFilter, std::vector<std::basic_string<TCHAR>>& strParams, bool bCaseSensitive) {
	for (; *szSRC && *szFilter; szSRC++, szFilter++) {
		switch (*szFilter) {
		case '?' :
			{
				std::vector<std::basic_string<TCHAR>> strParamsNew;
				if (TFilterString<TCHAR>(szSRC+1, szFilter+1, strParamsNew, bCaseSensitive)) {
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
				std::basic_string<TCHAR> str = szSRC;
				for (size_t nPos = 0; nPos <= str.size(); nPos++) {
					std::vector<std::basic_string<TCHAR>> strParamsNew;
					if (TFilterString<TCHAR>(szSRC+nPos, szFilter+1, strParamsNew, bCaseSensitive)) {
						strParams.emplace_back(str.substr(0, nPos));
						for (const auto& str : strParamsNew)
							strParams.emplace_back(str);
						return true;
					}
				}
				szSRC--;
			}
			break;

		default :
			if (bCaseSensitive) {
				if (*szSRC != *szFilter)
					return false;
			} else {
				if (_totupper(*szSRC) != _totupper(*szFilter))
					return false;
			}
			break;
		}
	}

	return !*szSRC && !*szFilter;	// both reached to end
}

bool FilterFileMultiFilter(wchar_t const* pszFilters, wchar_t const* pszName, bool bCaseSensitive, wchar_t const* szSpliter) {
	if (!pszFilters || !pszFilters[0] || !pszName || !pszName[0])
		return true;

	//if (bCaseSensitive) {
	std::vector<std::wstring> strsFilter;
	TSplitString<wchar_t>(pszFilters, szSpliter, strsFilter);
	for (int i = 0; i < strsFilter.size(); i++) {
		std::vector<std::wstring> strings;
		if (TFilterString<wchar_t>(pszName, strsFilter[i].c_str(), strings, bCaseSensitive))
			return true;
	}

	return false;
}

