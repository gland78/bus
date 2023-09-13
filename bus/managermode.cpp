// managermode.cpp: 구현 파일
//

#include "pch.h"
#include "bus.h"
#include "afxdialogex.h"
#include "managermode.h"


#include "busDoc.h"
#include "busView.h"

// managermode 대화 상자

IMPLEMENT_DYNAMIC(managermode, CDialogEx)

managermode::managermode(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG7, pParent)
{

}

managermode::~managermode()
{
	m_db.Close();
}

void managermode::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, DBList);
	//DDX_Control(pDX, IDC_LIST4, DBList);
	DDX_Control(pDX, IDC_LIST4, Filter_DBList);

	

}

BOOL managermode::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	DBList.InsertColumn(0, L"ID", LVCFMT_LEFT, 60);
	//DBList.InsertColumn(1, L"PW", LVCFMT_LEFT, 45);
	//DBList.InsertColumn(2, L"PW", LVCFMT_LEFT, 60);
	DBList.InsertColumn(2, L"이름", LVCFMT_LEFT, 55);
	//DBList.InsertColumn(4, L"좌석", LVCFMT_LEFT, 50);
	Filter_DBList.InsertColumn(0, L"이름", LVCFMT_LEFT, 60);
	Filter_DBList.InsertColumn(1, L"날짜", LVCFMT_LEFT, 45);
	Filter_DBList.InsertColumn(2, L"시간", LVCFMT_LEFT, 45);
	Filter_DBList.InsertColumn(3, L"목적지", LVCFMT_LEFT, 55);
	Filter_DBList.InsertColumn(4, L"좌석", LVCFMT_LEFT, 50);

	BOOL bopen = m_db.OpenEx(_T("DSN=to_2020118023;SERVER=155.230.235.248;PORT=34056;UID=2020118023;PWD=2020118023;DATABASE=s2020118023;"), CDatabase::noOdbcDialog);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BEGIN_MESSAGE_MAP(managermode, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON5, &managermode::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON2, &managermode::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &managermode::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &managermode::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &managermode::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON3, &managermode::OnBnClickedButton3)
END_MESSAGE_MAP()


// managermode 메시지 처리기


void managermode::OnBnClickedButton5() //userlist 삭제
{
	CString ID;

	int count = DBList.GetItemCount(); //리스트 컨트롤의 현재 항목 수를 얻어옵니다.

	//CString ind;

	//bool* flag=new bool[]{false,};
	int temp;

	for (int i = count - 1; i >= 0; i--)   //모든 항목을 조사하여
	{
		if (DBList.GetItemState(i, LVIS_SELECTED) != 0) //선택된 항목을 삭제
		{
			ID = DBList.GetItemText(i, 0);
			//flag[i] = true;

			temp = i;
			//ind.Format(L"%d", i);
			//MessageBox(ind);

			CString qur;

			m_db.BeginTrans();
			try {
				qur.Format(_T("DELETE FROM project_bus where ID=\"%s\""), ID);
				m_db.ExecuteSQL(qur);
				DBList.DeleteItem(temp);

				/*	for (int i = count-1; i >= 0; i--)
					{
						if (flag[i])
						{
							DBList.DeleteItem(i);
						}
					}*/

			}
			catch (CException* e) {
				e->ReportError();
			}
			m_db.CommitTrans();
		}


	}




	//delete[] flag;
}


void managermode::OnBnClickedButton2() //buslist 삭제
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString ID, date, tm, seat, dp;

	//CString ind;


	//bool* flag = new bool[] {false,};

	int count = Filter_DBList.GetItemCount(); //리스트 컨트롤의 현재 항목 수를 얻어옵니다.
	int temp = count;
	for (int i = count - 1; i >= 0; i--)   //모든 항목을 조사하여
	{
		if (Filter_DBList.GetItemState(i, LVIS_SELECTED) != 0)
		{
			date = Filter_DBList.GetItemText(i, 1);
			tm = Filter_DBList.GetItemText(i, 2);
			dp = Filter_DBList.GetItemText(i, 3);
			seat = Filter_DBList.GetItemText(i, 4);

			//flag[i] = true;

			temp = i;
			//ind.Format(L"%d", i);
			//MessageBox(ind);

			CString qur;

			m_db.BeginTrans();
			try {

				qur.Format(_T("DELETE FROM project_bus where date=\"%s\" and seat=\"%s\" and time=\"%s\" and departure=\"%s\""), date, seat, tm, dp);
				//MessageBox(qur);
				m_db.ExecuteSQL(qur);

				if (0 <= temp <= count - 1 || count == 1)
					Filter_DBList.DeleteItem(temp);
					MessageBox(L"정상적으로 삭제 하였습니다!");
					//Filter_DBList.GetItem();
					
			}
			catch (CException* e) {
				e->ReportError();
				MessageBox(L"해당 ID를 가진 사용자의 예매 내역을 먼저 삭제해주세요");
			}
			m_db.CommitTrans();


			//delete[] flag;
		}

	}

}


void managermode::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	view->mmode = NULL;

	delete this;

	//CDialogEx::PostNcDestroy();
}


