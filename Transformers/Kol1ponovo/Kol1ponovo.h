
// Kol1ponovo.h : main header file for the Kol1ponovo application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CKol1ponovoApp:
// See Kol1ponovo.cpp for the implementation of this class
//

class CKol1ponovoApp : public CWinApp
{
public:
	CKol1ponovoApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CKol1ponovoApp theApp;
