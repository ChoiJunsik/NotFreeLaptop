
// MFCProjectDlg.cpp: 구현 파일
//
#pragma comment(lib, "winmm")

#include "stdafx.h"
#include "MFCProject.h"
#include "MFCProjectDlg.h"
#include "afxdialogex.h"
#include "easendmailobj.tlh" //헤더 라이브러리 이거 분석 필요함
#include <mmsystem.h>
#include "Crypt.h"
#include <time.h>
#include <fstream>
#include <string.h>
#include <iostream>

using namespace EASendMailObjLib;
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCProjectDlg 대화 상자



CMFCProjectDlg::CMFCProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCPROJECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	c_pWnd = NULL;
}

void CMFCProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_MAIN, m_MainTab);
	DDX_Control(pDX, IDC_PICTURE, m_picture);
}

BEGIN_MESSAGE_MAP(CMFCProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CMFCProjectDlg::OnTcnSelchangeTabMain)
	ON_WM_DESTROY()
	ON_WM_TIMER()
//	ON_EN_CHANGE(IDC_EDIT_PASSWORD_INPUT, &CMFCProjectDlg::OnChangeEditPasswordInput)
END_MESSAGE_MAP()


// CMFCProjectDlg 메시지 처리기

BOOL CMFCProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_MainTab.InsertItem(1, _T("설정"));
	m_MainTab.InsertItem(2, _T("정보"));
	style = ::GetWindowLong(this->m_hWnd, GWL_STYLE);
	::GetWindowRect(this->m_hWnd, &_originWindow);

	CRect rt;
	m_MainTab.GetClientRect(&rt);

	c_Setting.Create(IDD_DIALOG_SETTING, &m_MainTab);
	c_Setting.SetWindowPos(NULL, 4, 25, rt.Width() - 10, rt.Height() - 30, SWP_SHOWWINDOW | SWP_NOZORDER);
	c_pWnd = &c_Setting;

	c_Info.Create(IDD_DIALOG_INFO, &m_MainTab);
	c_Info.SetWindowPos(NULL, 4, 25, rt.Width() - 10, rt.Height() - 30, SWP_NOZORDER);


	capture = new VideoCapture(0);
	if (!capture->isOpened())
	{
		MessageBox(_T("캠을 열수 없습니다. \n"));
	}

	//웹캠 크기를  320x240으로 지정    
	capture->set(CAP_PROP_FRAME_WIDTH, 480);
	capture->set(CAP_PROP_FRAME_HEIGHT, 320);

	int totalHour2;
	char gmail2[30];
	char pw2[30];
	bool onOff2;
	ifstream input("C:\\log", ios::in | ios::binary);
	if (input.is_open()) {
		input.read((char*)&onOff2, sizeof(bool));
		input.read((char*)&prevTime, sizeof(int));
		input.read((char*)&totalHour2, sizeof(int));
		input.read((char*)&gmail2, 30);
		input.read((char*)&pw2, 30);
		input.close();

		tm_st = prevTime;
		time(&tm_nd);
		d_diff = difftime(tm_nd, tm_st);

		Decrypt(gmail2, gmail2, 30);
		Decrypt(pw2, pw2, 30);

		Email = gmail2;
		Pw = pw2;
		if (d_diff > totalHour2) {

			onOff = true;

			input.close();
			SetTimer(1000, 5, NULL);


			Fullscreen();
			CatchBadGuy();
		}
		else if (onOff2) {

			onOff = onOff2;
			
			input.close();
			SetTimer(1000, 5, NULL);


			Fullscreen();
			CatchBadGuy();
		}
		else
		{
			
			input.close();
			SetTimer(1000, 5, NULL);

		}
	}
	else
	{
		input.close();
		SetTimer(1000, 5, NULL);

	}
	
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCProjectDlg::OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (c_pWnd != NULL)
	{
		c_pWnd->ShowWindow(SW_HIDE);
		c_pWnd = NULL;
	}

	int index = m_MainTab.GetCurSel();
	switch (index)
	{
	case 0:
		c_Setting.ShowWindow(SW_SHOW);
		c_pWnd = &c_Setting;
		break;
	case 1:
		c_Info.ShowWindow(SW_SHOW);
		c_pWnd = &c_Info;
		break;
	default:
		break;
	}

	*pResult = 0;
}


void CMFCProjectDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CMFCProjectDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//mat_frame가 입력 이미지입니다. 
	checkedFace = c_Setting.IsDlgButtonChecked(IDC_CHECK_FACE) ? TRUE : FALSE;
	checkedAlert = c_Setting.IsDlgButtonChecked(IDC_CHECK_ALARM) ? TRUE : FALSE;
	checkedCharge = c_Setting.IsDlgButtonChecked(IDC_CHECK_CHARGE) ? TRUE : FALSE;
	checkedTimer = c_Setting.IsDlgButtonChecked(IDC_CHECK_TIMER) ? TRUE : FALSE;

	SYSTEM_POWER_STATUS st;
	GetSystemPowerStatus(&st);

	if (checkedTimer) {
		c_Setting.GetDlgItem(IDC_EDIT_TIMER_HOUR)->EnableWindow(TRUE);
		c_Setting.GetDlgItem(IDC_EDIT_TIMER_MINUTE)->EnableWindow(TRUE);
	}
	else {
		c_Setting.GetDlgItem(IDC_EDIT_TIMER_HOUR)->EnableWindow(FALSE);
		c_Setting.GetDlgItem(IDC_EDIT_TIMER_MINUTE)->EnableWindow(FALSE);
	}

	if (checkedCharge) {
		if (st.ACLineStatus!=1&&checkedChargingAction==false) {
			checkedChargingAction = true;

			CString szSoundPath = _T("C:\\alert.wav");
			if (checkedAlert == true)
				PlaySound(szSoundPath, AfxGetInstanceHandle(), SND_ASYNC | SND_LOOP); // 무한
		}

	}
	time(&tm_nd);
	double diff = difftime(tm_nd, tm_st);
	if ((diff > totalHour) && timerCheck==false && loginCheck==true) {
		timerCheck = true;
		CatchBadGuy();
	}
	HWND TaskManager;

	CascadeClassifier face_classifier;

	face_classifier.load("C:/opencv-3.4.3/sources/data/haarcascades/haarcascade_frontalface_default.xml");

	if ((TaskManager = FindWindowA(NULL, "작업 관리자")) != NULL)
		::ShowWindow(TaskManager, SW_HIDE);

	capture->read(mat_frame);

	if (checkedFace== BST_CHECKED) {
		try {
			// convert captured frame to gray scale & equalize
			cv::Mat grayframe;
			cv::cvtColor(mat_frame, grayframe, CV_BGR2GRAY);
			cv::equalizeHist(grayframe, grayframe);

			// -------------------------------------------------------------
			// face detection routine

			// a vector array to store the face found
			std::vector<cv::Rect> faces;

			face_classifier.detectMultiScale(grayframe, faces,
				1.1, // increase search scale by 10% each pass
				3,   // merge groups of three detections
				CV_HAAR_FIND_BIGGEST_OBJECT | CV_HAAR_SCALE_IMAGE,
				cv::Size(30, 30)
			);

			// -------------------------------------------------------------
			// draw the results
			for (int i = 0; i < faces.size(); i++) {
				cv::Point lb(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
				cv::Point tr(faces[i].x, faces[i].y);

				cv::rectangle(mat_frame, lb, tr, cv::Scalar(0, 255, 0), 3, 4, 0);
			}

			// print the output
			//cv::imshow("webcam", mat_frame);
		}
		catch (cv::Exception& e) {
			std::cerr << "Exception occurred. Ignoring frame... " << e.err << std::endl;
		}

	}
	//이곳에 OpenCV 함수들을 적용합니다.

	//여기에서는 그레이스케일 이미지로 변환합니다.
	//cvtColor(mat_frame, mat_frame, COLOR_BGR2GRAY);



	//화면에 보여주기 위한 처리입니다.
	int bpp = 8 * mat_frame.elemSize();
	assert((bpp == 8 || bpp == 24 || bpp == 32));

	int padding = 0;
	//32 bit image is always DWORD aligned because each pixel requires 4 bytes
	if (bpp < 32)
		padding = 4 - (mat_frame.cols % 4);

	if (padding == 4)
		padding = 0;

	int border = 0;
	//32 bit image is always DWORD aligned because each pixel requires 4 bytes
	if (bpp < 32)
	{
		border = 4 - (mat_frame.cols % 4);
	}



	Mat mat_temp;
	if (border > 0 || mat_frame.isContinuous() == false)
	{
		// Adding needed columns on the right (max 3 px)
		cv::copyMakeBorder(mat_frame, mat_temp, 0, 0, 0, border, cv::BORDER_CONSTANT, 0);
	}
	else
	{
		mat_temp = mat_frame;
	}


	RECT r;
	m_picture.GetClientRect(&r);
	cv::Size winSize(r.right, r.bottom);

	cimage_mfc.Create(winSize.width, winSize.height, 24);


	BITMAPINFO *bitInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD));
	bitInfo->bmiHeader.biBitCount = bpp;
	bitInfo->bmiHeader.biWidth = mat_temp.cols;
	bitInfo->bmiHeader.biHeight = -mat_temp.rows;
	bitInfo->bmiHeader.biPlanes = 1;
	bitInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitInfo->bmiHeader.biCompression = BI_RGB;
	bitInfo->bmiHeader.biClrImportant = 0;
	bitInfo->bmiHeader.biClrUsed = 0;
	bitInfo->bmiHeader.biSizeImage = 0;
	bitInfo->bmiHeader.biXPelsPerMeter = 0;
	bitInfo->bmiHeader.biYPelsPerMeter = 0;


	//그레이스케일 인경우 팔레트가 필요
	if (bpp == 8)
	{
		RGBQUAD* palette = bitInfo->bmiColors;
		for (int i = 0; i < 256; i++)
		{
			palette[i].rgbBlue = palette[i].rgbGreen = palette[i].rgbRed = (BYTE)i;
			palette[i].rgbReserved = 0;
		}
	}


	// Image is bigger or smaller than into destination rectangle
	// we use stretch in full rect

	if (mat_temp.cols == winSize.width  && mat_temp.rows == winSize.height)
	{
		// source and destination have same size
		// transfer memory block
		// NOTE: the padding border will be shown here. Anyway it will be max 3px width

		SetDIBitsToDevice(cimage_mfc.GetDC(),
			//destination rectangle
			0, 0, winSize.width, winSize.height,
			0, 0, 0, mat_temp.rows,
			mat_temp.data, bitInfo, DIB_RGB_COLORS);
	}
	else
	{
		// destination rectangle
		int destx = 0, desty = 0;
		int destw = winSize.width;
		int desth = winSize.height;

		// rectangle defined on source bitmap
		// using imgWidth instead of mat_temp.cols will ignore the padding border
		int imgx = 0, imgy = 0;
		int imgWidth = mat_temp.cols - border;
		int imgHeight = mat_temp.rows;

		StretchDIBits(cimage_mfc.GetDC(),
			destx, desty, destw, desth,
			imgx, imgy, imgWidth, imgHeight,
			mat_temp.data, bitInfo, DIB_RGB_COLORS, SRCCOPY);
	}




	HDC dc = ::GetDC(m_picture.m_hWnd);
	cimage_mfc.BitBlt(dc, 0, 0);


	::ReleaseDC(m_picture.m_hWnd, dc);

	cimage_mfc.ReleaseDC();
	cimage_mfc.Destroy();

	CDialogEx::OnTimer(nIDEvent);
}


