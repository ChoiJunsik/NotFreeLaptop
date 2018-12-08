
// MFCProjectDlg.h: 헤더 파일
//

#pragma once
#include "CInfo.h"
#include "CSetting.h"
#include "afxwin.h"
#include <Windows.h>
#include <ShlObj.h>
#include <afxinet.h>
#include <string>
// CMFCProjectDlg 대화 상자
class CMFCProjectDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCProjectDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCPROJECT_DIALOG };
#endif

	CSetting c_Setting;
	CInfo c_Info;
	CWnd* c_pWnd;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_MainTab;
	afx_msg void OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult);
	CStatic m_picture;
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	VideoCapture *capture;
	Mat mat_frame;
	int style;
	CRect _originWindow;
	time_t     tm_st;
	time_t     tm_nd;
	int        tm_day, tm_hour, tm_min, tm_sec;
	double     d_diff;
	bool onOff = false;
	int prevTime;
	struct tm  user_stime;
	CString Email;
	CString EmailAdr;
	CString Pw;
	int hour;
	int min;
	bool timerCheck = false;
	bool loginCheck = false;
	int pwMiss=0;
	int totalHour=0;
	bool checkedAlert;
	bool checkedCharge;
	bool checkedTimer;
	bool checkedFace;
	bool checkedChargingAction = false;
	CImage cimage_mfc;
	void Fullscreen();
//	afx_msg void OnChangeEditPasswordInput();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void CatchBadGuy();
};
