#pragma once
#include "afxdialogex.h"

#include <afxdb.h>//

// signup 대화 상자

class signup : public CDialogEx
{
	DECLARE_DYNAMIC(signup)

public:
	signup(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~signup();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG6 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton2();

	//헤더에 라디오 버튼을 처리할 함수와 라디오 버튼의 이름을 받아 줄 UINT 형 변수를 선언해 준다.
	afx_msg void RadioCtrl(UINT id);
	UINT m_radio_index;

	CEdit nameEdit;
	CEdit idEdit;
	CEdit pwEdit;

	BOOL check; // ID 중복 확인 버튼
	BOOL bopen;

	CRecordset* m_prs;//
	CDatabase m_db;//

	CEdit pw_contrast;
	afx_msg void OnBnClickedButton3();
	BOOL pw_check;


	BOOL admin_check;
};
