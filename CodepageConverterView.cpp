
// CodepageConverterView.cpp : implementation of the CCodepageConverterView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "CodepageConverter.h"
#endif

#include "CodepageConverterDoc.h"
#include "CodepageConverterView.h"

#include <vector>
#include <algorithm>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifndef UNICODE_PAGE1200_BOM
#	define UNICODE_PAGE1200_BOM (0xFEFF)		// Unicode Little Endian
#endif

#ifndef UNICODE_PAGE1201_BOM
#	define UNICODE_PAGE1201_BOM (0xFFFE)		// Unicode BIG Endian
#endif

#ifndef UTF8_BOM
#	define UTF8_BOM "\xEF\xBB\xBF"
#endif

#ifndef ZeroVar
#	define ZeroVar(var) memset(&var, 0, sizeof(var))
#endif

BOOL FilterFileMultiFilter(LPCTSTR pszFilters, LPCTSTR pszName, BOOL bCaseSensitive, LPCTSTR szSpliter);

// CCodepageConverterView

IMPLEMENT_DYNCREATE(CCodepageConverterView, CFormView)

BEGIN_MESSAGE_MAP(CCodepageConverterView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_BN_CLICKED(IDC_CONVERT, &CCodepageConverterView::OnBnClickedConvert)
	ON_BN_CLICKED(IDC_REFRESH, &CCodepageConverterView::OnBnClickedRefresh)
	ON_COMMAND(ID_VIEW_REFRESH, &CCodepageConverterView::OnViewRefresh)
	ON_BN_CLICKED(IDC_GO_UP, &CCodepageConverterView::OnBnClickedGoUp)
	ON_BN_CLICKED(IDC_SET_CUR_PATH, &CCodepageConverterView::OnBnClickedSetCurPath)
	ON_NOTIFY(TVN_SELCHANGED, IDC_MFCSHELLTREE1, &CCodepageConverterView::OnSelchangedMfcshelltree1)
	ON_NOTIFY(TVN_ITEMCHANGED, IDC_MFCSHELLTREE1, &CCodepageConverterView::OnItemchangedMfcshelltree1)
END_MESSAGE_MAP()

// CCodepageConverterView construction/destruction

CCodepageConverterView::CCodepageConverterView() : CFormView(IDD_CODEPAGECONVERTER_FORM) {
}

CCodepageConverterView::~CCodepageConverterView() {
}

void CCodepageConverterView::DoDataExchange(CDataExchange* pDX) {
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CODE_PAGE_SRC, m_cboCodepageSrc);
	DDX_Control(pDX, IDC_CODE_PAGE_DEST, m_cboCodepageDest);
	DDX_Control(pDX, IDC_FILTER, m_cboFilter);
	DDX_Control(pDX, IDC_FILTER_EXCLUDE, m_cboFilterExclude);
	DDX_Control(pDX, IDC_MFCSHELLTREE1, m_tree);
	DDX_Control(pDX, IDC_MFCSHELLLIST1, m_lst);
}

BOOL CCodepageConverterView::PreCreateWindow(CREATESTRUCT& cs) {

	return CFormView::PreCreateWindow(cs);
}

