// test18.h : main header file for the TEST18 application
//

#if !defined(AFX_TEST18_H__2259AD6F_B6FE_4F7C_AF5A_781471E14167__INCLUDED_)
#define AFX_TEST18_H__2259AD6F_B6FE_4F7C_AF5A_781471E14167__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTest18App:
// See test18.cpp for the implementation of this class
//

class CTest18App : public CWinApp
{
public:
	CTest18App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTest18App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTest18App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST18_H__2259AD6F_B6FE_4F7C_AF5A_781471E14167__INCLUDED_)
