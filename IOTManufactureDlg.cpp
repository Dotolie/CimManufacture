
// IOTManufactureDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "IOTManufacture.h"
#include "IOTManufactureDlg.h"
#include "afxdialogex.h"
#include "XLEzAutomation.h"

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
public:
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


// CIOTManufactureDlg 대화 상자



CIOTManufactureDlg::CIOTManufactureDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IOTMANUFACTURE_DIALOG, pParent)
	, m_strMACETH0(_T(""))
	, m_strMACETH1(_T(""))
	, m_strSerialNum(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pWndShow = NULL;

	m_iSendDataType = 1;
	m_iReceiveDataType = 1;
	m_iCount = 0;
	m_iSize = 0;
	m_ResultFlag = 0;

	GetterResult = _T("");
}

void CIOTManufactureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_MENU, m_tabMenu);
	DDX_Control(pDX, IDC_EDIT_RECEIVE, m_EditReceive);
	DDX_Control(pDX, IDC_COMBO_COMPORT, m_comboComPort);
	DDX_Control(pDX, IDC_COMBO_MODEL, m_comboModel);
	DDX_Control(pDX, IDC_EDIT_CONTROL, m_EditControl);
	DDX_Text(pDX, IDC_EDIT_ETH0_MAC, m_strMACETH0);
	DDX_Text(pDX, IDC_EDIT_ETH1_MAC, m_strMACETH1);
	DDX_Text(pDX, IDC_EDIT_SERIAL_NUMBER, m_strSerialNum);
	DDX_Control(pDX, IDC_LIST_RESULT, m_listExcelCtrl);
}

BEGIN_MESSAGE_MAP(CIOTManufactureDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_DROPDOWN(IDC_COMBO_COMPORT, &CIOTManufactureDlg::OnCbnDropdownComboComport)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CIOTManufactureDlg::OnBnClickedButtonConnect)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MENU, &CIOTManufactureDlg::OnTcnSelchangeTabMenu)
	ON_MESSAGE(WM_COMM_READ, (LRESULT(AFX_MSG_CALL CWnd::*)(WPARAM, LPARAM))OnCommunication) //추가
	ON_EN_MAXTEXT(IDC_EDIT_RECEIVE, &CIOTManufactureDlg::OnEnMaxtextEditReceive)
	ON_BN_CLICKED(IDC_BUTTON_RECEIVE_DATA_CLEAR, &CIOTManufactureDlg::OnBnClickedButtonReceiveDataClear)
	ON_BN_CLICKED(IDC_BUTTON_VIEW_MAC, &CIOTManufactureDlg::OnBnClickedButtonViewMac)
	ON_BN_CLICKED(IDC_BUTTON_ETH0_MAC, &CIOTManufactureDlg::OnBnClickedButtonEth0Mac)
	ON_BN_CLICKED(IDC_BUTTON_ETH1_MAC, &CIOTManufactureDlg::OnBnClickedButtonEth1Mac)
	ON_BN_CLICKED(IDC_BUTTON_START, &CIOTManufactureDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_SERIAL_NUMBER, &CIOTManufactureDlg::OnBnClickedButtonSerialNumber)
	ON_CBN_SELCHANGE(IDC_COMBO_MODEL, &CIOTManufactureDlg::OnCbnSelchangeComboModel)
	ON_BN_CLICKED(IDC_BUTTON_SERIAL_INC, &CIOTManufactureDlg::OnBnClickedButtonSerialInc)
	ON_BN_CLICKED(IDC_BUTTON_EXCEL_SAVE, &CIOTManufactureDlg::OnBnClickedButtonExcelSave)
END_MESSAGE_MAP()


// CIOTManufactureDlg 메시지 처리기

BOOL CIOTManufactureDlg::OnInitDialog()
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
	CRect rect;
	//GetClientRect(&rect);
	m_tabMenu.GetClientRect(&rect);

	CString tab0 = _T("Common");
	CString tab1 = _T("Digital");
	CString tab2 = _T("Iolink");
	CString tab3 = _T("Analog");
	CString tab4 = _T("Vibration");

	m_tabMenu.InsertItem(1, tab0);
#if 0
	m_tabMenu.InsertItem(2, tab1);
	m_tabMenu.InsertItem(3, tab2);
	m_tabMenu.InsertItem(4, tab3);
	m_tabMenu.InsertItem(5, tab4);
#endif

	m_CommonDlg.Create(IDD_DIALOG_COMMON, &m_tabMenu);
	m_CommonDlg.SetWindowPos(NULL, 4, 25, rect.Width() - 10, rect.Height() -30 , SWP_SHOWWINDOW | SWP_NOZORDER);
	m_CommonDlg.ShowWindow(SW_HIDE);
#if 0
	m_DigitalDlg.Create(IDD_DIALOG_DIGITAL, &m_tabMenu);
	m_DigitalDlg.SetWindowPos(NULL, 4, 25, rect.Width() - 10, rect.Height() - 30, SWP_NOZORDER);
	m_DigitalDlg.ShowWindow(SW_HIDE);

	m_IolinkDlg.Create(IDD_DIALOG_IOLINK, &m_tabMenu);
	m_IolinkDlg.SetWindowPos(NULL, 4, 25, rect.Width() - 10, rect.Height() - 30, SWP_NOZORDER);
	m_DigitalDlg.ShowWindow(SW_HIDE);

	m_AnalogDlg.Create(IDD_DIALOG_ANALOG, &m_tabMenu);
	m_AnalogDlg.SetWindowPos(NULL, 4, 25, rect.Width() - 10, rect.Height() - 30, SWP_NOZORDER);
	m_AnalogDlg.ShowWindow(SW_HIDE);

	m_VibrationDlg.Create(IDD_DIALOG_VIB, &m_tabMenu);
	m_VibrationDlg.SetWindowPos(NULL, 4, 25, rect.Width() - 10, rect.Height() - 30, SWP_NOZORDER);
	m_VibrationDlg.ShowWindow(SW_HIDE);