void CCodepageConverterView::OnInitialUpdate() {
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	//ResizeParentToFit();

	//m_lst.ModifyStyle(0, TVS_FULLROWSELECT);
	//m_lst.DisplayFolder(_T("C:\\Downloads\\"));

	LPCTSTR pszCodepage[] = {
		_T("949 - Korean"),
		_T("1250 - Latin 2"),
		_T("1251 - Cyrillic"),
		_T("1252 - Western"),
		_T("1253 - Greek"),
		_T("950 - (Chinese)BIG5"),
		_T("1370 - (Chinese)BIG5"),
		_T("932 - (Japanese)Shift JIS"),
		_T("943 - (Japanese)Shift JIS"),
	};
	for (const auto& psz : pszCodepage)
		m_cboCodepageSrc.AddString(psz);
	m_cboCodepageSrc.SetCurSel(0);

	m_cboCodepageDest.AddString(_T("65001 - UTF-8"));
	m_cboCodepageDest.AddString(_T("1200 - Unicode Little-Endian"));
	m_cboCodepageDest.SetCurSel(0);

	m_cboFilter.AddString(_T("*.cpp;*.cxx;*.h;*.hpp;*.hxx"));
	m_cboFilter.AddString(_T("*.txt"));
	m_cboFilter.AddString(_T("*.*"));
	m_cboFilter.SetCurSel(0);

	m_cboFilterExclude.AddString(_T("resource.h"));
	m_cboFilterExclude.SetCurSel(0);

	CheckDlgButton(IDC_CB_BACKUP, theApp.GetProfileInt(_T("misc"), _T("BACKUP"), 1));
	CheckDlgButton(IDC_CB_PRESERVE_MODIFIED_TIME, theApp.GetProfileInt(_T("misc"), _T("PRESERVE_MODIFIED_TIME"), 0));
	CheckDlgButton(IDC_CB_DONT_CONVERT_IF_CODEPAGE_IRRELAVANT, theApp.GetProfileInt(_T("misc"), _T("DONT_CONVERT_IF_CODEPAGE_IRRELAVANT"), 0));

	m_tree.Expand(TVI_ROOT, TVE_EXPAND);
	m_tree.SetRelatedList(&m_lst);

	CString strCurrentFolder;
	strCurrentFolder = theApp.GetProfileString(_T("misc"), _T("LastFolder"), _T(""));
	SetDlgItemText(IDC_PATH, strCurrentFolder);
	//m_tree.SelectPath(strCurrentFolder);
	m_lst.DisplayFolder(strCurrentFolder);

}

void CCodepageConverterView::OnRButtonUp(UINT /* nFlags */, CPoint point) {
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCodepageConverterView::OnContextMenu(CWnd* /* pWnd */, CPoint point) {
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCodepageConverterView diagnostics

#ifdef _DEBUG
void CCodepageConverterView::AssertValid() const { CFormView::AssertValid(); }
void CCodepageConverterView::Dump(CDumpContext& dc) const { CFormView::Dump(dc); }
CCodepageConverterDoc* CCodepageConverterView::GetDocument() const { ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCodepageConverterDoc))); return (CCodepageConverterDoc*)m_pDocument; }
#endif //_DEBUG


// CCodepageConverterView message handlers
bool CCodepageConverterView::ConvertCodepage_Folder(UINT eCodepageSource, UINT eCodepageDest, LPCTSTR pszFolder, LPCTSTR pszFilters, LPCTSTR pszFiltersExclude, bool bBackup, bool bPreserveModifiedTime, bool bDontConvertIfCodepageIrrelavant) {
	CFileFind ff;
	bool bFound = ff.FindFile(CString(pszFolder) + _T("\\*")) != false;
	while (bFound) {
		bFound = ff.FindNextFile() != false;

		if (ff.IsDots())
			continue;

		if (FilterFileMultiFilter(pszFiltersExclude, ff.GetFileName(), false, _T(";")))
			continue;

		if (ff.IsDirectory()) {
			ConvertCodepage_Folder(eCodepageSource, eCodepageDest, ff.GetFilePath(), pszFilters, pszFiltersExclude, bBackup, bPreserveModifiedTime, bDontConvertIfCodepageIrrelavant);
		} else {
			if (FilterFileMultiFilter(pszFilters, ff.GetFileName(), false, _T(";")))
				ConvertCodepage(eCodepageSource, eCodepageDest, ff.GetFilePath(), bBackup, bPreserveModifiedTime, bDontConvertIfCodepageIrrelavant);
		}
	}

	return true;
}

