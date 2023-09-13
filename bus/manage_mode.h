#pragma once
#include "afxdialogex.h"


// manage_mode 대화 상자

class manage_mode : public CDialogEx
{
	DECLARE_DYNAMIC(manage_mode)

public:
	manage_mode(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~manage_mode();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = MANAGE_MODE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
