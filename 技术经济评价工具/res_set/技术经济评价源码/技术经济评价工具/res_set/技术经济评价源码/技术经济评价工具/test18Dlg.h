// test18Dlg.h : header file
//

#if !defined(AFX_TEST18DLG_H__49C1D1CD_2415_4F7B_8AD8_5E843F6E37D2__INCLUDED_)
#define AFX_TEST18DLG_H__49C1D1CD_2415_4F7B_8AD8_5E843F6E37D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTest18Dlg dialog

class CTest18Dlg : public CDialog
{
// Construction
public:
	CTest18Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTest18Dlg)
	enum { IDD = IDD_TEST18_DIALOG };
	CComboBox	m_NewCom2;
	CComboBox	m_NewCom1;
	int		m_Radio1;
	int		m_Radio2;
	CString	m_Result;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTest18Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTest18Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnData1();
	afx_msg void OnData2();
	afx_msg void OnOk1();
	afx_msg void OnOk2();
	afx_msg void OnAbout();
	afx_msg void OnExit();
	afx_msg void OnClear();
	afx_msg void OnClearfile();
	afx_msg void OnAbout2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST18DLG_H__49C1D1CD_2415_4F7B_8AD8_5E843F6E37D2__INCLUDED_)