bool CCodepageConverterView::ConvertCodepage(UINT eCodepageSource, UINT eCodepageDest, LPCTSTR pszPathSource, bool bBackup, bool bPreserveModifiedTime, bool bDontConvertIfCodepageIrrelavant) {
	std::vector<char> buf;
	FILETIME ftC, ftM;
	ZeroVar(ftC);
	ZeroVar(ftM);
	{
		CFile f;
		CFileException e;
		if (!f.Open(pszPathSource, CFile::modeRead, &e))
			return false;
		GetFileTime(f, &ftC, nullptr, &ftM);
		ULONGLONG len = f.GetLength();
		if ( (len <= 0) ||(len > 16 * 1024 * 1024) )
			return false;

		buf.assign(len, 0);

		f.Read(buf.data(), len);

		// Check Code first.
		if ( (len >= 2) 
			&& (
				(*(wchar_t*)buf.data() == UNICODE_PAGE1200_BOM)
				|| (*(wchar_t*)buf.data() == UNICODE_PAGE1201_BOM)
				)
			)
		{
			return false;
		}

		if ( (len >= 3) && (memcmp(buf.data(), UTF8_BOM, 3) == 0) ) {
			return false;
		}

	}

	std::vector<wchar_t> szUnicode;

	int nLen = 0;
	{
		nLen = MultiByteToWideChar(eCodepageSource, 0, buf.data(), buf.size(), nullptr, 0);
		if (nLen <= 0)
			return false;
		szUnicode.assign(nLen, 0);
		nLen = MultiByteToWideChar(eCodepageSource, 0, buf.data(), buf.size(), szUnicode.data(), szUnicode.size());
		if (nLen < 0)
			return false;
	}

	std::vector<BYTE> szResult;
	std::vector<BYTE> szHeader;
	if (eCodepageDest == CP_UTF8) {
		szHeader.assign({0xEF, 0xBB, 0xBF});

		int nLenResult = WideCharToMultiByte(eCodepageDest, 0, szUnicode.data(), nLen, nullptr, 0, nullptr, nullptr);
		if (nLenResult <= 0)
			return false;

		szResult.assign(nLenResult, 0);
		nLenResult = WideCharToMultiByte(eCodepageDest, 0, szUnicode.data(), nLen, (char*)szResult.data(), nLenResult, nullptr, nullptr);
		if (nLenResult <= 0)
			return false;

	} else if (eCodepageDest == 1200) {
		szHeader.assign({0xFF, 0xFE});

		szResult.assign((nLen)*sizeof(wchar_t), 0);
		wchar_t* pos = (wchar_t*)szResult.data();
		memcpy(pos, szUnicode.data(), nLen*sizeof(wchar_t));
	} else {
		return false;
	}

	if (bDontConvertIfCodepageIrrelavant) {
		if ( (buf.size() == szResult.size()) && (memcmp(buf.data(), szResult.data(), buf.size()) == 0) )
			return false;
	}

	if (szResult.size()) {
		bool bBackedUp = false;
		if (bBackup)
			bBackedUp = MoveFileEx(pszPathSource, CString(pszPathSource) + _T(".org"), MOVEFILE_REPLACE_EXISTING);
		if ( !bBackup || bBackedUp ) {	// 백업 안하거나, 백업이 잘 됐거나...
			CFile f;
			CFileException e;
			if (f.Open(pszPathSource, CFile::modeCreate|CFile::modeWrite, &e)) {
				if (szHeader.size())
					f.Write(szHeader.data(), szHeader.size());
				f.Write(szResult.data(), szResult.size());
				f.Flush();
				if (bPreserveModifiedTime)
					SetFileTime(f, nullptr, nullptr, &ftM);
			}
		}
	}

	return true;
}