#endif
	m_tabMenu.SetCurSel(0);
	m_CommonDlg.ShowWindow(SW_SHOW);
	m_pWndShow = &m_CommonDlg;

	m_Comm.hCommWnd = this->m_hWnd;
#if 0
	m_comboModel.InsertString(0, _T("DIGITAL"));
	m_comboModel.InsertString(1, _T("IOLINK"));
	m_comboModel.InsertString(2, _T("ANALOG"));
	m_comboModel.InsertString(3, _T("VIBRATION"));
#else
	m_comboModel.InsertString(0, _T("CIM"));
#endif
	m_comboModel.SetCurSel(0);

	CTime timeNow = CTime::GetCurrentTime();
	CString strDateTime;
	strDateTime = timeNow.Format(_T("%Y%m%d")) + SDC_CIM + _T("0001");
	strDateTime.Delete(0, 2);

	CString SumStrSerial;
	SumStrSerial = _T("MVTECH") + strDateTime;
	GetDlgItem(IDC_EDIT_SERIAL_NUMBER)->SetWindowText(SumStrSerial);

	m_listExcelCtrl.InsertColumn(0, _T("시리얼번호."), LVCFMT_CENTER, 160);
	m_listExcelCtrl.InsertColumn(1, _T("MAC Eth0"), LVCFMT_CENTER, 120);
	m_listExcelCtrl.InsertColumn(2, _T("MAC Eth1"), LVCFMT_CENTER, 120);
	m_listExcelCtrl.InsertColumn(3, _T("MAC WIFI"), LVCFMT_CENTER, 120);
	m_listExcelCtrl.InsertColumn(4, _T("MEMORY"), LVCFMT_CENTER, 70);
	m_listExcelCtrl.InsertColumn(5, _T("EMMC"), LVCFMT_CENTER, 70);
	m_listExcelCtrl.InsertColumn(6, _T("FLASH"), LVCFMT_CENTER, 70);
	m_listExcelCtrl.InsertColumn(7, _T("OLED"), LVCFMT_CENTER, 70);
	m_listExcelCtrl.InsertColumn(8, _T("ETH0"), LVCFMT_CENTER, 70);
	m_listExcelCtrl.InsertColumn(9, _T("ETH1"), LVCFMT_CENTER, 70);
	m_listExcelCtrl.InsertColumn(10, _T("WIFI"), LVCFMT_CENTER, 70);
	m_listExcelCtrl.InsertColumn(11, _T("RSSI"), LVCFMT_CENTER, 70);
	m_listExcelCtrl.InsertColumn(12, _T("TIME"), LVCFMT_CENTER, 120);

	m_listExcelCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listExcelCtrl.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);

	m_FontResult.CreateFontW(
		20,                            // 글자높이
		8,                            // 글자너비
		0,                            // 출력각도
		0,                            // 기준 선에서의각도
		FW_HEAVY,                    // 글자굵기
		FALSE,                        // Italic 적용여부
		FALSE,                        // 밑줄적용여부
		FALSE,                        // 취소선적용여부
		DEFAULT_CHARSET,            // 문자셋종류
		OUT_DEFAULT_PRECIS,            // 출력정밀도
		CLIP_CHARACTER_PRECIS,        // 클리핑정밀도
		PROOF_QUALITY,                // 출력문자품질
		DEFAULT_PITCH,                // 글꼴Pitch
		_T("굴림")                // 글꼴
	);

	m_CommonDlg.GetDlgItem(IDC_STATIC_MEMORY_RESULT)->SetFont(&m_FontResult);
	m_CommonDlg.GetDlgItem(IDC_STATIC_EMMC_RESULT)->SetFont(&m_FontResult);
	m_CommonDlg.GetDlgItem(IDC_STATIC_FLASH_RESULT)->SetFont(&m_FontResult);
	m_CommonDlg.GetDlgItem(IDC_STATIC_OLED_RESULT)->SetFont(&m_FontResult);
	m_CommonDlg.GetDlgItem(IDC_STATIC_ETH0_RESULT)->SetFont(&m_FontResult);
	m_CommonDlg.GetDlgItem(IDC_STATIC_ETH1_RESULT)->SetFont(&m_FontResult);
	m_CommonDlg.GetDlgItem(IDC_STATIC_WLAN0_RESULT)->SetFont(&m_FontResult);
	GetDlgItem(IDC_STATIC_TEST_MONITOR)->SetFont(&m_FontResult);

	m_TestFlag = 0;
	SetTimer(0, 500, NULL);

	AllButtonDisable();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CIOTManufactureDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CIOTManufactureDlg::OnPaint()
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

		CClientDC dc(this);
		RECT rect, rect1;
		int nOffset = 10;
		COLORREF color;
		GetDlgItem(IDC_BUTTON_CONNECT)->GetWindowRect(&rect);
		ScreenToClient(&rect);
		rect1.top = rect.top;
		rect1.left = rect.right + 10;
		rect1.right = rect.right + 10 + (rect.bottom - rect.top);
		rect1.bottom = rect.top + (rect.bottom - rect.top);

		if (m_Comm.m_bConnected)
			color = RGB(0, 255, 0);
		else
			color = 0;
		dc.FillSolidRect(&rect1, color);
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CIOTManufactureDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CIOTManufactureDlg::OnCbnDropdownComboComport()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	getSerialPort();
}


