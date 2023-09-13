// login.cpp: 구현 파일
//

#include "pch.h"
#include "bus.h"
#include "afxdialogex.h"
#include "login.h"


#include "busDoc.h"
#include "busView.h"

#include "findID.h"
#include "findPW.h"
#include "signup.h"

// login 대화 상자

IMPLEMENT_DYNAMIC(login, CDialogEx)

login::login(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{
}

login::~login()
{
}

void login::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, idEdit);
	DDX_Control(pDX, IDC_EDIT2, pwEdit);

	IDcheck = false;
}


BEGIN_MESSAGE_MAP(login, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &login::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &login::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &login::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &login::OnBnClickedButton4)
	//ON_BN_CLICKED(ㅑ, &login::OnBnClickedLogin)
END_MESSAGE_MAP()


// login 메시지 처리기


void login::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString id, pw;
	idEdit.GetWindowTextW(id);
	pwEdit.GetWindowTextW(pw);

	bopen = m_db.OpenEx(_T("DSN=to_2020118023;SERVER=155.230.235.248;PORT=34056;UID=2020118023;PWD=2020118023;DATABASE=s2020118023;"), CDatabase::noOdbcDialog);
	if (bopen)
		m_prs = new CRecordset(&m_db);

	CString b_que;
	b_que.Format(_T("SELECT ID, admin FROM project_busid where ID=\"%s\" and PW=\"%s\""), id, pw);  // 의심2
	
	m_prs->Open(CRecordset::snapshot, b_que);
	{
		int row = 1;
		BOOL beof = m_prs->IsEOF();
		DWORD dwsize = m_prs->GetRowsetSize();

		CString id;
		CString admin;

		if (!beof) {
			for (m_prs->MoveFirst(); !m_prs->IsEOF(); m_prs->MoveNext()) {
				int fieldc = m_prs->GetODBCFieldCount();
					m_prs->SetAbsolutePosition(row);
					m_prs->GetFieldValue(short(0),id);
					m_prs->GetFieldValue(short(1), admin);

					//MessageBox(id, L"알림", MB_OK);
					//MessageBox(admin, L"알림", MB_OK);

					am = _ttoi(admin);
					ID = id;
					IDcheck = true;
					row++;
			}
		}
	}
	m_prs->Close();
	m_db.Close();

	if (ID.IsEmpty() || pw.IsEmpty()) {
		MessageBox(L"ID, PW가 올바르지 않습니다", L"알림", MB_OK);
		return;
	}
	CDialogEx::OnCancel();
}


void login::OnBnClickedButton2()  // ID 찾기
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	findID dlg;
	dlg.DoModal();
}


void login::OnBnClickedButton3() // pw 찾기
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	findPW dlg;
	dlg.DoModal();

}


void login::OnBnClickedButton4() // 회원 가입
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	signup dlg;
	dlg.DoModal();

}


void login::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CDialogEx::PostNcDestroy();

	//view->logg = NULL;

	//delete this;
}


void login::OnCancel()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnCancel();
	int temp=MessageBox(L"정말 종료하시겠습니까?", L"알림", MB_YESNO | MB_ICONERROR);
	if (temp == IDYES)
	{
		CDialogEx::OnCancel();
		exit(0);
	}
	idEdit.SetFocus();

}