void CCodepageConverterView::OnBnClickedConvert() {
	CWaitCursor wc;

	CString strCurrentFolder;
	m_lst.GetCurrentFolder(strCurrentFolder);
	theApp.WriteProfileString(_T("misc"), _T("LastFolder"), strCurrentFolder);
	SetDlgItemText(IDC_PATH, strCurrentFolder);

	int nItem = m_lst.GetItemCount();
	UINT eCodepageSource = GetDlgItemInt(IDC_CODE_PAGE_SRC);
	UINT eCodepageDest = GetDlgItemInt(IDC_CODE_PAGE_DEST);
	CString strFilters, strFiltersExclude;
	GetDlgItemText(IDC_FILTER, strFilters);
	GetDlgItemText(IDC_FILTER_EXCLUDE, strFiltersExclude);
	bool bBackup = IsDlgButtonChecked(IDC_CB_BACKUP);
	bool bPreserveModifiedTime = IsDlgButtonChecked(IDC_CB_PRESERVE_MODIFIED_TIME);
	bool bDontConvertIfCodepageIrrelavant = IsDlgButtonChecked(IDC_CB_DONT_CONVERT_IF_CODEPAGE_IRRELAVANT);

	theApp.WriteProfileInt(_T("misc"), _T("BACKUP"), bBackup);
	theApp.WriteProfileInt(_T("misc"), _T("PRESERVE_MODIFIED_TIME"), bPreserveModifiedTime);
	theApp.WriteProfileInt(_T("misc"), _T("DONT_CONVERT_IF_CODEPAGE_IRRELAVANT"), bDontConvertIfCodepageIrrelavant);

	if (m_lst.GetSelectedCount() > 0) {
		for (int iItem = 0; iItem < nItem; iItem++) {
			if (!m_lst.GetItemState(iItem, LVIS_SELECTED))
				continue;

			CString strPath;
			if (!m_lst.GetItemPath(strPath, iItem))
				continue;
			if (PathIsDirectory(strPath)) {
				ConvertCodepage_Folder(eCodepageSource, eCodepageDest, strPath, strFilters, strFiltersExclude, bBackup, bPreserveModifiedTime, bDontConvertIfCodepageIrrelavant);
			} else {
				ConvertCodepage(eCodepageSource, eCodepageDest, strPath, bBackup, bPreserveModifiedTime, bDontConvertIfCodepageIrrelavant);
			}

		}
	} else {
		CString strDrive, strFolder, strTitle, strExt;
		_tsplitpath(strCurrentFolder, strDrive.GetBuffer(260), strFolder.GetBuffer(260), strTitle.GetBuffer(260), strExt.GetBuffer(260));
		strDrive.ReleaseBuffer();
		strFolder.ReleaseBuffer();
		strTitle.ReleaseBuffer();
		strExt.ReleaseBuffer();
		if ( strCurrentFolder.IsEmpty() || strDrive.IsEmpty() || strFolder.IsEmpty() || (strFolder == _T("\\")) ) {
			MessageBox(_T("CANNOT Convert the Whole disk"));
			return;
		}
		ConvertCodepage_Folder(eCodepageSource, eCodepageDest, strCurrentFolder, strFilters, strFiltersExclude, bBackup, bPreserveModifiedTime, bDontConvertIfCodepageIrrelavant);
	}

	OnBnClickedRefresh();
}


void CCodepageConverterView::OnBnClickedGoUp() {
	m_lst.DisplayParentFolder();
}

void CCodepageConverterView::OnBnClickedRefresh() {
	vector<CString> strsItemSelected;
	CString strItemFocused;

	if (m_lst.GetSelectedCount() > 0) {
		int nItem = m_lst.GetItemCount();
		for (int iItem = 0; iItem < nItem; iItem++) {
			if (!m_lst.GetItemState(iItem, LVIS_SELECTED))
				continue;

			CString strItem = m_lst.GetItemText(iItem, 0);
			strsItemSelected.push_back(strItem);
			if (m_lst.GetItemState(iItem, LVIS_FOCUSED))
				strItemFocused = strItem;
		}
	}

	m_lst.Refresh();
	// Re-Select
	int nItem = m_lst.GetItemCount();
	for (int iItem = 0; iItem < nItem; iItem++) {
		if (m_lst.GetItemState(iItem, LVIS_SELECTED))
			continue;

		CString strItem  = m_lst.GetItemText(iItem, 0);
		auto pos = find(strsItemSelected.begin(), strsItemSelected.end(), strItem);
		if (pos == strsItemSelected.end())
			continue;
		m_lst.SetItemState(iItem, LVIS_SELECTED, LVIS_SELECTED);
		if ( !strItemFocused.IsEmpty() && (strItemFocused == strItem) )
			m_lst.SetItemState(iItem, LVIS_FOCUSED, LVIS_FOCUSED);
	}
	m_lst.SetFocus();
}

void CCodepageConverterView::OnViewRefresh() {
	OnBnClickedRefresh();
}

void CCodepageConverterView::OnBnClickedSetCurPath() {
	CString strPath;
	GetDlgItemText(IDC_PATH, strPath);
	//m_tree.SelectPath(strPath, true);
	m_lst.DisplayFolder(strPath);
}

void CCodepageConverterView::OnSelchangedMfcshelltree1(NMHDR *pNMHDR, LRESULT *pResult) {
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	CString strPath;
	m_tree.GetItemPath(strPath);
	//SetDlgItemText(IDC_PATH, strPath);
	//if (m_lst)
	//	m_lst.DisplayFolder(strPath);

	*pResult = 0;
}

