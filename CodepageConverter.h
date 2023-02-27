
// CodepageConverter.h : main header file for the CodepageConverter application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CCodepageConverterApp:
// See CodepageConverter.cpp for the implementation of this class
//

class CCodepageConverterApp : public CWinAppEx
{
public:
	CCodepageConverterApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCodepageConverterApp theApp;
