// signup.cpp: 구현 파일
//

#include "pch.h"
#include "bus.h"
#include "afxdialogex.h"
#include "signup.h"


// signup 대화 상자

IMPLEMENT_DYNAMIC(signup, CDialogEx)

signup::signup(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG6, pParent)
	, m_radio_index(0) //소스 파일에서 방금 생성한 변수를 초기화 해준다. 
	, admin_check(TRUE)
{
}

signup::~signup()
{
}

void signup::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, nameEdit);
	DDX_Control(pDX, IDC_EDIT2, idEdit);
	DDX_Control(pDX, IDC_EDIT3, pwEdit);

	DDX_Radio(pDX, IDC_RADIO1, (int&)m_radio_index);

	check = false; /// id 중복 버튼 눌렀는지 확인
	pw_check = false; //비밀번호 확인버튼 눌렀는지 검사

	bopen = false;

	
	DDX_Control(pDX, IDC_EDIT4, pw_contrast);//DoDataExchange 에서 라디오 버튼의 ID와 선언한 변수 사이를 연결해준다.

}


BEGIN_MESSAGE_MAP(signup, CDialogEx)
	ON_BN_CLICKED(IDOK, &signup::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON2, &signup::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &signup::OnBnClickedButton3)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO1, IDC_RADIO2, &signup::RadioCtrl) //라디오 버튼이 하나의 컨트롤 범위 안에 있다고 알려 준다.트롤 범위
END_MESSAGE_MAP()


// signup 메시지 처리기


void signup::OnBnClickedOk()  //확인 버튼
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (check == false) ///id 중복 버튼 눌렀는지 확인
	{
		MessageBox(L"중복 확인 버튼을 눌러 주세요!", L"알림", MB_OK | MB_ICONERROR);
		return;
	}
	else if (pw_check == false)
	{
		MessageBox(L"비밀번호 확인 버튼을 눌러 주세요!", L"알림", MB_OK | MB_ICONERROR);
		return;
	}

	//if(admin_check.GetCheck)
	


	CString name, id, pw;

	nameEdit.GetWindowTextW(name);
	idEdit.GetWindowTextW(id);
	pwEdit.GetWindowTextW(pw);

	if (name.IsEmpty())
	{
		MessageBox(L"이름을 입력하세요!", L"알림", MB_OK);
		nameEdit.SetFocus();
		return;
	}

		
	bopen = m_db.OpenEx(_T("DSN=to_2020118023;SERVER=155.230.235.248;PORT=34056;UID=2020118023;PWD=2020118023;DATABASE=s2020118023;"), CDatabase::noOdbcDialog);

	if (bopen)
		m_prs = new CRecordset(&m_db);
	CString query_test;

	m_db.BeginTrans();
	try {

		query_test.Format(_T("Insert INTO s2020118023.project_busid(ID, name, pw, admin) VALUES(\"%s\" ,\"%s\" ,\"%s\" ,\"%d\");"), id, name, pw,admin_check);
		//MessageBox(query_test, L"알림", MB_OK);
		m_db.ExecuteSQL(query_test);

		
		MessageBox(L"회원가입이 완료되었습니다!", L"알림", MB_OK);
	}

	catch (CException* e) {
		MessageBox(L"예기치 못한 오류로 회원가입이 취소되었습니다", L"알림", MB_OK);
		e->ReportError();

	}
	m_db.CommitTrans();
	m_db.Close();

	CDialogEx::OnOK();
	DestroyWindow();
}


void signup::OnBnClickedButton2()  //중복 확인 버튼
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString id;
	idEdit.GetWindowTextW(id);
	if (id.IsEmpty())
	{
		MessageBox(L"ID를 입력하세요!", L"알림", MB_OK);
		idEdit.SetFocus();
		return;
	}

	if(!bopen)
		bopen = m_db.OpenEx(_T("DSN=to_2020118023;SERVER=155.230.235.248;PORT=34056;UID=2020118023;PWD=2020118023;DATABASE=s2020118023;"), CDatabase::noOdbcDialog);
	if (bopen)
		m_prs = new CRecordset(&m_db);
	CString b_que;

	b_que.Format(_T("SELECT ID FROM s2020118023.project_busid where ID=\"%s\""), id);

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

				/*	CString inde;
					inde.Format(L"%d", i);
					MessageBox(inde, L"알림", MB_OK);*/

					MessageBox(L"ID가 중복입니다!", L"알림", MB_OK);
					return;
				}
				row++;
			} 
		}
	}
	m_prs->Close();

	m_db.Close();

	MessageBox(L"ID가 중복이 아닙니다!", L"알림", MB_OK);
	check = true;
}


void signup::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString pw, contrast;
	pwEdit.GetWindowTextW(pw);
	pw_contrast.GetWindowTextW(contrast);

	if (pw.IsEmpty() || contrast.IsEmpty())
	{
		return;
	}

	if (!pw.Compare(contrast))
	{
		int temp=MessageBox(L"비밀번호가 일치합니다. 사용하시겠습니까?", L"알림", MB_YESNO | MB_ICONERROR);
		if (temp == IDYES)
		{
			pwEdit.EnableWindow(FALSE);
			pw_contrast.EnableWindow(FALSE);
			pw_check = true;
		}
		else
		{
			pwEdit.Clear();
			pw_contrast.Clear();
			pwEdit.SetFocus();
		}
	}
	else
	{
		MessageBox(L"비밀번호가 불일치합니다! 다시 입력하세요", L"알림", MB_OK | MB_ICONERROR);
		pwEdit.Clear();
		pw_contrast.Clear();
		pwEdit.SetFocus();
	}
}

void signup::RadioCtrl(UINT id)
{
	UpdateData(TRUE);
	switch (id)
	{
	case IDC_RADIO1:
		admin_check = TRUE;
		break;
	case IDC_RADIO2:
		admin_check = FALSE;
		break;
	}
}