void CCodepageConverterView::OnItemchangedMfcshelltree1(NMHDR *pNMHDR, LRESULT *pResult) {
	NMTVITEMCHANGE *pNMTVItemChange = reinterpret_cast<NMTVITEMCHANGE*>(pNMHDR);

	if (pNMTVItemChange->uStateNew & TVIS_SELECTED) {
		CString strPath;
		m_tree.GetItemPath(strPath);
		SetDlgItemText(IDC_PATH, strPath);
	}

	*pResult = 0;
}

//=================================================================================================================================
//


template <typename TCHAR, class TSTRING>
int TFindOneOf(const TCHAR* pszSource, const TCHAR* pszDelimiters) {
	for (const TCHAR* psz = pszSource; psz && *psz; psz++) {
		for (const TCHAR* pszDelimiter = pszDelimiters; *pszDelimiter; pszDelimiter++) {
			if (*pszDelimiter == *psz)
				return (int)(psz - pszSource);
		}
	}
	return -1;
}

template <typename TCHAR, class TSTRING>
int TSplitString(TSTRING strSRC, const TCHAR* pszDelimiters, std::vector<TSTRING>& strs, int nInitialSize = 0) {
	strs.clear();
	if (nInitialSize > 0)
		strs.reserve(nInitialSize);
	if (strSRC.IsEmpty())
		return 0;
	const TCHAR* pszSRC = strSRC;
	while (TRUE) {
		int index = TFindOneOf<TCHAR, TSTRING>(pszSRC, pszDelimiters);
		if (index < 0) {
			strs.push_back(pszSRC);
			break;
		} else if (index == 0) {
			strs.push_back(TSTRING());
		} else {
			TSTRING str;
			TCHAR* psz = str.GetBufferSetLength(index);
			memcpy(psz, pszSRC, index*sizeof(TCHAR));
			str.ReleaseBuffer();
			strs.push_back(str);
		}
		pszSRC += index+1;
	}
	return strs.size();
}

template <typename TCHAR, class TSTRING>
BOOL TFilterString(const TCHAR* szSRC, const TCHAR* szFilter, vector<TSTRING>& strParams, BOOL bCaseSensitive) {
	for (; *szSRC && *szFilter; szSRC++, szFilter++) {
		switch (*szFilter) {
		case '?' :
			{
				vector<TSTRING> strParamsNew;
				if (TFilterString<TCHAR, TSTRING>(szSRC+1, szFilter+1, strParamsNew, bCaseSensitive)) {
					strParams.emplace_back(*szSRC);
					for (const auto& str : strParamsNew)
						strParams.emplace_back(str);
					return TRUE;
				}
			}
			break;

		case '*' :
			{
				TSTRING str = szSRC;
				for (int nPos = 0; nPos <= str.GetLength(); nPos++) {
					vector<TSTRING> strParamsNew;
					if (TFilterString<TCHAR, TSTRING>(szSRC+nPos, szFilter+1, strParamsNew, bCaseSensitive)) {
						strParams.emplace_back(str.Left(nPos));
						for (const auto& str : strParamsNew)
							strParams.emplace_back(str);
						return TRUE;
					}
				}
				szSRC--;
			}
			break;

		default :
			if (bCaseSensitive) {
				if (*szSRC != *szFilter)
					return FALSE;
			} else {
				if (_totupper(*szSRC) != _totupper(*szFilter))
					return FALSE;
			}
			break;
		}
	}

	return !*szSRC && !*szFilter;	// both reached to end
}

BOOL FilterFileMultiFilter(LPCTSTR pszFilters, LPCTSTR pszName, BOOL bCaseSensitive, LPCTSTR szSpliter) {
	if (!pszFilters || !pszFilters[0] || !pszName || !pszName[0])
		return TRUE;

	//if (bCaseSensitive) {
	vector<CString> strsFilter;
	TSplitString<TCHAR, CString>(pszFilters, szSpliter, strsFilter);
	for (int i = 0; i < strsFilter.size(); i++) {
		if (TFilterString<TCHAR, CString>(pszName, strsFilter[i], vector<CString>(), bCaseSensitive))
			return TRUE;
	}

	return FALSE;
}

