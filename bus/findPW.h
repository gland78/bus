#pragma once
#include "afxdialogex.h"


#include <afxdb.h>//

// findPW 대화 상자

class findPW : public CDialogEx
{
	DECLARE_DYNAMIC(findPW)

public:
	findPW(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~findPW();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CEdit idEdit;

	CRecordset* m_prs;//
	CDatabase m_db;//

	BOOL bopen;
	CEdit name_edit;
};
