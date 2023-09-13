// findPW.cpp: 구현 파일
//

#include "pch.h"
#include "bus.h"
#include "afxdialogex.h"
#include "findPW.h"


// findPW 대화 상자

IMPLEMENT_DYNAMIC(findPW, CDialogEx)

findPW::findPW(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG5, pParent)
{

}

findPW::~findPW()
{
}

void findPW::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, idEdit);


	bopen = m_db.OpenEx(_T("DSN=to_2020118023;SERVER=155.230.235.248;PORT=34056;UID=2020118023;PWD=2020118023;DATABASE=s2020118023;"), CDatabase::noOdbcDialog);
	DDX_Control(pDX, IDC_EDIT2, name_edit);
}


BEGIN_MESSAGE_MAP(findPW, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &findPW::OnBnClickedButton1)
END_MESSAGE_MAP()


// findPW 메시지 처리기


void findPW::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString str,str2;
	idEdit.GetWindowTextW(str);
	name_edit.GetWindowTextW(str2);

	if (bopen)
		m_prs = new CRecordset(&m_db);

	if (str.IsEmpty() || str2.IsEmpty())
	{
		MessageBox(L"ID나 이름 중 올바르지 않은 정보를 입력했습니다.", L"알림", MB_OK);
	}

	CString b_que;
	b_que.Format(_T("SELECT PW FROM s2020118023.project_busid where ID=\"%s\""), str); 
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
					str1.Format(L"PW:%s", info);
					MessageBox(str1, L"알림", MB_OK | MB_ICONERROR);
				}
				row++;
			}
		}
	}
	m_prs->Close();

}
