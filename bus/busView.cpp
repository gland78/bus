
// busView.cpp: CbusView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "bus.h"
#endif

#include "busDoc.h"
#include "busView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "dClf.h"
#include "seat_Sel.h"
#include "managermode.h"

#include "login.h"

// CbusView

IMPLEMENT_DYNCREATE(CbusView, CFormView)

BEGIN_MESSAGE_MAP(CbusView, CFormView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
	ON_BN_CLICKED(IDC_BUTTON1, &CbusView::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CbusView::OnBnClickedButton2)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CbusView::OnLvnItemchangedList1)
	ON_NOTIFY(MCN_SELCHANGE, IDC_MONTHCALENDAR1, &CbusView::OnMcnSelchangeMonthcalendar1)
	ON_BN_CLICKED(IDC_BUTTON4, &CbusView::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CbusView::OnBnClickedButton3)
	ON_WM_PAINT()
	ON_COMMAND(ID_32771, &CbusView::On32771)
END_MESSAGE_MAP()

// CbusView 생성/소멸

CbusView::CbusView() noexcept
	: CFormView(IDD_BUS_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	departure = NULL;
	seat = NULL;
	mmode = NULL;

	IDcheck = false;
	bopen = m_db.OpenEx(_T("DSN=to_2020118023;SERVER=155.230.235.248;PORT=34056;UID=2020118023;PWD=2020118023;DATABASE=s2020118023;"), CDatabase::noOdbcDialog);


	if (IDcheck == false) ///로그인 화면 출력
	{
		logg = new login;
		logg->DoModal();
		ID = (logg->ID);
		IDcheck = (logg->IDcheck);
		admin_check = (logg->am);
		//MessageBox(ID, L"알림", MB_OK | MB_ICONERROR);
		managercheck();
	}
}

CbusView::~CbusView()
{
}

void CbusView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, dEdit);
	DDX_Control(pDX, IDC_LIST1, busList);
	DDX_Control(pDX, IDC_MONTHCALENDAR1, calendar);
	DDX_Control(pDX, IDC_LIST2, resultList);
	DDX_Control(pDX, IDC_LIST3, resultlistbox);
}

BOOL CbusView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CbusView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	busList.InsertColumn(0, L"날짜", LVCFMT_LEFT, 65);
	busList.InsertColumn(1, L"시간", LVCFMT_LEFT, 50);
	busList.InsertColumn(2, L"목적지", LVCFMT_LEFT, 60);
	busList.InsertColumn(3, L"요금", LVCFMT_LEFT, 60);
	busList.InsertColumn(4, L"좌석", LVCFMT_LEFT, 50);

	
	resultList.InsertColumn(0, L"날짜", LVCFMT_LEFT, 60);
	resultList.InsertColumn(1, L"시간", LVCFMT_LEFT, 45);
	resultList.InsertColumn(2, L"목적지", LVCFMT_LEFT, 60);
	resultList.InsertColumn(3, L"요금", LVCFMT_LEFT, 60);
	resultList.InsertColumn(4, L"좌석", LVCFMT_LEFT, 50);


}


// CbusView 인쇄

BOOL CbusView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CbusView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CbusView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CbusView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: 여기에 사용자 지정 인쇄 코드를 추가합니다.
}


// CbusView 진단

#ifdef _DEBUG
void CbusView::AssertValid() const
{
	CFormView::AssertValid();
}

void CbusView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CbusDoc* CbusView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CbusDoc)));
	return (CbusDoc*)m_pDocument;
}
#endif //_DEBUG


// CbusView 메시지 처리기


