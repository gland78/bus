// seat_Sel.cpp: 구현 파일
//

#include "pch.h"
#include "bus.h"
#include "afxdialogex.h"
#include "seat_Sel.h"


#include "busDoc.h"
#include "busView.h"
// seat_Sel 대화 상자

IMPLEMENT_DYNAMIC(seat_Sel, CDialogEx)

seat_Sel::seat_Sel(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

seat_Sel::~seat_Sel()
{
}

void seat_Sel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}


BEGIN_MESSAGE_MAP(seat_Sel, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &seat_Sel::OnBnClickedCancel)
	ON_WM_PAINT()
	//ON_BN_CLICKED(IDC_CHECK_12, &seat_Sel::OnBnClickedCheck12)
	ON_BN_CLICKED(IDC_BACK, &seat_Sel::OnBnClickedBack)
END_MESSAGE_MAP()


// seat_Sel 메시지 처리기


void seat_Sel::OnBnClickedCancel() //선택 버튼
{
	CDialogEx::OnCancel();
	DestroyWindow();
	//// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//for (int i = 1; i < 23; i++)
	//{
	//	if (checkbox(i)) //check 확인
	//	{
	//		CString str;
	//		str.Format(L"%d", i);
	//		for (int j = 0; j < view->resultList.GetItemCount(); j++) //result list에 중복된 값이 있는지 확인
	//		{
	//			if (str == view->resultList.GetItemText(j, 4)) //중복된 값이 있을 때
	//			{
	//				CString sstr;
	//				sstr.Format(L"%s번 좌석이 중복입니다.", str);
	//				MessageBox(sstr, L"알림", MB_OK | MB_ICONERROR);
	//				goto st;
	//			}
	//		}
	//		view->resultList.InsertItem(0, view->busList.GetItemText(listnumber, 0));
	//		view->resultList.SetItemText(0, 1, view->busList.GetItemText(listnumber, 1));
	//		view->resultList.SetItemText(0, 2, view->busList.GetItemText(listnumber, 2));
	//		view->resultList.SetItemText(0, 3, view->busList.GetItemText(listnumber, 3));
	//		view->resultList.SetItemText(0, 4, str);
	//		view->seat_check = ~(view->seat_check);
	//		st:;
	//	}
	//}
	//view->totalfeeprint();

	////CDialogEx::OnCancel();
	//DestroyWindow();
}


void seat_Sel::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::PostNcDestroy();
	view->seat = NULL;

	delete this;
}


void seat_Sel::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

//	for(int i=1; i<23; i++)
//		activate(i);
}

///check box 비확성화 시키는 함수
void seat_Sel::activate(int num)  
{
	if(num==1)
		GetDlgItem(IDC_CHECK_1)->EnableWindow(FALSE);
	if (num == 2)
		GetDlgItem(IDC_CHECK_2)->EnableWindow(FALSE);
	if (num == 3)
		GetDlgItem(IDC_CHECK_3)->EnableWindow(FALSE);
	if (num == 4)
		GetDlgItem(IDC_CHECK_4)->EnableWindow(FALSE);
	if (num == 5)
		GetDlgItem(IDC_CHECK_5)->EnableWindow(FALSE);
	if (num == 6)
		GetDlgItem(IDC_CHECK_6)->EnableWindow(FALSE);
	if (num == 7)
		GetDlgItem(IDC_CHECK_7)->EnableWindow(FALSE);
	if (num == 8)
		GetDlgItem(IDC_CHECK_8)->EnableWindow(FALSE);
	if (num == 9)
		GetDlgItem(IDC_CHECK_9)->EnableWindow(FALSE);
	if (num == 10)
		GetDlgItem(IDC_CHECK_10)->EnableWindow(FALSE);
	if (num == 11)
		GetDlgItem(IDC_CHECK_11)->EnableWindow(FALSE);
	if (num == 12)
		GetDlgItem(IDC_CHECK_12)->EnableWindow(FALSE); 
	if (num == 13)
		GetDlgItem(IDC_CHECK_13)->EnableWindow(FALSE);
	if (num == 14)
		GetDlgItem(IDC_CHECK_14)->EnableWindow(FALSE);
	if (num == 15)
		GetDlgItem(IDC_CHECK_15)->EnableWindow(FALSE);
	if (num == 16)
		GetDlgItem(IDC_CHECK_16)->EnableWindow(FALSE);
	if (num == 17)
		GetDlgItem(IDC_CHECK_17)->EnableWindow(FALSE);
	if (num == 18)
		GetDlgItem(IDC_CHECK_18)->EnableWindow(FALSE);
	if (num == 19)
		GetDlgItem(IDC_CHECK_19)->EnableWindow(FALSE);
	if (num == 20)
		GetDlgItem(IDC_CHECK_20)->EnableWindow(FALSE);
	if (num == 21)
		GetDlgItem(IDC_CHECK_21)->EnableWindow(FALSE);
	if (num == 22)
		GetDlgItem(IDC_CHECK_22)->EnableWindow(FALSE);
}


