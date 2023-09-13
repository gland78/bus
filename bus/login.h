#pragma once
#include "afxdialogex.h"


#include <afxdb.h>//

// login 대화 상자

class CbusView;

class findID;
class findPW;
class signup;

class login : public CDialogEx
{
	DECLARE_DYNAMIC(login)

public:
	login(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~login();


// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();


	findID* fID;
	findPW* fPW;
	signup* sign;
	CbusView* view;


	CEdit idEdit;
	CEdit pwEdit;


	CRecordset* m_prs;//
	CDatabase m_db;//
	BOOL bopen;//
	virtual void PostNcDestroy();

	CString ID;
	BOOL IDcheck;
	virtual void OnCancel();
	afx_msg void OnBnClickedLogin();
	BOOL am;
};