void CbusView::OnBnClickedButton1() ///검색
{
/*	
	CString strdata;
	if (departure == NULL)
	{
		departure = new dClf;
		departure->view = this;
		departure->Create(IDD_DIALOG1);
		departure->ShowWindow(SW_SHOW);


		//////////////////////////////edit1 값 받아오기
		dEdit.GetWindowTextW(strdata);
		departure->str = strdata;
		departure->Invalidate();
	}
	else
	{
		departure->SetFocus();

		//////////////////////////////
		dEdit.GetWindowTextW(strdata);
		departure->str = strdata;
		departure->Invalidate();
	}
*/

	Invalidate();
	if (IDcheck == false) return;

	CString str;
	dEdit.GetWindowTextW(str); //edit1 값 받아오기

	CString area[] = { L"서울", L"대전", L"대구", L"부산", L"광주", L"강릉" };

	int count=0;
	for (int i = 0; i < 6; i++) ///검색한 내용이 목적지에 있는지 확인
	{
		if (str == area[i]) count++;
	}
	if (count == 0)
	{
		MessageBox(L"검색한 내용이 없습니다.",L"error", MB_OK);
		dEdit.SetSel(0, -1, TRUE); //edit 초기화
		dEdit.Clear();
		return;
	}

	busList.DeleteAllItems(); //list 초기화

	CTime date;
	calendar.GetCurSel(date);

	CString datestr;
	CString time;
	CString fee[] = { L"20,000", L"14,000", L"9,000", L"12,000", L"15,000", L"19,000" };
	CString seat;

	CString b_que;

	for (int i = 21; i >= 9; i--)
	{
		for (int j = 0; j < 6; j++)
		{
			if (area[j] == str)
			{
				datestr.Format(L"%02d/%02d", date.GetMonth(), date.GetDay());
				busList.InsertItem(0, datestr);


				time.Format(L"%02d:00", i);
				busList.SetItemText(0, 1, time);


				busList.SetItemText(0, 2, area[j]);


				busList.SetItemText(0, 3, fee[j]);

				b_que.Format(_T("SELECT count(seat) FROM project_bus where date=\"%s\" and time = \"%s\" and departure=\"%s\""), datestr, time, area[j]);
				//AfxMessageBox(b_que);
				m_prs->Open(CRecordset::snapshot, b_que);
				{
					int row = 1;
					BOOL beof = m_prs->IsEOF();
					DWORD dwsize = m_prs->GetRowsetSize();

					if (!beof) {
						for (m_prs->MoveFirst(); !m_prs->IsEOF(); m_prs->MoveNext()) {
							int fieldc = m_prs->GetODBCFieldCount();

							for (int i = 0; i < fieldc; i++) {
								CString info;
								m_prs->SetAbsolutePosition(row);
								m_prs->GetFieldValue(i, info);
								//str = str + " " + info;
								seat.Format(L"22/%s", info);
								//AfxMessageBox(info);
								busList.SetItemText(0, 4, seat);
							}

							//str += "\n";
							row++;
						} // for m_prs
					} // if 
				}
				m_prs->Close();
			}
		}
	}

}


void CbusView::OnBnClickedButton2()  /// 좌석 선택
{
	int count = busList.GetItemCount(); //리스트 컨트롤의 현재 항목 수를 얻어옵니다.
	int number = 0; //선택된 위치 저장
	for (int i = count; i >= 0; i--)   //모든 항목을 조사하여
		if (busList.GetItemState(i, LVIS_SELECTED) != 0) //선택된 항목
			number = i;
	
	if (count == 0) //버스 list를 선택 했는지 확인 하는 함수
	{
		MessageBox(L"날짜를 선택해 주세요!", L"알림", MB_OK | MB_ICONERROR);
		return;
	}
	else if (number == 0) 
	{
		MessageBox(L"시간를 선택해 주세요!", L"알림", MB_OK | MB_ICONERROR);
		return;
	}
	

	if (seat == NULL)
	{
		seat = new seat_Sel;
		seat->view = this;
		seat->Create(IDD_DIALOG2);
		seat->ShowWindow(SW_SHOW);


		seat->listnumber = number;

		/*
		CString str;
		str.Format(L"%s", busList.GetItemText(number, 0));
		MessageBox(str, L"알림", MB_OK | MB_ICONERROR);
		*/
		
		CString datestr =busList.GetItemText(number, 0);
		CString time = busList.GetItemText(number, 1);
		CString area = busList.GetItemText(number, 2);

		CString b_que;
		b_que.Format(_T("SELECT seat FROM project_bus where date=\"%s\" and time = \"%s\" and departure=\"%s\""), datestr, time, area);
		//AfxMessageBox(b_que);
		m_prs->Open(CRecordset::snapshot, b_que);
		{
			int row = 1;
			BOOL beof = m_prs->IsEOF();
			DWORD dwsize = m_prs->GetRowsetSize();

			if (!beof) {
				for (m_prs->MoveFirst(); !m_prs->IsEOF(); m_prs->MoveNext()) {
					int fieldc = m_prs->GetODBCFieldCount();

					for (int i = 0; i < fieldc; i++) {
						CString info;
						m_prs->SetAbsolutePosition(row);
						m_prs->GetFieldValue(i, info);

						int data = _ttoi(info);
						seat->activate(data);  //이미 있는 좌석 비활성화
	
					}

					//str += "\n";
					row++;
				} // for m_prs
			} // if 
		}
		m_prs->Close();


	}
	else
	{
		seat->SetFocus();

		seat->Invalidate();
	}
}


