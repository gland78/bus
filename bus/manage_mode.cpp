// manage_mode.cpp: 구현 파일
//

#include "pch.h"
#include "bus.h"
#include "afxdialogex.h"
#include "manage_mode.h"


// manage_mode 대화 상자

IMPLEMENT_DYNAMIC(manage_mode, CDialogEx)

manage_mode::manage_mode(CWnd* pParent /*=nullptr*/)
	: CDialogEx(MANAGE_MODE, pParent)
{

}

manage_mode::~manage_mode()
{
}

void manage_mode::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(manage_mode, CDialogEx)
END_MESSAGE_MAP()


// manage_mode 메시지 처리기
