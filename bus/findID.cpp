// findID.cpp: 구현 파일
//

#include "pch.h"
#include "bus.h"
#include "afxdialogex.h"
#include "findID.h"

#include "busDoc.h"
#include "busView.h"

// findID 대화 상자

IMPLEMENT_DYNAMIC(findID, CDialogEx)

findID::findID(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
{

}

findID::~findID()
{
}

void findID::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, nameEdit);

	bopen = m_db.OpenEx(_T("DSN=to_2020118023;SERVER=155.230.235.248;PORT=34056;UID=2020118023;PWD=2020118023;DATABASE=s2020118023;"), CDatabase::noOdbcDialog);
}


BEGIN_MESSAGE_MAP(findID, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &findID::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &findID::OnBnClickedOk)
END_MESSAGE_MAP()


// findID 메시지 처리기


void findID::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString str;
	nameEdit.GetWindowTextW(str);

	if (str.IsEmpty())
	{
		MessageBox(L"이름을 입력하세요", L"알림", MB_OK);
	}

	if (bopen)
		m_prs = new CRecordset(&m_db);

	CString b_que;
	b_que.Format(_T("SELECT ID FROM project_busid where name=\"%s\""), str); // busid 의심1
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

					CString str1;  /// ID 값 출력
					str1.Format(L"ID:%s",info);
					MessageBox(str1, L"알림", MB_OK | MB_ICONERROR);
				}
				row++;
			}
		} 
	}
	m_prs->Close();
}


void findID::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}