void CMFCProjectDlg::Fullscreen()
{
	
	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);

	LONG style = ::GetWindowLong(m_hWnd, GWL_STYLE);

	style &= ~WS_CAPTION;
	style &= ~WS_SYSMENU;

	::SetWindowLong(m_hWnd, GWL_STYLE, style);
	int screenx = GetSystemMetrics(SM_CXSCREEN);
	int screeny = GetSystemMetrics(SM_CYSCREEN);

	// resize:
	SetWindowPos(NULL, -4, -4, screenx + 8, screeny + 4, SWP_NOZORDER);
	SetWindowPos(&this->wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	c_Info.GetDlgItem(IDC_EDIT_SET_PASSWORD)->SendMessage(EM_SETREADONLY, 1, 0);
	c_Info.GetDlgItem(IDC_EDIT_EMAIL)->SendMessage(EM_SETREADONLY, 1, 0);
	c_Info.GetDlgItem(IDC_EDIT_EMAIL)->SendMessage(EM_SETPASSWORDCHAR, 1, 0);
	c_Info.GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);

	c_Setting.GetDlgItem(IDC_CHECK_ALARM)->EnableWindow(FALSE);
	c_Setting.GetDlgItem(IDC_CHECK_CHARGE)->EnableWindow(FALSE);
	c_Setting.GetDlgItem(IDC_CHECK_TIMER)->EnableWindow(FALSE);
	c_Setting.GetDlgItem(IDC_CHECK_FACE)->EnableWindow(FALSE);
	c_Setting.GetDlgItem(IDC_EDIT_TIMER_HOUR)->EnableWindow(FALSE);
	c_Setting.GetDlgItem(IDC_EDIT_TIMER_MINUTE)->EnableWindow(FALSE);
	c_Setting.GetDlgItem(IDC_SPIN_TIMER_HOUR)->EnableWindow(FALSE);
	c_Setting.GetDlgItem(IDC_SPIN_TIMER_MINUTE)->EnableWindow(FALSE);
}