void CIOTManufactureDlg::OnBnClickedButtonConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString selectDropListString, strPort;
	int nIndex, nPortNum;

	nIndex = m_comboComPort.GetCurSel();
	if (nIndex < 0)
	{
		AfxMessageBox(_T("컴포트를 선택하세요"), MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	m_comboComPort.GetLBText(nIndex, selectDropListString);
	strPort = selectDropListString;
	strPort.TrimLeft(_T("COM"));
	nPortNum = _ttoi(strPort);

	if (nPortNum > 9)
		selectDropListString.Format(_T("\\\\.\\COM%d"), nPortNum);

	if (!m_Comm.m_bConnected)
	{
		//if (m_Comm.OpenPort(selectDropListString, _T("115200"), _T("8"), _T("NO"), _T("NO"), _T("1")))
		if (m_Comm.OpenPort(selectDropListString, 115200, 8, 0, 0))
		{
			//접속 성공
			//AfxMessageBox("컴포트 오픈 성공", MB_OK | MB_ICONEXCLAMATION);

			//MsgMonitor("컴포트 오픈 성공");

			GetDlgItem(IDC_COMBO_COMPORT)->EnableWindow(FALSE);

			SetDlgItemText(IDC_BUTTON_CONNECT, _T("해제"));

			SetDlgItemText(IDC_STATIC_VIEWMACS, _T(""));
			m_CommonDlg.SetDlgItemText(IDC_STATIC_VIEWMACS, _T("Need Read!!"));
			m_CommonDlg.SetDlgItemText(IDC_STATIC_RSSI, _T("RSSI :"));
			m_CommonDlg.SetDlgItemText(IDC_STATIC_MEMORY_RESULT, _T("Ready"));
			m_CommonDlg.SetDlgItemText(IDC_STATIC_EMMC_RESULT, _T("Ready"));
			m_CommonDlg.SetDlgItemText(IDC_STATIC_FLASH_RESULT, _T("Ready"));
			m_CommonDlg.SetDlgItemText(IDC_STATIC_OLED_RESULT, _T("Ready"));
			m_CommonDlg.SetDlgItemText(IDC_STATIC_ETH0_RESULT, _T("Ready"));
			m_CommonDlg.SetDlgItemText(IDC_STATIC_ETH1_RESULT, _T("Ready"));
			m_CommonDlg.SetDlgItemText(IDC_STATIC_WLAN0_RESULT, _T("Ready"));

			AllButtonEnable();
		}
		else
		{
			//접속 실패
			AfxMessageBox(_T("컴포트 오픈 실패"), MB_OK | MB_ICONEXCLAMATION);
		}
	}
	else
	{
		CString StrTestCode;

		StrTestCode = "x\n";
		SendAsciiData(StrTestCode);
		Wait(200);

		StrTestCode = "exit\n";
		SendAsciiData(StrTestCode);
		Wait(200);

		m_Comm.ClosePort();

		//MsgMonitor("컴포트 닫기 성공");
		GetDlgItem(IDC_COMBO_COMPORT)->EnableWindow(TRUE);
		SetDlgItemText(IDC_BUTTON_CONNECT, _T("연결"));
		AllButtonDisable();
	}

	m_ResultFlag = 0;
	Invalidate(false);
}


void CIOTManufactureDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_ResultFlag)
	{
		if (m_TestFlag)
			SetDlgItemText(IDC_STATIC_TEST_MONITOR, _T("테스트 중!!"));
		else
			SetDlgItemText(IDC_STATIC_TEST_MONITOR, _T(""));
		m_TestFlag = !m_TestFlag;
	}
	else
	{
		SetDlgItemText(IDC_STATIC_TEST_MONITOR, _T(""));
	}

	CDialogEx::OnTimer(nIDEvent);
}


HBRUSH CIOTManufactureDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_TEST_MONITOR)
	{
		pDC->SetTextColor(RGB(255, 0, 0));
	}

	return hbr;
}


BOOL CIOTManufactureDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CIOTManufactureDlg::OnTcnSelchangeTabMenu(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pWndShow != NULL)
	{
		m_pWndShow->ShowWindow(SW_HIDE);
		m_pWndShow = NULL;
	}

	int nIndex = m_tabMenu.GetCurSel();
	switch (nIndex)
	{
	case 0:
		m_CommonDlg.ShowWindow(SW_SHOW);
		m_pWndShow = &m_CommonDlg;
		break;
	case 1:
		m_DigitalDlg.ShowWindow(SW_SHOW);
		m_pWndShow = &m_DigitalDlg;
		break;
	case 2:
		m_IolinkDlg.ShowWindow(SW_SHOW);
		m_pWndShow = &m_IolinkDlg;
		break;
	case 3:
		m_AnalogDlg.ShowWindow(SW_SHOW);
		m_pWndShow = &m_AnalogDlg;
		break;
	case 4:
		m_VibrationDlg.ShowWindow(SW_SHOW);
		m_pWndShow = &m_VibrationDlg;
		break;
	}
	*pResult = 0;
}


void CIOTManufactureDlg::getSerialPort()
{
	// TODO: 여기에 구현 코드 추가.
	int nPortNum;
	HKEY hKey;
	HANDLE hCom = NULL;
	CString strPort;

	RegOpenKey(HKEY_LOCAL_MACHINE, TEXT("HARDWARE\\DEVICEMAP\\SERIALCOMM"), &hKey);

	TCHAR szData[20], szName[100];
	DWORD index = 0, dwSize = 100, dwSize2 = 20, dwType = REG_SZ;
	m_comboComPort.ResetContent();
	memset(szData, 0x00, sizeof(szData));
	memset(szName, 0x00, sizeof(szName));

	while (ERROR_SUCCESS == RegEnumValue(hKey, index, szName, &dwSize, NULL, NULL, NULL, NULL))
	{
		index++;

		RegQueryValueEx(hKey, szName, NULL, &dwType, (LPBYTE)szData, &dwSize2);

		strPort = szData;
		strPort.TrimLeft(_T("COM"));
		nPortNum = _ttoi(strPort);

		if (nPortNum < 10)
			strPort.Format(_T("COM%d"), nPortNum);
		else
			strPort.Format(_T("\\\\.\\COM%d"), nPortNum);
		hCom = CreateFile(strPort,
			GENERIC_READ | GENERIC_WRITE, // desired access should be read&write  
			0,                          // COM port must be opened in non-sharing mode  
			NULL,                       // don't care about the security  
			OPEN_EXISTING,              // IMPORTANT: must use OPEN_EXISTING for a COM port  
			0,                          // usually overlapped but non-overlapped for existance test  
			NULL);                      // always NULL for a general purpose COM port
		if (INVALID_HANDLE_VALUE == hCom)
		{
			//if (ERROR_ACCESS_DENIED == hCom)  
		   // {
				// then it exists and currently opened  
		   // }  
		}
		else
		{   // COM port exist  
			m_comboComPort.AddString(CString(szData));
			CloseHandle(hCom);
		}

		memset(szData, 0x00, sizeof(szData));
		memset(szName, 0x00, sizeof(szName));
		dwSize = 100;
		dwSize2 = 20;
	}

	if (m_comboComPort.GetCount() > 0)
		m_comboComPort.SetCurSel(0);

	RegCloseKey(hKey);
}