void CbusView::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


////////////////////////////// 달력 날짜 선택시 수행하는 이벤트 처리기
void CbusView::OnMcnSelchangeMonthcalendar1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMSELCHANGE pSelChange = reinterpret_cast<LPNMSELCHANGE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	buslistview();

	*pResult = 0;
}

void CbusView::buslistview() //buslist를 보여주는 함수
{
	if (IDcheck == false)  ///로그인 화면 출력
	{
		logg = new login;
		logg->DoModal();
		ID = (logg->ID);
		IDcheck = (logg->IDcheck);
		//MessageBox(ID, L"알림", MB_OK | MB_ICONERROR);
		managercheck();
	}

	if (IDcheck == false) return;
	busList.DeleteAllItems();//list 초기화

	dEdit.SetSel(0, -1, TRUE); //edit 초기화
	dEdit.Clear();

	CTime date;
	calendar.GetCurSel(date); ///선택한 날짜를 값으로 변경

	CString datestr;
	CString time;
	CString area[] = { L"서울", L"대전", L"대구", L"부산", L"광주", L"강릉" };
	CString fee[] = { L"20,000", L"14,000", L"9,000", L"12,000", L"15,000", L"19,000" };
	CString seat;


	//	BOOL bopen = m_db.OpenEx(_T("DSN=test1;SERVER=155.230.235.248;PORT=34056;UID=mfcuser01;PWD=mfcuser01;DATABASE=mfctestdb;"), CDatabase::noOdbcDialog); ///test1 변경
	if (bopen)
		m_prs = new CRecordset(&m_db);
	CString b_que;
	CString str = _T("");

	for (int i = 21; i >= 9; i -= 2)
	{
		for (int j = 0; j < 6; j++)
		{
			datestr.Format(L"%02d/%02d", date.GetMonth(), date.GetDay());
			busList.InsertItem(0, datestr);


			time.Format(L"%02d:00", i);
			busList.SetItemText(0, 1, time);


			busList.SetItemText(0, 2, area[j]);


			busList.SetItemText(0, 3, fee[j]);

			b_que.Format(_T("SELECT count(seat) FROM project_bus where date=\"%s\" and time = \"%s\" and departure=\"%s\""), datestr, time, area[j]);
			//AfxMessageBox(b_que);
			m_prs->Open(CRecordset::snapshot, b_que);
			{
				int row = 1;
				BOOL beof = m_prs->IsEOF();
				DWORD dwsize = m_prs->GetRowsetSize();

				if (!beof) {
					for (m_prs->MoveFirst(); !m_prs->IsEOF(); m_prs->MoveNext()) {
						int fieldc = m_prs->GetODBCFieldCount();

						for (int i = 0; i < fieldc; i++) {
							CString info;
							m_prs->SetAbsolutePosition(row);
							m_prs->GetFieldValue(i, info);
							//str = str + " " + info;
							seat.Format(L"22/%s", info);
							//AfxMessageBox(info);
							busList.SetItemText(0, 4, seat);
						}

						//str += "\n";
						row++;
					} // for m_prs
				} // if 
			}
			m_prs->Close();
		}
	}
}


void CbusView::OnBnClickedButton4() //result list 삭제
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int count = resultList.GetItemCount(); //리스트 컨트롤의 현재 항목 수를 얻어옵니다.

	for (int i = count; i >= 0; i--)   //모든 항목을 조사하여
	{
		if (resultList.GetItemState(i, LVIS_SELECTED) != 0) //선택된 항목을 삭제
		{
			resultList.DeleteItem(i);
		}
	}
	totalfeeprint();
	BOOL seat_check = FALSE;
}