///check box check 확인(true false)
BOOL seat_Sel::checkbox(int num)
{
	if (num == 1)
		return ((CButton*)GetDlgItem(IDC_CHECK_1))->GetCheck();
	if (num == 2)
		return ((CButton*)GetDlgItem(IDC_CHECK_2))->GetCheck();
	if (num == 3)
		return ((CButton*)GetDlgItem(IDC_CHECK_3))->GetCheck();
	if (num == 4)
		return ((CButton*)GetDlgItem(IDC_CHECK_4))->GetCheck();
	if (num == 5)
		return ((CButton*)GetDlgItem(IDC_CHECK_5))->GetCheck();
	if (num == 6)
		return ((CButton*)GetDlgItem(IDC_CHECK_6))->GetCheck();
	if (num == 7)
		return ((CButton*)GetDlgItem(IDC_CHECK_7))->GetCheck();
	if (num == 8)
		return ((CButton*)GetDlgItem(IDC_CHECK_8))->GetCheck();
	if (num == 9)
		return ((CButton*)GetDlgItem(IDC_CHECK_9))->GetCheck();
	if (num == 10)
		return ((CButton*)GetDlgItem(IDC_CHECK_10))->GetCheck();
	if (num == 11)
		return ((CButton*)GetDlgItem(IDC_CHECK_11))->GetCheck();
	if (num == 12)
		return ((CButton*)GetDlgItem(IDC_CHECK_12))->GetCheck();
	if (num == 13)
		return ((CButton*)GetDlgItem(IDC_CHECK_13))->GetCheck();
	if (num == 14)
		return ((CButton*)GetDlgItem(IDC_CHECK_14))->GetCheck();
	if (num == 15)
		return ((CButton*)GetDlgItem(IDC_CHECK_15))->GetCheck();
	if (num == 16)
		return ((CButton*)GetDlgItem(IDC_CHECK_16))->GetCheck();
	if (num == 17)
		return ((CButton*)GetDlgItem(IDC_CHECK_17))->GetCheck();
	if (num == 18)
		return ((CButton*)GetDlgItem(IDC_CHECK_18))->GetCheck();
	if (num == 19)
		return ((CButton*)GetDlgItem(IDC_CHECK_19))->GetCheck();
	if (num == 20)
		return ((CButton*)GetDlgItem(IDC_CHECK_20))->GetCheck();
	if (num == 21)
		return ((CButton*)GetDlgItem(IDC_CHECK_21))->GetCheck();
	if (num == 22)
		return ((CButton*)GetDlgItem(IDC_CHECK_22))->GetCheck();
}


void seat_Sel::OnBnClickedBack()
{
	//CDialogEx::OnCancel();
	//DestroyWindow();
		// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	for (int i = 1; i < 23; i++)
	{
		if (checkbox(i)) //check 확인
		{
			CString str;
			str.Format(L"%d", i);
			for (int j = 0; j < view->resultList.GetItemCount(); j++) //result list에 중복된 값이 있는지 확인
			{
				if (str == view->resultList.GetItemText(j, 4)) //중복된 값이 있을 때
				{
					CString sstr;
					sstr.Format(L"%s번 좌석이 중복입니다.", str);
					MessageBox(sstr, L"알림", MB_OK | MB_ICONERROR);
					goto st;
				}
			}
			view->resultList.InsertItem(0, view->busList.GetItemText(listnumber, 0));
			view->resultList.SetItemText(0, 1, view->busList.GetItemText(listnumber, 1));
			view->resultList.SetItemText(0, 2, view->busList.GetItemText(listnumber, 2));
			view->resultList.SetItemText(0, 3, view->busList.GetItemText(listnumber, 3));
			view->resultList.SetItemText(0, 4, str);
			view->seat_check = ~(view->seat_check);
		st:;
		}
	}
	view->totalfeeprint();

	//CDialogEx::OnCancel();
	DestroyWindow();
}