void CIOTManufactureDlg::AllButtonDisable()
{
	// TODO: 여기에 구현 코드 추가.
	m_CommonDlg.GetDlgItem(IDC_BUTTON_MEM_TEST)->EnableWindow(FALSE);
	m_CommonDlg.GetDlgItem(IDC_BUTTON_EMMC_TEST)->EnableWindow(FALSE);
	m_CommonDlg.GetDlgItem(IDC_BUTTON_FLASH_TEST)->EnableWindow(FALSE);
	m_CommonDlg.GetDlgItem(IDC_BUTTON_LED_TEST)->EnableWindow(FALSE);
	m_CommonDlg.GetDlgItem(IDC_BUTTON_ETH0_TEST)->EnableWindow(FALSE);
	m_CommonDlg.GetDlgItem(IDC_BUTTON_ETH1_TEST)->EnableWindow(FALSE);
	m_CommonDlg.GetDlgItem(IDC_BUTTON_WLAN_TEST)->EnableWindow(FALSE);
	m_CommonDlg.GetDlgItem(IDC_BUTTON_AUTO_TEST)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_BUTTON_VIEW_MAC)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ETH0_MAC)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ETH1_MAC)->EnableWindow(FALSE);
}


void CIOTManufactureDlg::AllButtonEnable()
{
	// TODO: 여기에 구현 코드 추가.
	m_CommonDlg.GetDlgItem(IDC_BUTTON_MEM_TEST)->EnableWindow(TRUE);
	m_CommonDlg.GetDlgItem(IDC_BUTTON_EMMC_TEST)->EnableWindow(TRUE);
	m_CommonDlg.GetDlgItem(IDC_BUTTON_FLASH_TEST)->EnableWindow(TRUE);
	m_CommonDlg.GetDlgItem(IDC_BUTTON_LED_TEST)->EnableWindow(TRUE);
	m_CommonDlg.GetDlgItem(IDC_BUTTON_ETH0_TEST)->EnableWindow(TRUE);
	m_CommonDlg.GetDlgItem(IDC_BUTTON_ETH1_TEST)->EnableWindow(TRUE);
	m_CommonDlg.GetDlgItem(IDC_BUTTON_WLAN_TEST)->EnableWindow(TRUE);
	m_CommonDlg.GetDlgItem(IDC_BUTTON_AUTO_TEST)->EnableWindow(TRUE);

	GetDlgItem(IDC_BUTTON_VIEW_MAC)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_ETH0_MAC)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_ETH1_MAC)->EnableWindow(TRUE);
}

long CIOTManufactureDlg::OnCommunication(WPARAM wParam, LPARAM lParam)
{
	UpdateData(TRUE);//받는 데이터 타입을 알기 위해
	CString str = _T("");
	CString strResult = _T("");
	CString strSize = _T("");

	BYTE aByte; //데이터를 저장할 변수 
	int iSize = (m_Comm.m_QueueRead).GetSize(); //포트로 들어온 데이터 갯수
	//SetCommState에 설정된 내용 때문에 거의 8개씩 들어옴
	m_iSize += iSize;	//받은 데이터의 총 갯수를 설정창에 보여주기 위해 
	//wsprintf(size, _T("Receive %d characters\r\n"), m_iSize);
	strSize.Format(_T("Receive %d characters\r\n"), m_iSize);
	if (iSize != 0)//받은 갯수가 0이 아니면 화면에 들어온 갯수를 설정창에  출력
	{
		m_EditControl.SetSel(-1, 0);
		m_EditControl.ReplaceSel(strSize);
		//strSize.Format(_T("############ Receive %d characters\r\n"), m_iSize);
		//m_EditReceive.SetSel(-1, 0);
		//m_EditReceive.ReplaceSel(strSize);
	}

	for (int i = 0; i < iSize; i++)//들어온 갯수 만큼 데이터를 읽어 와 화면에 보여줌
	{
		(m_Comm.m_QueueRead).GetByte(&aByte);//큐에서 데이터 한개를 읽어옴
		switch (m_iReceiveDataType)//받는 데이터 타입이 ASCII or HEX 인가에 따라 데이터 받는 법을 다르게
		{
		case 0: //데이터가 HEX이면
			str.Format(_T("%02X "), aByte);
			m_iCount++;//데이터 갯수 세기
			if ((m_iCount % 16) == 0) //16개를 받으면 줄 바꿈
			{
				str += _T("\r\n");
			}
			/*else if((m_iCount % 8) ==0)//8개를 받으면 TAB을 넣어서 데이터 구분
			{
				str += _T("\t");
			}*/
			strResult += str;
			break;
		case 1://데이터가 ASCII이면
			str.Format(_T("%c"), aByte);
			strResult += str;

			if (m_ResultFlag != 0) {
				GetterResult += str;

			}
			else {
				GetterResult = _T("");
			}
			break;
		}
	}

	m_EditReceive.SetSel(-1, 0);
	m_EditReceive.ReplaceSel(strResult);//화면에 받은 데이터 보여줌
	//TRACE(strResult);
	UpdateData(TRUE);
	return 1;
}

void CIOTManufactureDlg::OnEnMaxtextEditReceive()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CIOTManufactureDlg::OnBnClickedButtonReceiveDataClear();
}


void CIOTManufactureDlg::OnBnClickedButtonReceiveDataClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_iCount = 0;
	m_EditReceive.SetSel(0, -1);
	m_EditReceive.Clear();
}


