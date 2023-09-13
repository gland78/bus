#pragma once
#include "afxdialogex.h"


// seat_Sel 대화 상자
class CbusView;
class seat_Sel : public CDialogEx
{
	DECLARE_DYNAMIC(seat_Sel)

public:
	seat_Sel(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~seat_Sel();

	CbusView* view;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	virtual void PostNcDestroy();
	afx_msg void OnPaint();

	void activate(int num);
	BOOL checkbox(int num);

	int listnumber; ///buslist에서 선택된 좌석 위치
	afx_msg void OnBnClickedBack();
};
