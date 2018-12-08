// CSetting.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFCProject.h"
#include "CSetting.h"
#include "afxdialogex.h"


// CSetting 대화 상자

IMPLEMENT_DYNAMIC(CSetting, CDialogEx)

CSetting::CSetting(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SETTING, pParent)
	, m_bCheckAlarm(FALSE)
	, m_bCheckCharge(FALSE)
	, m_bCheckTimer(FALSE)
	, m_nTimerHour(0)
	, m_nTimerMinute(0)
	, m_checkedFace(FALSE)
{

}

CSetting::~CSetting()
{
}

void CSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_ALARM, m_bCheckAlarm);
	DDX_Check(pDX, IDC_CHECK_CHARGE, m_bCheckCharge);
	DDX_Check(pDX, IDC_CHECK_TIMER, m_bCheckTimer);
	DDX_Text(pDX, IDC_EDIT_TIMER_HOUR, m_nTimerHour);
	DDV_MinMaxUInt(pDX, m_nTimerHour, 0, 23);
	DDX_Text(pDX, IDC_EDIT_TIMER_MINUTE, m_nTimerMinute);
	DDV_MinMaxUInt(pDX, m_nTimerMinute, 0, 59);
	DDX_Control(pDX, IDC_SPIN_TIMER_HOUR, m_spinTimerHour);
	DDX_Control(pDX, IDC_SPIN_TIMER_MINUTE, m_spinTimerMinute);
	DDX_Check(pDX, IDC_CHECK_FACE, m_checkedFace);
}


BEGIN_MESSAGE_MAP(CSetting, CDialogEx)
//	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_TIMER_HOUR, &CSetting::OnDeltaposSpinTimerHour)
END_MESSAGE_MAP()


// CSetting 메시지 처리기


BOOL CSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	//체크박스 초기화
	((CButton*)GetDlgItem(IDC_CHECK_ALARM))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_CHECK_FACE))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_CHECK_TIMER))->SetCheck(TRUE);

	m_bCheckAlarm = true;
	m_bCheckTimer = true;
	m_bCheckCharge = false;

	m_spinTimerHour.SetRange(0, 23);
	m_spinTimerMinute.SetRange(0, 59);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


//void CSetting::OnDeltaposSpinTimerHour(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	*pResult = 0;
//}




BOOL CSetting::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_MENU || pMsg->wParam == VK_F4 || pMsg->wParam == VK_CONTROL || pMsg->wParam == VK_DELETE) return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}