void CIOTManufactureDlg::OnBnClickedButtonViewMac()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString StrTestCode;
	CString strTemp;
	int n, i, len;
	CString strMACEth0, strMACEth1, strMACWlan0;
	char* sourcechar;
	char  Tempchar[30];

	AllButtonDisable();

	StrTestCode = "\n9\n";
	SendAsciiData(StrTestCode);
	m_ResultFlag = VIEWMAC;
	Wait(100);

	CIOTManufactureDlg::WaitSting(_T("enter key"), 20);
	//CIOTManufactureDlg::Discrimination(GetterResult);

	n = GetterResult.Find(_T("eth0 Mac : "), 0);
	strTemp = GetterResult.Mid(n);

	int sLen = WideCharToMultiByte(CP_ACP, 0, strTemp, -1, NULL, 0, NULL, NULL);
	sourcechar = new char[sLen + 1];
	WideCharToMultiByte(CP_ACP, 0, strTemp, -1, sourcechar, sLen, NULL, NULL);

	for (i = 0; i < strTemp.GetLength(); i++)
	{
		if (sourcechar[i] == 'e' && sourcechar[i + 1] == 't' && sourcechar[i + 2] == 'h' && sourcechar[i + 3] == '0')
		{
			memset(Tempchar, 0, 30);
			memcpy(Tempchar, sourcechar + (i + 11), 17);
			strMACEth0 = char2CString(Tempchar);
		}
		if (sourcechar[i] == 'e' && sourcechar[i + 1] == 't' && sourcechar[i + 2] == 'h' && sourcechar[i + 3] == '1')
		{
			memset(Tempchar, 0, 30);
			memcpy(Tempchar, sourcechar + (i + 11), 17);
			strMACEth1 = char2CString(Tempchar);
		}
		if (sourcechar[i] == 'w' && sourcechar[i + 1] == 'l' && sourcechar[i + 2] == 'a' && sourcechar[i + 3] == 'n')
		{
			memset(Tempchar, 0, 30);
			memcpy(Tempchar, sourcechar + (i + 12), 17);
			strMACWlan0 = char2CString(Tempchar);
		}
	}

	len = strTemp.GetLength();
	n = strTemp.Find(_T("wlan0 Mac : "), 0);
	strTemp.Delete(n + 29, len - (n + 29));
	SetDlgItemText(IDC_STATIC_VIEWMACS, strTemp);

	GetterResult = _T("");
	StrTestCode = "\n";
	SendAsciiData(StrTestCode);

	m_ResultFlag = 0;

	m_RptETH0MAC = strMACEth0;
	m_RptETH1MAC = strMACEth1;
	m_RptWLAN0MAC = strMACWlan0;

	delete[] sourcechar;

	AllButtonEnable();
}


void CIOTManufactureDlg::OnBnClickedButtonEth0Mac()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CString StrSendCode;

	if (m_strMACETH0.GetLength() < 17)
	{
		AfxMessageBox(_T("MAC번호의 길이가 맞지 않습니다."));
		return;
	}
	AllButtonDisable();
	StrSendCode = "\n7\n";
	SendAsciiData(StrSendCode);
	Wait(200);

	StrSendCode = m_strMACETH0;
	SendAsciiData(StrSendCode);
	Wait(200);

	StrSendCode = "\n";
	SendAsciiData(StrSendCode);
	Wait(500);

	StrSendCode = "\n";
	SendAsciiData(StrSendCode);
	Wait(200);
	AllButtonEnable();
}


void CIOTManufactureDlg::OnBnClickedButtonEth1Mac()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CString StrSendCode;

	if (m_strMACETH1.GetLength() < 17)
	{
		AfxMessageBox(_T("MAC번호의 길이가 맞지 않습니다."));
		return;
	}
	AllButtonDisable();
	StrSendCode = "\n8\n";
	SendAsciiData(StrSendCode);
	Wait(200);

	StrSendCode = m_strMACETH1;
	SendAsciiData(StrSendCode);
	Wait(200);

	StrSendCode = "\n";
	SendAsciiData(StrSendCode);
	Wait(500);

	StrSendCode = "\n";
	SendAsciiData(StrSendCode);
	Wait(200);
	AllButtonEnable();
}


void CIOTManufactureDlg::Wait(DWORD dwMillisecond)
{
	// TODO: 여기에 구현 코드 추가.
	MSG msg;
	DWORD dwStart;
	dwStart = GetTickCount();

	while (GetTickCount() - dwStart < dwMillisecond)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}


int CIOTManufactureDlg::SendHEXData(CString strSend)
{
	// TODO: 여기에 구현 코드 추가.
	int bufPos = 0;
	int datasize, bufsize, i, j;
	BYTE* Send_buff, byHigh, byLow;
	CString byGetData = strSend;
	byGetData.Replace(_T(" "), _T(""));// 공백 없애기 
	byGetData.Replace(_T("\r\n"), _T(""));//엔터 없애기
	datasize = byGetData.GetLength(); // 공백을 없앤 문자열 길이 얻기 

	// 문자 길이를 %2로 나눈 값이 0이 아니면 홀수 이기 때문에 마지막 문자를 처리 해줘야 함
	if (datasize % 2 == 0)
	{
		bufsize = datasize;
	}
	else
	{
		bufsize = datasize - 1;
	}

	Send_buff = new BYTE[bufsize];

	for (i = 0; i < bufsize; i += 2)
	{
		byHigh = byCode2AsciiValue(byGetData[i]);
		byLow = byCode2AsciiValue(byGetData[i + 1]);
		Send_buff[bufPos++] = (byHigh << 4) | byLow;

	}
	//마지막 문자가 1자리수 일때 처리 하기 위해  예) 1 -> 01
	if (datasize % 2 != 0)
	{
		Send_buff[bufPos++] = byCode2AsciiValue(byGetData[datasize - 1]);
	}

	int etc = bufPos % 8;
	//포트에 데이터를 8개씩 쓰기 위해
	//데이터의 길이가 8의 배수가 아니면 나머지 데이터는 따로 보내줌
	for (j = 0; j < bufPos - etc; j += 8)//8의 배수 보냄
	{
		m_Comm.WriteComm(&Send_buff[j], 8);
	}
	if (etc != 0)//나머지 데이터 전송
	{
		m_Comm.WriteComm(&Send_buff[bufPos - etc], etc);// 포트에 데이터 쓰기 
	}

	delete[] Send_buff;
	return bufPos;
}


