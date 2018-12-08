#pragma once


// CSetting 대화 상자

class CSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CSetting)

public:
	CSetting(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSetting();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bCheckAlarm;
	BOOL m_bCheckCharge;
	BOOL m_bCheckTimer;
	virtual BOOL OnInitDialog();
	UINT m_nTimerHour;
	UINT m_nTimerMinute;
	CSpinButtonCtrl m_spinTimerHour;
	CSpinButtonCtrl m_spinTimerMinute;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	BOOL m_checkedFace;
};