void managermode::OnBnClickedButton1() // busid DB 불러오기
{
	DBList.DeleteAllItems();
	if (bopen)
		m_prs = new CRecordset(&m_db);

	CString str = _T("");
	//select ID, `name` from project_busid
	m_prs->Open(CRecordset::snapshot, _T("SELECT ID, name FROM project_busid where admin=FALSE"));
	{
		int row = 1;
		BOOL beof = m_prs->IsEOF();
		DWORD dwsize = m_prs->GetRowsetSize();

		CString query_test;
		CString ID, NAME;

		if (!beof) {

			for (m_prs->MoveFirst(); !m_prs->IsEOF(); m_prs->MoveNext()) { // 여기가 맹 전체 리드.
				int fieldc = m_prs->GetODBCFieldCount();

				m_prs->SetAbsolutePosition(row);
				m_prs->GetFieldValue(short(0), ID);
				m_prs->GetFieldValue(short(1), NAME);

				DBList.InsertItem(0, ID);
				DBList.SetItemText(0, 1, NAME);

				row++;
			} // for m_prs
		} // if 
		m_prs->Close();
	}
}


void managermode::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void managermode::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


void managermode::OnBnClickedButton3() // 관리자 DB에서 선택한 대상.
{
	Filter_DBList.DeleteAllItems();

	int count = DBList.GetItemCount(); //리스트 컨트롤의 현재 항목 수를 얻어옵니다.
	int number = 0; //선택된 위치 저장

	for (int i = count; i >= 0; i--)   //모든 항목을 조사하여
		if (DBList.GetItemState(i, LVIS_SELECTED) != 0) //선택된 항목
			number = i;

	if (count == 0) //선택 했는지 확인 하는 함수
	{
		MessageBox(L"사람부터 고르시오!", L"알림", MB_OK | MB_ICONERROR);
		return;
	}
	CString select_name = DBList.GetItemText(number, 0);

	AfxMessageBox(select_name + L"에 접근합니다.");
	//AfxMessageBox(select_name);



	CString str = _T("");
	CString search_T;
	search_T.Format(_T("SELECT * FROM project_bus where ID = \"%s\""), select_name);
	m_prs->Open(CRecordset::snapshot, search_T);
	{
		int row = 1;
		BOOL beof = m_prs->IsEOF();
		DWORD dwsize = m_prs->GetRowsetSize();

		CString query_test;
		CString ID, NAME;

		if (!beof) {

			for (m_prs->MoveFirst(); !m_prs->IsEOF(); m_prs->MoveNext()) { // 여기가 맹 전체 리드.
				int fieldc = m_prs->GetODBCFieldCount();
				CString info;
				m_prs->SetAbsolutePosition(row);

				for (int i = 0; i < fieldc; i++) {			// 한 필드 기준으로 읽기...
					CString info;
					m_prs->SetAbsolutePosition(row);
					m_prs->GetFieldValue(i, info);

					if (LKER == 0) {	// 처음엔 공백이 나옴으로 넘어가야 된다.
						Filter_DBList.InsertItem(0, info);
						LKER++;
						continue;
					}
					else if (LKER == 1) {	// 날짜					
						Filter_DBList.SetItemText(0, 1, info);
						LKER++;
					}
					else if (LKER == 2) {	// 시간
						Filter_DBList.SetItemText(0, 2, info);
						LKER++;
					}
					else if (LKER == 3) {	// 목적지
						Filter_DBList.SetItemText(0, 3, info);
						LKER++;
					}
					else if (LKER == 4) {	// 좌석 + 전부 다 돌았으니 초기화 해야됨.
						Filter_DBList.SetItemText(0, 4, info);
						LKER = 0;
					}
				} // for i
				row++;
			} // for m_prs



		} // if 

		//AfxMessageBox(str);
		m_prs->Close();
	}


	//else if (number == 0)
	//{
	//	MessageBox(L"시간를 선택해 주세요!", L"알림", MB_OK | MB_ICONERROR);
	//	return;
	//}

	//if (seat == NULL)
	//{
	//	seat = new seat_Sel;
	//	seat->view = this;
	//	seat->Create(IDD_DIALOG2);
	//	seat->ShowWindow(SW_SHOW);
	//	seat->listnumber = number;

	//	/*
	//	CString str;
	//	str.Format(L"%s", busList.GetItemText(number, 0));
	//	MessageBox(str, L"알림", MB_OK | MB_ICONERROR);
	//	*/

	//	CString datestr = busList.GetItemText(number, 0);
	//	CString time = busList.GetItemText(number, 1);
	//	CString area = busList.GetItemText(number, 2);
	//	CString b_que;
	//	b_que.Format(_T("SELECT seat FROM project_bus where date=\"%s\" and time = \"%s\" and departure=\"%s\""), datestr, time, area);
	//	//AfxMessageBox(b_que);
	//	m_prs->Open(CRecordset::snapshot, b_que);
	//	{
	//		int row = 1;
	//		BOOL beof = m_prs->IsEOF();
	//		DWORD dwsize = m_prs->GetRowsetSize();

	//		if (!beof) {
	//			for (m_prs->MoveFirst(); !m_prs->IsEOF(); m_prs->MoveNext()) {
	//				int fieldc = m_prs->GetODBCFieldCount();

	//				for (int i = 0; i < fieldc; i++) {
	//					CString info;
	//					m_prs->SetAbsolutePosition(row);
	//					m_prs->GetFieldValue(i, info);

	//					int data = _ttoi(info);
	//					seat->activate(data);  //이미 있는 좌석 비활성화

	//				}

	//				//str += "\n";
	//				row++;
	//			} // for m_prs
	//		} // if 
	//	}
	//	m_prs->Close();


	//}
	//else
	//{
	//	seat->SetFocus();

	//	seat->Invalidate();
	//}
}



/// 이것이 지워졌다면 더 이상 수정할 필요가 없습니다!