int CIOTManufactureDlg::WaitSting(CString CompStr, int n_timeout)
{
	// TODO: 여기에 구현 코드 추가.
	int m_result = 0;
	int i;

	for (i = 0; i < n_timeout; i++) {
		m_result = GetterResult.Find(CompStr);
		if (m_result >= 1) {
			TRACE("Wait ok %s, TO %d, %d\n", CompStr, n_timeout, i);
			return 1;
		}
		else {
			TRACE("Wait %s, TO %d, %d\n", CompStr, n_timeout, i);
			Wait(1000);
		}
	}
	return 0;
}


int CIOTManufactureDlg::SendAsciiData(CString strSend)
{
	// TODO: 여기에 구현 코드 추가.
	int bufPos = 0;
	int nSize = strSend.GetLength();

	BYTE* Send_buff;
	Send_buff = new BYTE[nSize];
	memset(Send_buff, 0, nSize);

	for (int i = 0; i < nSize; i++)//ASCII 데이터 이기 때문에 버터에 그대로 저장
	{
		Send_buff[bufPos++] = strSend[i];
	}
	int etc = bufPos % 8;
	//포트에 데이터를 8개씩 쓰기 위해
	//데이터의 길이가 8의 배수가 아니면 나머지 데이터는 따로 보내줌
	if (nSize > 8) {
		for (int j = 0; j < bufPos - etc; j += 8)
		{
			m_Comm.WriteComm(&Send_buff[j], 8);
		}
	}
	if (etc != 0)//나머지 데이터 전송
	{
		m_Comm.WriteComm(&Send_buff[bufPos - etc], etc);
	}
	delete[] Send_buff;

	return 1;
}


int CIOTManufactureDlg::Discrimination(CString strDist)
{
	// TODO: 여기에 구현 코드 추가.
	int m_result = 0;
	switch (m_ResultFlag)
	{
	case TESTETH0:
		m_result = strDist.Find(_T("100% packet loss"));
		if (m_result >= 0) {
			m_RptTESTETH0 = "NG";
			//AfxMessageBox("NETWORTK (eth0)  FAIL");
			return 0;
		}
		else {
			m_RptTESTETH0 = "OK";
			//AfxMessageBox("NETWORTK (eth0)  OK!!!");
			return 1;
		}
		break;
	case TESTETH1:
		m_result = strDist.Find(_T("100% packet loss"));
		if (m_result >= 0) {
			m_RptTESTETH1 = "NG";
			//AfxMessageBox("NETWORTK (eth1)  FAIL");
			return 0;
		}
		else {
			m_RptTESTETH1 = "OK";
			//AfxMessageBox("NETWORTK (eth1)  OK!!!");
			return 1;
		}
		break;
	case TESTWIFI:
		m_result = strDist.Find(_T("100% packet loss"));
		if (m_result >= 0) {
			m_RptTESTWIFI = "NG";
			//AfxMessageBox("NETWORTK (eth1)  FAIL");
			return 0;
		}
		else {
			m_RptTESTWIFI = "OK";
			//AfxMessageBox("NETWORTK (eth1)  OK!!!");
			return 1;
		}
		break;
	case VIEWMAC:
		//판정후 있으면 출력한다.
		m_result = strDist.Find(_T("wlan0 Mac"));
		if (m_result >= 0) {
			//AfxMessageBox(strDist);
			return 0;
		}
		else {
			//strDist
			//AfxMessageBox(strDist);
			return 1;
		}
		break;
	}
	return 1;
}


CString CIOTManufactureDlg::char2CString(char* inp)
{
	// TODO: 여기에 구현 코드 추가.
	int len;
	CString str;
	BSTR buf;

	len = MultiByteToWideChar(CP_ACP, 0, inp, (int)strlen(inp), NULL, NULL);
	buf = SysAllocStringLen(NULL, len);
	MultiByteToWideChar(CP_ACP, 0, inp, (int)strlen(inp), buf, len);

	str = (LPWSTR)buf;
	return str;
}


BYTE CIOTManufactureDlg::byCode2AsciiValue(char cData)
{
	// TODO: 여기에 구현 코드 추가.
	BYTE byAsciiValue;
	if (('0' <= cData) && (cData <= '9'))
	{
		byAsciiValue = cData - '0';
	}
	else if (('A' <= cData) && (cData <= 'F'))
	{
		byAsciiValue = (cData - 'A') + 10;
	}
	else if (('a' <= cData) && (cData <= 'f'))
	{
		byAsciiValue = (cData - 'a') + 10;
	}
	else
	{
		byAsciiValue = 0;
	}
	return byAsciiValue;
}


void CIOTManufactureDlg::OnBnClickedButtonStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString StrTestCode;

	StrTestCode = "root\n";
	SendAsciiData(StrTestCode);
	Wait(200);

	//2016-09-29 암호추가
	StrTestCode = "fab123\n";
	SendAsciiData(StrTestCode);
	Wait(500);

	StrTestCode = "\n\ncd\n";
	SendAsciiData(StrTestCode);
	Wait(200);

	StrTestCode = "./utils/manufacture\n";
	SendAsciiData(StrTestCode);
	Wait(200);

	AllButtonEnable();
}


