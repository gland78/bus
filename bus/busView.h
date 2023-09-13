
// busView.h: CbusView 클래스의 인터페이스
//

#pragma once

#include <afxdb.h> //
class dClf;
class seat_Sel;

class managermode;

class login;

class CbusView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CbusView() noexcept;
	DECLARE_DYNCREATE(CbusView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_BUS_FORM };
#endif

// 특성입니다.
public:
	CbusDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CbusView();

	dClf* departure;
	seat_Sel* seat;
	managermode* mmode;

	login* logg;

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMcnSelchangeMonthcalendar1(NMHDR* pNMHDR, LRESULT* pResult);

	CEdit dEdit;
	CListCtrl busList; ///선택 리스트
	CMonthCalCtrl calendar; // 달력
	CListCtrl resultList; //결과 값 리스트

	CDatabase m_db;
	CRecordset* m_prs;
	SQLHDBC mh_odbc;
	SQLHANDLE mh_environment;

	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnPaint();

	void CbusView::totalfeeprint(); //총 요금 값 출력 함수
	CListBox resultlistbox;

	void CbusView::buslistview();
	BOOL bopen;


	BOOL IDcheck; ///ID를 입력 받았는지 확인
	CString ID;

	void managercheck(); // 관리자인지 확인하는 함수
	BOOL admin_check;
	afx_msg void On32771();

	BOOL seat_check = FALSE;
};

#ifndef _DEBUG  // busView.cpp의 디버그 버전
inline CbusDoc* CbusView::GetDocument() const
   { return reinterpret_cast<CbusDoc*>(m_pDocument); }
#endif

