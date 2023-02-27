
// CodepageConverterView.h : interface of the CCodepageConverterView class
//

#pragma once
#include "afxshelllistctrl.h"
#include "afxwin.h"
#include "afxshelltreectrl.h"


class CCodepageConverterView : public CFormView {
protected: // create from serialization only
	CCodepageConverterView();
	DECLARE_DYNCREATE(CCodepageConverterView)

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CODEPAGECONVERTER_FORM };
#endif

// Attributes
public:
	CCodepageConverterDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CCodepageConverterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CComboBox m_cboCodepageSrc;
	CComboBox m_cboCodepageDest;
	CComboBox m_cboFilter;
	CComboBox m_cboFilterExclude;
	CMFCShellTreeCtrl m_tree;
	CMFCShellListCtrl m_lst;

	//=============================================================================
	// Clipboard

	CEdit* GetFocusedEdit(CWnd* pWnd) {
		if (!pWnd || !pWnd->m_hWnd)
			return NULL;
		CWnd* pWndFocused = pWnd->GetFocus();
		if (!pWndFocused)
			return NULL;
		if (pWndFocused->IsKindOf(RUNTIME_CLASS(CEdit)))
			return (CEdit*)pWndFocused;
		TCHAR szClassName[64];
		::GetClassName(pWndFocused->m_hWnd, szClassName, sizeof(szClassName));
		if (_tcscmp(szClassName, _T("Edit")) == 0)
			return (CEdit*)pWndFocused;

		return NULL;
	}
	BOOL OnEditCopy(CWnd* pWnd) {
		CEdit* pEdit = GetFocusedEdit(pWnd);
		if (!pEdit)
			return FALSE;
		pEdit->Copy();
		return TRUE;
	}
	BOOL OnEditCut(CWnd* pWnd) {
		CEdit* pEdit = GetFocusedEdit(pWnd);
		if (!pEdit)
			return FALSE;
		pEdit->Cut();
		return TRUE;
	}
	BOOL OnEditPaste(CWnd* pWnd) {
		CEdit* pEdit = GetFocusedEdit(pWnd);
		if (!pEdit)
			return FALSE;
		pEdit->Paste();
		return TRUE;
	}
	BOOL OnEditUndo(CWnd* pWnd) {
		CEdit* pEdit = GetFocusedEdit(pWnd);
		if (!pEdit)
			return FALSE;
		pEdit->Undo();
		return TRUE;
	}


	//=============================================================================
	//

	inline BOOL OnCmdMsg_EditFunction(CWnd* pWnd, UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) {
		if (nCode == CN_COMMAND) {
			if (pExtra) {
				switch (nID) {
				case ID_EDIT_COPY :
				case ID_EDIT_CUT :
				case ID_EDIT_PASTE :
				case ID_EDIT_UNDO :
					if (GetFocusedEdit(pWnd))
						return TRUE;
					break;
				}
			} else {
				switch (nID) {
				case ID_EDIT_COPY :		if (OnEditCopy(pWnd)) return TRUE; break;
				case ID_EDIT_CUT :		if (OnEditCut(pWnd)) return TRUE; break;
				case ID_EDIT_PASTE :	if (OnEditPaste(pWnd)) return TRUE;  break;
				case ID_EDIT_UNDO :		if (OnEditUndo(pWnd)) return TRUE; break;
				}
			}
		}
		return FALSE;
	}


	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) {
		if (OnCmdMsg_EditFunction(this, nID, nCode, pExtra, pHandlerInfo))
			return TRUE;
		return __super::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
	}


protected:
	bool ConvertCodepage_Folder(UINT eCodepageSource, UINT eCodepageDest, LPCTSTR pszFolder, LPCTSTR pszFilters, LPCTSTR pszFiltersExclude, bool bBackup, bool bPreserveModifiedTime, bool bDontConvertIfCodepageIrrelavant);
	bool ConvertCodepage(UINT eCodepageSource, UINT eCodepageDest, LPCTSTR pszPathSource, bool bBackup, bool bPreserveModifiedTime, bool bDontConvertIfCodepageIrrelavant);

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnBnClickedConvert();
	afx_msg void OnBnClickedGoUp();
	afx_msg void OnBnClickedRefresh();
	afx_msg void OnViewRefresh();
	afx_msg void OnBnClickedSetCurPath();
	afx_msg void OnSelchangedMfcshelltree1(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnItemchangedMfcshelltree1(NMHDR *pNMHDR, LRESULT *pResult);
};

#ifndef _DEBUG  // debug version in CodepageConverterView.cpp
inline CCodepageConverterDoc* CCodepageConverterView::GetDocument() const {
	return reinterpret_cast<CCodepageConverterDoc*>(m_pDocument);
}
#endif

