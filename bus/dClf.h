#pragma once
#include "afxdialogex.h"


// dClf 대화 상자
class CbusView;
class dClf : public CDialogEx
{
	DECLARE_DYNAMIC(dClf)

public:
	dClf(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~dClf();

	CbusView* view;
	CString str;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	afx_msg void OnBnClickedOk();
	CListCtrl clfBusList;
};