void CIOTManufactureDlg::OnBnClickedButtonSerialNumber()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	char* sourcechar;
	char  DateTimechar[30];
	char  Modelnumber[30];
	char  Serialnumber[30];

	CString   strDatetime, strModelNum, strSerialNum, SerialSendData;

	if (IDNO == AfxMessageBox(_T("Serial Number를 입력하시겠습니까?"), MB_YESNO))
	{
		return;
	}

	CTime cTime = CTime::GetCurrentTime();
	CString strTime;
	strTime.Format(_T("%02d시 %02d분 %02d초"), cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond()); // 현재 초 반환

	int resultv;

	UpdateData(TRUE);
	AllButtonDisable();

	memset(DateTimechar, 0, 30);
	memset(Modelnumber, 0, 30);
	memset(Serialnumber, 0, 30);

	int sLen = WideCharToMultiByte(CP_ACP, 0, m_strSerialNum, -1, NULL, 0, NULL, NULL);
	sourcechar = new char[sLen + 1];
	WideCharToMultiByte(CP_ACP, 0, m_strSerialNum, -1, sourcechar, sLen, NULL, NULL);

	m_ResultFlag = VIEWSERIAL;

	memcpy(DateTimechar, sourcechar + 6, 6);
	memcpy(Modelnumber, sourcechar + 12, 3);
	memcpy(Serialnumber, sourcechar + 15, 4);

	strDatetime = char2CString(DateTimechar);
	strModelNum = char2CString(Modelnumber);
	strSerialNum = char2CString(Serialnumber);

	SerialSendData = "\n0\n";
	SendAsciiData(SerialSendData);
	Wait(200);

	SerialSendData = strDatetime + '\n';
	SendAsciiData(SerialSendData);
	Wait(200);

	SerialSendData = strModelNum + '\n';
	SendAsciiData(SerialSendData);
	Wait(200);

	SerialSendData = strSerialNum + '\n';
	SendAsciiData(SerialSendData);
	Wait(400);

	//resultv = CSerialComDlg::WaitSting( "enter key", 40);
	resultv = GetterResult.Find(_T("enter key"));
	//resultv = 1;
	if (resultv != -1) {
		//리스트에 값을 입력한다.
		m_RptSERIAL = m_strSerialNum;
		//여기 까지 제대로 되었다면 시리얼 키를 저장한다.
		m_listExcelCtrl.InsertItem(0, _T("1231513453"), 0); //컬럼줄
		m_listExcelCtrl.SetItemText(0, 0, m_RptSERIAL);
		m_listExcelCtrl.SetItemText(0, 1, m_RptETH0MAC);
		m_listExcelCtrl.SetItemText(0, 2, m_RptETH1MAC);
		m_listExcelCtrl.SetItemText(0, 3, m_RptWLAN0MAC);
		m_listExcelCtrl.SetItemText(0, 4, m_RptMEMTEST);
		m_listExcelCtrl.SetItemText(0, 5, m_RptEMMCTEST);
		m_listExcelCtrl.SetItemText(0, 6, m_RptFLASHTEST);
		m_listExcelCtrl.SetItemText(0, 7, m_RptOLEDTEST);
		m_listExcelCtrl.SetItemText(0, 8, m_RptTESTETH0);
		m_listExcelCtrl.SetItemText(0, 9, m_RptTESTETH1);
		m_listExcelCtrl.SetItemText(0, 10, m_RptTESTWIFI);
		m_listExcelCtrl.SetItemText(0, 11, m_strDBM);
		m_listExcelCtrl.SetItemText(0, 12, strTime);
	}
	m_ResultFlag = 0;

	AllButtonEnable();
#if 0
	//혹시 데이터 소실을 방지 하기 위해 엑셀에 미리 미리 저장한다.
	if (m_listExcelCtrl.GetItemCount() <= 0)
	{
		AfxMessageBox(_T("조회된 데이터가 0건이므로 엑셀 저장 할 수 없습니다."));
		return;
	}
#endif
	CTime timeNow = CTime::GetCurrentTime();
	CString strDateTime;
	strDateTime = timeNow.Format(_T("%Y-%m-%d_%H%M%S"));
	CString strFileName;
	strFileName.Format(_T("CIM_TEST_%s_%s"), strDateTime, m_strSerialNum);

	CFileDialog fdlg(FALSE, _T("xlsx"), strFileName + ".xlsx", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR, _T("xlsx 파일 (*.xlsx)|*.xlsx"), NULL);
	if (fdlg.DoModal() != IDOK)
	{
		AfxMessageBox(_T("파일을 오픈 할 수 없습니다."));
		return;
	}

	CXLEzAutomation xls(FALSE);  // FALSE : 처리 과정을 화면에 보이지 않는다.

	int rowOffset = 2; //시작 컬럼
	int colOffset = 1; //시작 컬럼

	int rowCount = m_listExcelCtrl.GetItemCount();
	CHeaderCtrl* pHeaderCtrl = m_listExcelCtrl.GetHeaderCtrl();
	int colCount = pHeaderCtrl->GetItemCount();

	CString strItemText;
	xls.SetCellValue(0 + 1, 0 + 1, _T("시리얼번호"));
	xls.SetCellValue(1 + 1, 0 + 1, _T("MAC Eth0"));
	xls.SetCellValue(2 + 1, 0 + 1, _T("MAC Eth1"));
	xls.SetCellValue(3 + 1, 0 + 1, _T("MAC WIFI"));
	xls.SetCellValue(4 + 1, 0 + 1, _T("MEMORY TEST"));
	xls.SetCellValue(5 + 1, 0 + 1, _T("EMMC TEST"));
	xls.SetCellValue(6 + 1, 0 + 1, _T("FLASH TEST"));
	xls.SetCellValue(7 + 1, 0 + 1, _T("LED TEST"));
	xls.SetCellValue(8 + 1, 0 + 1, _T("ETH0 TEST"));
	xls.SetCellValue(9 + 1, 0 + 1, _T("ETH1 TEST"));
	xls.SetCellValue(10 + 1, 0 + 1, _T("WIFI TEST"));
	xls.SetCellValue(11 + 1, 0 + 1, _T("RSSI"));
	xls.SetCellValue(12 + 1, 0 + 1, _T("TIME"));
	for (int rowIdx = 0; rowIdx < rowCount; rowIdx++)
	{
		for (int colIdx = 0; colIdx < colCount; colIdx++)
		{
			strItemText = m_listExcelCtrl.GetItemText(rowIdx, colIdx);
			// 컬럼 데이터
			xls.SetCellValue(colIdx + colOffset, rowIdx + rowOffset, strItemText);
		}
	}
	xls.SaveFileAs(fdlg.GetPathName());
	xls.ReleaseExcel();

	m_strSerialNum = _T("");

	m_RptETH0MAC = _T("");
	m_RptETH1MAC = _T("");
	m_RptWLAN0MAC = _T("");
	m_RptSERIAL = _T("");

	m_RptTESTETH0 = _T("");
	m_RptTESTETH1 = _T("");
	m_RptTESTWIFI = _T("");

	m_RptMEMTEST = _T("");
	m_RptOLEDTEST = _T("");
	m_RptEMMCTEST = _T("");

	GetterResult = _T("");

	SetDlgItemText(IDC_STATIC_VIEWMACS, _T(""));

	m_CommonDlg.SetDlgItemText(IDC_STATIC_VIEWMACS, _T("Need Read!!"));
	m_CommonDlg.SetDlgItemText(IDC_STATIC_RSSI, _T("RSSI :"));
	m_CommonDlg.SetDlgItemText(IDC_STATIC_MEMORY_RESULT, _T("Ready"));
	m_CommonDlg.SetDlgItemText(IDC_STATIC_EMMC_RESULT, _T("Ready"));
	m_CommonDlg.SetDlgItemText(IDC_STATIC_FLASH_RESULT, _T("Ready"));
	m_CommonDlg.SetDlgItemText(IDC_STATIC_OLED_RESULT, _T("Ready"));
	m_CommonDlg.SetDlgItemText(IDC_STATIC_ETH0_RESULT, _T("Ready"));
	m_CommonDlg.SetDlgItemText(IDC_STATIC_ETH1_RESULT, _T("Ready"));
	m_CommonDlg.SetDlgItemText(IDC_STATIC_WLAN0_RESULT, _T("Ready"));
	
	SerialSendData = "\n";
	SendAsciiData(SerialSendData);
	Wait(100);
	AllButtonDisable();
}