void CbusView::OnBnClickedButton3() //result list에 있는 값 DB에 저장
{

	CString query_test;
	CString b_date, b_time, b_departure, b_seat_num;

	if (seat_check == FALSE) {
		MessageBox(L"우선 좌석을 선택해주세요!", L"알림", MB_OK);
		goto st;
	}

	//BOOL bopen = m_db.OpenEx(_T("DSN=2020118023_test;SERVER=155.230.235.248;PORT=34056;UID=mfcuser01;PWD=mfcuser01;DATABASE=mfctestdb;"), CDatabase::noOdbcDialog);
	if (bopen)
		m_prs = new CRecordset(&m_db);
	
	m_db.BeginTrans();

	try {
		for (int i = 0; i < resultList.GetItemCount(); i++)
		{
			b_date = resultList.GetItemText(i, 0);
			b_time = resultList.GetItemText(i, 1);
			b_departure = resultList.GetItemText(i, 2);
			b_seat_num = resultList.GetItemText(i, 4);
			query_test.Format(_T("Insert INTO project_bus(ID,DATE,TIME,DEPARTURE,SEAT) VALUES(\"%s\" ,\"%s\" ,\"%s\" ,\"%s\" ,\"%s\")"), ID, b_date, b_time, b_departure, b_seat_num);
			m_db.ExecuteSQL(query_test);
		}

		//m_db.ExecuteSQL(_T("UPDATE testtable SET id2=7 WHERE id1 = 2"));
		//m_db.ExecuteSQL(_T("DELETE FROM testtable WHERE id1 < 2"));
		MessageBox(L"예매가 완료되었습니다", L"알림", MB_OK);
		seat_check = ~(seat_check);
		resultList.DeleteAllItems();
	}

	catch (CException* e) {
		MessageBox(L"예상치 못한 오류로 예매에 실패하였습니다. 다시 시도해 주세요", L"알림", MB_OK);
		
		e->ReportError();
	}
	m_db.CommitTrans();
	
	buslistview();
	//seat_check = ~(seat_check);
	st:;
}


void CbusView::totalfeeprint() //총 요금 값 출력 함수
{
	int totalfee = 0;

	for (int i = 0; i < resultList.GetItemCount(); i++)
	{
		totalfee += _ttoi(resultList.GetItemText(i, 3));
	}
	CString fstr;
	fstr.Format(L"총 금액:%d,000", totalfee);
	resultlistbox.ResetContent();
	resultlistbox.AddString(fstr);
}


void CbusView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CFormView::OnPaint()을(를) 호출하지 마십시오.

	
}

void CbusView::managercheck()
{
	if (IDcheck == true) //사용자가 관리자인지 구별 해서 화면 출력
	{
		//MessageBox(ID, L"알림", MB_OK | MB_ICONERROR);

		CString b_que;
		CString info;
		int num;

		if (bopen)
			m_prs = new CRecordset(&m_db);
		b_que.Format(_T("SELECT admin FROM project_busid where ID=\"%s\""), ID);
		m_prs->Open(CRecordset::snapshot, b_que);
		{
			int row = 1;
			BOOL beof = m_prs->IsEOF();
			DWORD dwsize = m_prs->GetRowsetSize();

			if (!beof) {
				for (m_prs->MoveFirst(); !m_prs->IsEOF(); m_prs->MoveNext()) {
					int fieldc = m_prs->GetODBCFieldCount();

					for (int i = 0; i < fieldc; i++) {

						m_prs->SetAbsolutePosition(row);
						m_prs->GetFieldValue(i, info);
						num = _ttoi(info);
					}
					row++;
				}
			}
		}
		m_prs->Close();
		if (IDcheck == true && admin_check == TRUE) ///관리자 모드 작성
		{
			MessageBox(L"관리자 모드", L"알림", MB_OK | MB_ICONERROR);
			if (mmode == NULL)
			{
				mmode = new managermode;
				mmode->view = this;
				mmode->Create(IDD_DIALOG7);
				mmode->ShowWindow(SW_SHOW);
			}
			else
			{
				mmode->SetFocus();
			}
		}

	}
}

void CbusView::On32771()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	IDcheck = false;
	//mmode = new managermode;
	//mmode->DestroyWindow();
	//mmode->Destroy();
	///mmode = NULL;
//	ShowWindow(SW_SHOWMINIMIZED);
//	PostMessage(WM_SHOWWINDOW, FALSE, SW_OTHERUNZOOM);
	if (admin_check == true)
	{
		MessageBox(L"관리자 모드에서는 로그아웃이 안됩니다!", L"알림", MB_OK );
		return;
	}
	if (IDcheck == false) ///로그인 화면 출력
	{
		logg = new login;
		logg->DoModal();
		ID = (logg->ID);
		IDcheck = (logg->IDcheck);
		admin_check = (logg->am);
		//MessageBox(ID, L"알림", MB_OK | MB_ICONERROR);
		managercheck();
	}

}
