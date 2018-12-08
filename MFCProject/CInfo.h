#pragma once


// CInfo 대화 상자

class CInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CInfo)

public:
	CInfo(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CInfo();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
//	CString m_strEmail;
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
//	CString m_strMailAddr;
//	CString m_strPw;
	afx_msg void OnBnClickedButtonStart();
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