void CIOTManufactureDlg::OnCbnSelchangeComboModel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CTime timeNow = CTime::GetCurrentTime();
	CString strDateTime;
	CString strModel;
#if 0
	int nIndex = m_comboModel.GetCurSel();
	if (nIndex == 0)
		strModel = DIGITAL_BOX;
	else if (nIndex == 1)
		strModel = IOLINK_BOX;
	else if (nIndex == 2)
		strModel = ANALOG_BOX;
	else if (nIndex == 3)
		strModel = VIB_BOX;
#endif

	strModel = SDC_CIM;

	strDateTime = timeNow.Format(_T("%Y%m%d")) + strModel + _T("0001");
	strDateTime.Delete(0, 2);

	CString SumStrSerial;
	SumStrSerial = _T("MVTECH") + strDateTime;
	GetDlgItem(IDC_EDIT_SERIAL_NUMBER)->SetWindowText(SumStrSerial);
}


void CIOTManufactureDlg::OnBnClickedButtonSerialInc()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	int len = m_strSerialNum.GetLength();
	CString strSerialModel = m_strSerialNum.Mid(0, 15);
	CString strNumber = m_strSerialNum.Mid(15, len - 15);

	//MVTECH210408SE10001
	int nNum = _ttoi(strNumber);
	//if (m_strSerialNum.)
	m_strSerialNum.Format(_T("%04d"), nNum + 1);
	m_strSerialNum = strSerialModel + m_strSerialNum;
	GetDlgItem(IDC_EDIT_SERIAL_NUMBER)->SetWindowText(m_strSerialNum);
	//AllButtonEnable();
}


void CIOTManufactureDlg::OnBnClickedButtonExcelSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_listExcelCtrl.GetItemCount() <= 0)
	{
		AfxMessageBox(_T("조회된 데이터가 0건이므로 엑셀 저장 할 수 없습니다."));
		return;
	}

	CTime timeNow = CTime::GetCurrentTime();
	CString strDateTime;
	strDateTime = timeNow.Format(_T("%Y-%m-%d_%H%M%S"));
	CString strFileName;
	strFileName.Format(_T("CIMTEST_%s"), strDateTime);

	CFileDialog fdlg(FALSE, _T("xlsx"), strFileName + ".xlsx", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR, _T("xlsx 파일 (*.xlsx)|*.xlsx"), NULL);
	if (fdlg.DoModal() != IDOK) return;
	CXLEzAutomation xls(FALSE);  // FALSE : 처리 과정을 화면에 보이지 않는다.

	int rowOffset = 2; //시작 컬럼
	int colOffset = 1; //시작 컬럼

	int rowCount = m_listExcelCtrl.GetItemCount();
	CHeaderCtrl* pHeaderCtrl = m_listExcelCtrl.GetHeaderCtrl();
	int colCount = pHeaderCtrl->GetItemCount();

	CString strItemText;
	xls.SetCellValue(0 + 1, 0 + 1, _T("시리얼번호"));
	xls.SetCellValue(1 + 1, 0 + 1, _T("MAC Eth0"));
	xls.SetCellValue(2 + 1, 0 + 1, _T("MAC Eth1"));
	xls.SetCellValue(3 + 1, 0 + 1, _T("MAC WIFI"));
	xls.SetCellValue(4 + 1, 0 + 1, _T("MEMORY TEST"));
	xls.SetCellValue(5 + 1, 0 + 1, _T("EMMC TEST"));
	xls.SetCellValue(6 + 1, 0 + 1, _T("FLASH TEST"));
	xls.SetCellValue(7 + 1, 0 + 1, _T("LED TEST"));
	xls.SetCellValue(8 + 1, 0 + 1, _T("ETH0 TEST"));
	xls.SetCellValue(9 + 1, 0 + 1, _T("ETH1 TEST"));
	xls.SetCellValue(10 + 1, 0 + 1, _T("WLAN0 TEST"));
	xls.SetCellValue(11 + 1, 0 + 1, _T("RSSI"));
	xls.SetCellValue(12 + 1, 0 + 1, _T("TIME"));

	for (int rowIdx = 0; rowIdx < rowCount; rowIdx++)
	{
		for (int colIdx = 0; colIdx < colCount; colIdx++)
		{
			strItemText = m_listExcelCtrl.GetItemText(rowIdx, colIdx);
			// 컬럼 데이터
			xls.SetCellValue(colIdx + colOffset, rowIdx + rowOffset, strItemText);
		}
	}
	xls.SaveFileAs(fdlg.GetPathName());
	xls.ReleaseExcel();
}
