// CInfo.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFCProject.h"
#include "CInfo.h"
#include "afxdialogex.h"
#include "MFCProjectDlg.h"
#include "Crypt.h"
#include <time.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <iosfwd>
using namespace std;
// CInfo 대화 상자

IMPLEMENT_DYNAMIC(CInfo, CDialogEx)

CInfo::CInfo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_INFO, pParent)
{

}

CInfo::~CInfo()
{
}

void CInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInfo, CDialogEx)
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_BUTTON_START, &CInfo::OnBnClickedButtonStart)
END_MESSAGE_MAP()


// CInfo 메시지 처리기


void CInfo::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDCtl == IDC_BUTTON_START)
	{
		CDC dc;
		RECT rect;
		dc.Attach(lpDrawItemStruct->hDC);   // 버튼의 dc구하기

		rect = lpDrawItemStruct->rcItem;     // 버튼영역 구하기
		dc.Draw3dRect(&rect, RGB(255, 255, 255), RGB(0, 0, 0)); //버튼 외곽선 그리기
		dc.FillSolidRect(&rect, RGB(220, 20, 60));// 버튼 색상

		UINT state = lpDrawItemStruct->itemState;  // 버튼 상태구하기 
		if ((state & ODS_SELECTED))
			dc.DrawEdge(&rect, EDGE_SUNKEN, BF_RECT);
		else
			dc.DrawEdge(&rect, EDGE_RAISED, BF_RECT);

		dc.SetBkColor(RGB(220, 20, 60));   // 텍스트 백그라운드 색상
		dc.SetTextColor(RGB(255, 255, 255));     // 텍스트 색상

		TCHAR buffer[MAX_PATH];           //버튼의 텍스트를 얻기위한 임시버퍼
		ZeroMemory(buffer, MAX_PATH);     // 버퍼초기화
		::GetWindowText(lpDrawItemStruct->hwndItem, buffer, MAX_PATH); //버튼의 텍스트얻기 

		dc.DrawText(buffer, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//버튼의 텍스트 넣기 
		dc.Detach();  // 버튼의 dc풀어주기
	}

	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}


void CInfo::OnBnClickedButtonStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMFCProjectDlg* dlg=(CMFCProjectDlg*)AfxGetMainWnd();
	dlg->Fullscreen();
	dlg->loginCheck = true;
	dlg->checkedAlert = (dlg->c_Setting).IsDlgButtonChecked(IDC_CHECK_ALARM) ? TRUE : FALSE;
	dlg->checkedCharge = (dlg->c_Setting).IsDlgButtonChecked(IDC_CHECK_CHARGE) ? TRUE : FALSE;
	dlg->checkedTimer = (dlg->c_Setting).IsDlgButtonChecked(IDC_CHECK_TIMER) ? TRUE : FALSE;
	dlg->checkedFace = (dlg->c_Setting).IsDlgButtonChecked(IDC_CHECK_FACE) ? TRUE : FALSE;

	GetDlgItemText(IDC_EDIT_EMAIL, dlg->Email);
	GetDlgItemText(IDC_COMBO_MAILADDR, dlg->EmailAdr);
	GetDlgItemText(IDC_EDIT_SET_PASSWORD, dlg->Pw);
	BOOL trans = FALSE;

	dlg->hour=(dlg->c_Setting).GetDlgItemInt(IDC_EDIT_TIMER_HOUR, &trans);
	dlg->min=(dlg->c_Setting).GetDlgItemInt(IDC_EDIT_TIMER_MINUTE, &trans);

	dlg->checkedTimer = (dlg->c_Setting).IsDlgButtonChecked(IDC_CHECK_TIMER) ? TRUE : FALSE;
	if (dlg->checkedTimer) {
	}
	else {
		dlg->totalHour = INT_MAX;
	}

	(dlg->totalHour) += dlg->hour * 3600;
	(dlg->totalHour) += dlg->min*60;
	dlg->Email += "@";
	dlg->Email += dlg->EmailAdr;

	
	char gmail[30];
	char pw[30];
	bool onOff = false;
	time_t tm_st;
	time(&tm_st);
	dlg->prevTime = dlg->tm_st = tm_st;
	int prevTime=tm_st;

	strcpy_s(gmail, CStringA(dlg->Email).GetString());
	strcpy_s(pw, CStringA(dlg->Pw).GetString());
	Encrypt(gmail, gmail,30);
	Encrypt(pw, pw, 30);
	
	ofstream output("C:\\log", ios::out | ios::binary);
	output.write((char*)&onOff, sizeof(bool));
	output.write((char*)&prevTime, sizeof(int));
	output.write((char*)&dlg->totalHour, sizeof(int));
	output.write((char*)&gmail, 30);
	output.write((char*)&pw, 30);
	output.close();
}



BOOL CInfo::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE) return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}
