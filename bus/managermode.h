#pragma once
#include "afxdialogex.h"


#include <afxdb.h>//

class CbusView;
// managermode 대화 상자

class managermode : public CDialogEx
{
	DECLARE_DYNAMIC(managermode)

public:
	managermode(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~managermode();

	CbusView* view;

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG7 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton2();

	CRecordset* m_prs;//
	CDatabase m_db;//
	BOOL bopen;//
	int listnumber;
	int LKER = 0;

	virtual void PostNcDestroy();
	CListCtrl DBList;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton3();
	CListCtrl Filter_DBList;


	//void managermode::Destroy();
	virtual BOOL OnInitDialog();
};