BOOL CMFCProjectDlg::PreTranslateMessage(MSG* pMsg)
{
	 //TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	
	if (pMsg->message == WM_KEYDOWN && pMsg->hwnd == GetDlgItem(IDC_EDIT_PASSWORD_INPUT)->m_hWnd)
	{ //에디트박스에서 키다운이 발생하였는가 체크                       요기가 에디트박스
		if (pMsg->wParam == VK_RETURN) //<-- 눌려진키가 엔터키인가  체크
		{
			CString inputPw;
			CString masterPw = _T("94");
			GetDlgItemText(IDC_EDIT_PASSWORD_INPUT, inputPw);
			if (inputPw.Compare(masterPw)==0) {
				AfxGetMainWnd()->PostMessage(WM_COMMAND, ID_APP_EXIT, 0);
			}
			else if (Pw != inputPw) {
				++pwMiss;
				if (pwMiss >= 2) {
					
					char gmail[30];
					char pw[30];
					onOff = true;
					strcpy_s(gmail, CStringA(Email).GetString());
					strcpy_s(pw, CStringA(Pw).GetString());
					Encrypt(gmail, gmail, 30);
					Encrypt(pw, pw, 30);

					ofstream output("C:\\log", ios::out | ios::binary);
					output.write((char*)&onOff, sizeof(bool));
					output.write((char*)&prevTime, sizeof(int));
					output.write((char*)&gmail, 30);
					output.write((char*)&pw, 30);
					output.close();


					CatchBadGuy();
				}
				CString str;
				str.Format(_T("%d"), pwMiss);
				MessageBox(_T("비밀번호 ") + str + _T("회 틀렸습니다."));
			}
			else {				
				CFile::Remove(_T("C:\\log"));
				AfxGetMainWnd()->PostMessage(WM_COMMAND, ID_APP_EXIT, 0);
			}
			return TRUE;
		}
	}
	else if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_MENU || pMsg->wParam == VK_F4 || pMsg->wParam == VK_CONTROL || pMsg->wParam == VK_DELETE) return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMFCProjectDlg::CatchBadGuy()
{
	CInternetSession session;
	CString str, html_text;
	CString szSoundPath = _T("C:\\alert.wav");
	if (checkedAlert == true)
		PlaySound(szSoundPath, AfxGetInstanceHandle(), SND_ASYNC | SND_LOOP); // 무한

	try {
		LPCTSTR strInput = _T("http://mylocation.co.kr/");
		CInternetFile *p_html = (CInternetFile *)session.OpenURL(strInput);

		if (p_html != NULL) {

			// Html 정보를 가져올때 사용할 버퍼의 크기를 512Bytes로 설정한다.
			p_html->SetReadBufferSize(512);
			while (1) {
				// 더 이상 읽을 정보가 없다면 종료한다.
				if (!p_html->ReadString(str)) break;

				// 읽어 들인 정보는 html_text 문자열에 추가한다.
				html_text += CA2W((LPCSTR)str.GetBuffer(), CP_UTF8);
			}
			// Html 파일을 닫는다.
			p_html->Close();

			// Html 파일 읽기에 사용한 객체를 파괴한다.
			delete p_html;

			// 세션을 닫는다.
			session.Close();

			
		}

	}
	catch (CInternetException *) {

	}
	CString str2 = html_text;
	int ipPos = str2.Find(_T("ExIP"), 15000);
	int adPos = str2.Find(_T("lbAddr"), 20000);
	int ipPos2 = 0;
	int adPos2 = 0;
	CString address = str2.Mid(adPos + 31, 30);
	CString ipAddress = str2.Mid(ipPos + 38, 30);
	CString lo = _T("위치 : ");
	address = address.Tokenize(_T("</span>"), adPos2);
	ipAddress = ipAddress.Tokenize(_T("</span>"), ipPos2);

	CString finalOut = lo + address + "<br>IP주소 : " + ipAddress;

	char buf[256]= "C:\\BadGuy.jpg";
	capture->read(mat_frame);
	imwrite(buf, mat_frame);

	::CoInitialize(NULL);
	IMailPtr oSmtp = NULL;
	oSmtp.CreateInstance("EASendMailObj.Mail");
	oSmtp->LicenseCode = "TryIt";

	// Set your gmail email address
	oSmtp->FromAddr = "NotFreeLaptop@gmail.com";
	// Add recipient email address
	_bstr_t mstr(Email);
	_bstr_t pstr(Pw);
	oSmtp->AddRecipientEx(mstr, 0);
	// Set email subject
	oSmtp->Subject = "잡았다 요놈";
	// Set email body
	oSmtp->BodyText = "메일내용";
	// Gmail SMTP server address
	oSmtp->ServerAddr = "smtp.gmail.com";
	// Set HTML body format
	oSmtp->BodyFormat = 1;
	// Set HTML body text
	CString htmlText = _T("<font size=6>");
	htmlText += finalOut += "</font>";
	_bstr_t htmlConvert(htmlText);

	oSmtp->BodyText = htmlConvert;

	if (oSmtp->AddAttachment("C:\\BadGuy.jpg") != 0)
	{


	}
	// Use SSL 465 port, //암복호 포트 잘맞춰야 된다.
	oSmtp->ServerPort = 465;
	// detect SSL/TLS automatically
	oSmtp->SSL_init();

	// Gmail user authentication should use your 
	// Gmail email address as the user name. 
	
	oSmtp->UserName = mstr;
	oSmtp->Password = pstr;
	if (oSmtp->SendMail() == 0)

	{
		
		MessageBox(_T("당신의 정보는 노트북 소유자에게 넘어갔습니다.\n원래 위치에 노트북을 다시 갖다놓으시오."));


	}
	else {
		MessageBox((LPCTSTR)oSmtp->GetLastErrDescription());
	}
	if (oSmtp != NULL)

		oSmtp.Release();

	
}