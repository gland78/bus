#pragma once
#include "afxdialogex.h"

#include <afxdb.h>//

class CbusView;
// findID 대화 상자

class findID : public CDialogEx
{
	DECLARE_DYNAMIC(findID)

public:
	findID(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~findID();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CEdit nameEdit;

	CRecordset* m_prs;//
	CDatabase m_db;//

	CbusView* view;

	BOOL bopen;//
	afx_msg void OnBnClickedOk();
};
