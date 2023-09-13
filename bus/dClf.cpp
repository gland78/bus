// dClf.cpp: 구현 파일
//

#include "pch.h"
#include "bus.h"
#include "afxdialogex.h"
#include "dClf.h"

#include "busDoc.h"
#include "busView.h"
// dClf 대화 상자

IMPLEMENT_DYNAMIC(dClf, CDialogEx)

dClf::dClf(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

dClf::~dClf()
{
}

void dClf::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, clfBusList);
}


BEGIN_MESSAGE_MAP(dClf, CDialogEx)
	ON_BN_CLICKED(IDOK, &dClf::OnBnClickedOk)
END_MESSAGE_MAP()


// dClf 메시지 처리기


void dClf::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CDialogEx::PostNcDestroy();
	view->departure = NULL;
	
	delete this;
}


void dClf::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnOK();
	DestroyWindow();
}
