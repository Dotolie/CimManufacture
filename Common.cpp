// Common.cpp: 구현 파일
//

#include "pch.h"
#include "IOTManufacture.h"
#include "Common.h"
#include "afxdialogex.h"
#include "IOTManufactureDlg.h"

UINT ThreadForCounting(LPVOID param);
// CCommon 대화 상자

IMPLEMENT_DYNAMIC(CCommon, CDialogEx)

CCommon::CCommon(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_COMMON, pParent)
{
	m_pAautoDlg = NULL;
}

CCommon::~CCommon()
{
}

void CCommon::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCommon, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_MEM_TEST, &CCommon::OnBnClickedButtonMemTest)
	ON_BN_CLICKED(IDC_BUTTON_EMMC_TEST, &CCommon::OnBnClickedButtonEmmcTest)
	ON_BN_CLICKED(IDC_BUTTON_LED_TEST, &CCommon::OnBnClickedButtonLedTest)
	ON_BN_CLICKED(IDC_BUTTON_ETH0_TEST, &CCommon::OnBnClickedButtonEth0Test)
	ON_BN_CLICKED(IDC_BUTTON_ETH1_TEST, &CCommon::OnBnClickedButtonEth1Test)
	ON_BN_CLICKED(IDC_BUTTON_WLAN_TEST, &CCommon::OnBnClickedButtonWlanTest)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_AUTO_TEST, &CCommon::OnBnClickedButtonAutoTest)
	ON_BN_CLICKED(IDC_BUTTON_FLASH_TEST, &CCommon::OnBnClickedButtonFlashTest)
END_MESSAGE_MAP()


// CCommon 메시지 처리기


void CCommon::OnBnClickedButtonMemTest()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString StrTestCode;
	int rst, cntNULL = 0, cntTime = 0;
	int nLen = 0;

	CIOTManufactureDlg* pDlg = (CIOTManufactureDlg*)AfxGetApp()->GetMainWnd();

	pDlg->m_ResultFlag = TEST_MEMORY;
	pDlg->AllButtonDisable();

	StrTestCode = "1\n";
	pDlg->SendAsciiData(StrTestCode);
	pDlg->Wait(1000);

	while (1)
	{
		TRACE("MemTest : %d , %d!! \n", cntNULL, cntTime);

		if (pDlg->m_Comm.m_bConnected == false)
			break;

		cntTime++;
		nLen = pDlg->GetterResult.GetLength();
		if (nLen == 0 || cntTime >= 150) {
			cntNULL++;
			if (cntNULL >= 300) {
				pDlg->m_ResultFlag = 0;
				pDlg->AllButtonEnable();
				pDlg->m_RptMEMTEST = "NG";
				StrTestCode = "\n";
				pDlg->SendAsciiData(StrTestCode);
				return;
			}
		}
		else {
			cntNULL = 0;
		}

		rst = pDlg->GetterResult.Find(_T("press enter key"));
		if (rst > 0)
		{
			TRACE("press enter key detected !! \n");
			break;
		}
		else {
			TRACE("Buffer Clear !! %d\n", nLen);
			pDlg->GetterResult = _T("");
		}

		pDlg->Wait(500);
	}

	rst = pDlg->GetterResult.Find(_T("Done."));

	if (rst > 0)
	{
		pDlg->m_RptMEMTEST = "OK";

		//AfxMessageBox(_T("Memory Success."), MB_ICONINFORMATION | MB_OK);

	}
	else {
		pDlg->m_RptMEMTEST = "NG";
		//AfxMessageBox(_T("Memory Fail."), MB_ICONINFORMATION | MB_OK);
	}

	StrTestCode = "\n";
	pDlg->SendAsciiData(StrTestCode);

	//if (!m_ListExcelCtrl.GetItemCount())
	//	m_ListExcelCtrl.InsertItem(0, m_strSerialNum, 0); //컬럼줄
	//m_ListExcelCtrl.SetItemText(0, 4, m_RptMEMTEST);

	GetDlgItem(IDC_STATIC_MEMORY_RESULT)->SetWindowText(pDlg->m_RptMEMTEST);
	if (m_pAautoDlg) {
		if (m_pAautoDlg->IsWindowVisible() == TRUE)
			m_pAautoDlg->GetDlgItem(IDC_STATIC_MEMORY_RESULT)->SetWindowText(pDlg->m_RptMEMTEST);
	}

	pDlg->AllButtonEnable();
	pDlg->m_ResultFlag = 0;
	pDlg->GetterResult = _T("");
	return;
}


void CCommon::OnBnClickedButtonEmmcTest()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString StrTestCode;
	int rst, cntNULL = 0, cntTime = 0;

	CIOTManufactureDlg* pDlg = (CIOTManufactureDlg*)AfxGetApp()->GetMainWnd();

	pDlg->m_ResultFlag = TEST_EMMC;
	pDlg->AllButtonDisable();

	StrTestCode = "2\n";
	pDlg->SendAsciiData(StrTestCode);
	pDlg->Wait(1000);

	while (1)
	{
		TRACE("cntNULL : %d , %d!! \n", cntNULL, cntTime);

		if (pDlg->m_Comm.m_bConnected == false)
			break;

		cntTime++;
		if (pDlg->GetterResult.GetLength() == 0 || cntTime >= 100) {
			cntNULL++;
			if (cntNULL >= 5) {
				pDlg->m_ResultFlag = 0;
				pDlg->AllButtonEnable();
				pDlg->m_RptEMMCTEST = "NG";
				return;
			}
		}
		else {
			cntNULL = 0;
		}

		rst = pDlg->GetterResult.Find(_T("press enter key"));
		if (rst >= 1) {
			rst = 1;
		}

		if (rst > 0)
		{
			TRACE("100 percent detected !! \n");
			break;
		}
		else {
			TRACE("Buffer Clear !! \n");
			pDlg->GetterResult = _T("");
		}
		pDlg->Wait(500);

	}

	rst = pDlg->GetterResult.Find(_T("remove success"));

	if (rst > 0)
	{
		pDlg->m_RptEMMCTEST = "OK";
		//AfxMessageBox(_T("eMMC Success."), MB_ICONINFORMATION | MB_OK);
	}
	else {
		pDlg->m_RptEMMCTEST = "NG";
		//AfxMessageBox(_T("eMMC Fail."), MB_ICONINFORMATION | MB_OK);
	}

	StrTestCode = "\n";
	pDlg->SendAsciiData(StrTestCode);

	//if (!m_ListExcelCtrl.GetItemCount())
	//	m_ListExcelCtrl.InsertItem(0, m_strSerialNum, 0); //컬럼줄
	//m_ListExcelCtrl.SetItemText(0, 5, m_RptEMMCTEST);

	GetDlgItem(IDC_STATIC_EMMC_RESULT)->SetWindowText(pDlg->m_RptEMMCTEST);
	if (m_pAautoDlg) {
		if (m_pAautoDlg->IsWindowVisible() == TRUE)
			m_pAautoDlg->GetDlgItem(IDC_STATIC_EMMC_RESULT)->SetWindowText(pDlg->m_RptEMMCTEST);
	}

	pDlg->m_ResultFlag = 0;
	pDlg->AllButtonEnable();
}


void CCommon::OnBnClickedButtonLedTest()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString StrTestCode;
	int rst, cntNULL = 0, cntTime = 0;

	CIOTManufactureDlg* pDlg = (CIOTManufactureDlg*)AfxGetApp()->GetMainWnd();

	pDlg->m_ResultFlag = TEST_OLED;
	pDlg->AllButtonDisable();

	StrTestCode = "3\n";
	pDlg->SendAsciiData(StrTestCode);
	pDlg->Wait(1000);

	while (1)
	{
		TRACE("cntNULL : %d , %d!! \n", cntNULL, cntTime);

		if (pDlg->m_Comm.m_bConnected == false)
			break;

		cntTime++;
		if (pDlg->GetterResult.GetLength() == 0 || cntTime >= 50) {
			cntNULL++;
			if (cntNULL >= 10) {
				pDlg->m_ResultFlag = 0;
				pDlg->AllButtonEnable();
				pDlg->m_RptOLEDTEST = "NG";
				return;
			}
		}
		else {
			cntNULL = 0;
		}

		rst = pDlg->GetterResult.Find(_T("press enter key"));
		if (rst > 0)
		{
			TRACE("100 percent detected !! \n");
			pDlg->GetterResult = _T("");
			break;
		}
		else {
			TRACE("Buffer Clear !! \n");
			pDlg->GetterResult = _T("");
		}
		pDlg->Wait(1000);
	}

	StrTestCode = "\n";
	pDlg->SendAsciiData(StrTestCode);

	//if (!m_ListExcelCtrl.GetItemCount())
	//	m_ListExcelCtrl.InsertItem(0, m_strSerialNum, 0); //컬럼줄
	//m_ListExcelCtrl.SetItemText(0, 6, m_RptOLEDTEST);

	pDlg->m_ResultFlag = 0;

	if (IDYES == AfxMessageBox(_T("[육안검사] 적색 과 녹색 LED 3개가 번갈아 켜졌나요?"), MB_YESNO))
		pDlg->m_RptOLEDTEST = "OK";
	else
		pDlg->m_RptOLEDTEST = "NG";

	GetDlgItem(IDC_STATIC_OLED_RESULT)->SetWindowText(pDlg->m_RptOLEDTEST);
	if (m_pAautoDlg) {
		if (m_pAautoDlg->IsWindowVisible() == TRUE)
			m_pAautoDlg->GetDlgItem(IDC_STATIC_OLED_RESULT)->SetWindowText(pDlg->m_RptOLEDTEST);
	}

	pDlg->AllButtonEnable();
}


void CCommon::OnBnClickedButtonEth0Test()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString StrSerialCode;
	int rst, cntNULL = 0, cntTime = 0;

	CIOTManufactureDlg* pDlg = (CIOTManufactureDlg*)AfxGetApp()->GetMainWnd();

	AfxMessageBox(_T("랜 0번 케이블을 꽂아 주세요."), MB_ICONINFORMATION | MB_OK);

	pDlg->m_ResultFlag = TEST_ETH0;
	pDlg->AllButtonDisable();

	StrSerialCode = "\n4\n";
	pDlg->SendAsciiData(StrSerialCode);

	StrSerialCode = "\n";
	pDlg->SendAsciiData(StrSerialCode);

	while (1)
	{
		TRACE("cntNULL : %d , %d!! \n", cntNULL, cntTime);

		if (pDlg->m_Comm.m_bConnected == false)
			break;

		cntTime++;
		if (pDlg->GetterResult.GetLength() == 0 || cntTime >= 100) {
			cntNULL++;
			if (cntNULL >= ETHERNET_WAIT_TIME) {
				pDlg->m_ResultFlag = 0;
				pDlg->AllButtonEnable();
				pDlg->m_RptTESTETH0 = "NG";
				return;
			}
		}
		else {
			cntNULL = 0;
		}
		TRACE(pDlg->GetterResult);
		rst = pDlg->GetterResult.Find(_T("network(eth0)"));
		if (rst > 0)
		{
			TRACE("100 percent detected !! \n");
			break;
		}
		else {
			TRACE("Buffer Clear !! \n");
			pDlg->GetterResult = _T("");
		}
		pDlg->Wait(1000);
	}

	rst = pDlg->GetterResult.Find(_T("NETWORK (eth0) TEST SUCCESS"));
	if (rst > 0)
	{
		pDlg->m_RptTESTETH0 = "OK";
		//AfxMessageBox(_T("NETWORK (eth0) Success."), MB_ICONINFORMATION | MB_OK);
	}
	else {
		pDlg->m_RptTESTETH0 = "NG";
		//AfxMessageBox(_T("NETWORTK (eth0) Fail."), MB_ICONINFORMATION | MB_OK);
	}

	StrSerialCode = "\n";
	pDlg->SendAsciiData(StrSerialCode);

	//if (!m_ListExcelCtrl.GetItemCount())
	//	m_ListExcelCtrl.InsertItem(0, m_strSerialNum, 0); //컬럼줄
	//m_ListExcelCtrl.SetItemText(0, 7, m_RptTESTETH0);

	GetDlgItem(IDC_STATIC_ETH0_RESULT)->SetWindowText(pDlg->m_RptTESTETH0);
	if (m_pAautoDlg) {
		if (m_pAautoDlg->IsWindowVisible() == TRUE)
			m_pAautoDlg->GetDlgItem(IDC_STATIC_ETH0_RESULT)->SetWindowText(pDlg->m_RptTESTETH0);
	}

	pDlg->m_ResultFlag = 0;
	pDlg->AllButtonEnable();
}


void CCommon::OnBnClickedButtonEth1Test()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString StrSerialCode;
	int rst, cntNULL = 0, cntTime = 0;

	CIOTManufactureDlg* pDlg = (CIOTManufactureDlg*)AfxGetApp()->GetMainWnd();

	AfxMessageBox(_T("랜 1번 케이블을 꽂아 주세요."), MB_ICONINFORMATION | MB_OK);

	pDlg->m_ResultFlag = TEST_ETH1;
	pDlg->AllButtonDisable();

	StrSerialCode = "\n5\n";
	pDlg->SendAsciiData(StrSerialCode);

	StrSerialCode = "\n";
	pDlg->SendAsciiData(StrSerialCode);

	while (1)
	{
		TRACE("cntNULL : %d , %d!! \n", cntNULL, cntTime);

		if (pDlg->m_Comm.m_bConnected == false)
			break;

		cntTime++;
		if (pDlg->GetterResult.GetLength() == 0 || cntTime >= 200) {
			cntNULL++;
			if (cntNULL >= ETHERNET_WAIT_TIME) {
				pDlg->m_ResultFlag = 0;
				pDlg->AllButtonEnable();
				pDlg->m_RptTESTETH1 = "NG";
				return;
			}
		}
		else {
			cntNULL = 0;
		}

		rst = pDlg->GetterResult.Find(_T("network(eth1)"));
		if (rst > 0)
		{
			TRACE("100 percent detected !! \n");
			break;
		}
		else {
			TRACE("Buffer Clear !! \n");
			pDlg->GetterResult = _T("");
		}
		pDlg->Wait(1000);
	}

	rst = pDlg->GetterResult.Find(_T("NETWORK (eth1) TEST SUCCESS"));
	if (rst > 0)
	{
		pDlg->m_RptTESTETH1 = "OK";
		//AfxMessageBox(_T("NETWORK (eth1) Success."), MB_ICONINFORMATION | MB_OK);
	}
	else {
		pDlg->m_RptTESTETH1 = "NG";
		//AfxMessageBox(_T("NETWORK (eth1) Fail."), MB_ICONINFORMATION | MB_OK);
	}

	StrSerialCode = "\n";
	pDlg->SendAsciiData(StrSerialCode);

	//if (!m_ListExcelCtrl.GetItemCount())
	//	m_ListExcelCtrl.InsertItem(0, m_strSerialNum, 0); //컬럼줄
	//m_ListExcelCtrl.SetItemText(0, 8, m_RptTESTETH1);

	GetDlgItem(IDC_STATIC_ETH1_RESULT)->SetWindowText(pDlg->m_RptTESTETH1);
	if (m_pAautoDlg) {
		if (m_pAautoDlg->IsWindowVisible() == TRUE)
			m_pAautoDlg->GetDlgItem(IDC_STATIC_ETH1_RESULT)->SetWindowText(pDlg->m_RptTESTETH1);
	}

	pDlg->m_ResultFlag = 0;
	pDlg->GetterResult = _T("");
	pDlg->AllButtonEnable();
}


void CCommon::OnBnClickedButtonWlanTest()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString StrSerialCode;
	CString StrRSSI;
	int rst, cntNULL = 0, cntTime = 0;

	CIOTManufactureDlg* pDlg = (CIOTManufactureDlg*)AfxGetApp()->GetMainWnd();

	pDlg->m_ResultFlag = TEST_WLAN0;
	pDlg->AllButtonDisable();

	StrSerialCode = "\n6\n";
	pDlg->SendAsciiData(StrSerialCode);

	while (1)
	{
		TRACE("cntNULL : %d , %d!! \n", cntNULL, cntTime);

		if (pDlg->m_Comm.m_bConnected == false)
			break;

		cntTime++;
		if (pDlg->GetterResult.GetLength() == 0 || cntTime >= 200) {
			cntNULL++;
			if (cntNULL >= ETHERNET_WAIT_TIME) {
				pDlg->m_ResultFlag = 0;
				pDlg->AllButtonEnable();
				pDlg->m_RptTESTWIFI = "NG";
				return;
			}
		}
		else {
			cntNULL = 0;
		}

		rst = pDlg->GetterResult.Find(_T("network(wlan0) test"));
		if (rst > 0)
		{
			TRACE("100 percent detected !! \n");
			break;
		}
		else
		{
			TRACE("Buffer Clear !! \n");
			pDlg->GetterResult = _T("");
		}
		pDlg->Wait(1000);
	}

	rst = pDlg->GetterResult.Find(_T("network(wlan0) test success"));
	if (rst > 0)
	{
		pDlg->m_RptTESTWIFI = "OK";
		rst = pDlg->GetterResult.Find(_T("signal:"));
		if (rst > 0)
		{
			pDlg->m_strDBM = pDlg->GetterResult.Mid(rst + 10, 4);
		}

		StrRSSI = _T("RSSI : ") + pDlg->m_strDBM;
		//AfxMessageBox(_T("NETWORK (wlan0) Success") + m_strDBM, MB_ICONINFORMATION | MB_OK);
	}
	else {
		pDlg->m_RptTESTWIFI = "NG";
		//AfxMessageBox(_T("NETWORK (wlan0) Fail."), MB_ICONINFORMATION | MB_OK);
	}

	StrSerialCode = "\n";
	pDlg->SendAsciiData(StrSerialCode);

	//if (!m_ListExcelCtrl.GetItemCount())
	//	m_ListExcelCtrl.InsertItem(0, m_strSerialNum, 0); //컬럼줄
	//m_ListExcelCtrl.SetItemText(0, 9, m_RptTESTWIFI);
	//m_ListExcelCtrl.SetItemText(0, 10, m_strDBM);

	GetDlgItem(IDC_STATIC_RSSI)->SetWindowText(StrRSSI);
	GetDlgItem(IDC_STATIC_WLAN0_RESULT)->SetWindowText(pDlg->m_RptTESTWIFI);
	if (m_pAautoDlg) {
		if (m_pAautoDlg->IsWindowVisible() == TRUE)
			m_pAautoDlg->GetDlgItem(IDC_STATIC_WLAN0_RESULT)->SetWindowText(pDlg->m_RptTESTWIFI);
	}

	pDlg->m_ResultFlag = 0;
	pDlg->GetterResult = _T("");
	pDlg->AllButtonEnable();
}


void CCommon::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
}


HBRUSH CCommon::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	CIOTManufactureDlg* pDlg = (CIOTManufactureDlg*)AfxGetMainWnd();

	if (pWnd->GetDlgCtrlID() == IDC_STATIC_MEMORY_RESULT)
	{
		if (pDlg->m_RptMEMTEST.Compare(_T("OK")) == 0)
			pDC->SetTextColor(RGB(0, 0, 255));
		else
			pDC->SetTextColor(RGB(255, 0, 0));
	}

	if (pWnd->GetDlgCtrlID() == IDC_STATIC_EMMC_RESULT)
	{
		if (pDlg->m_RptEMMCTEST.Compare(_T("OK")) == 0)
			pDC->SetTextColor(RGB(0, 0, 255));
		else
			pDC->SetTextColor(RGB(255, 0, 0));
	}

	if (pWnd->GetDlgCtrlID() == IDC_STATIC_FLASH_RESULT)
	{
		if (pDlg->m_RptFLASHTEST.Compare(_T("OK")) == 0)
			pDC->SetTextColor(RGB(0, 0, 255));
		else
			pDC->SetTextColor(RGB(255, 0, 0));
	}

	if (pWnd->GetDlgCtrlID() == IDC_STATIC_OLED_RESULT)
	{
		if (pDlg->m_RptOLEDTEST.Compare(_T("OK")) == 0)
			pDC->SetTextColor(RGB(0, 0, 255));
		else
			pDC->SetTextColor(RGB(255, 0, 0));
	}

	if (pWnd->GetDlgCtrlID() == IDC_STATIC_ETH0_RESULT)
	{
		if (pDlg->m_RptTESTETH0.Compare(_T("OK")) == 0)
			pDC->SetTextColor(RGB(0, 0, 255));
		else
			pDC->SetTextColor(RGB(255, 0, 0));
	}

	if (pWnd->GetDlgCtrlID() == IDC_STATIC_ETH1_RESULT)
	{
		if (pDlg->m_RptTESTETH1.Compare(_T("OK")) == 0)
			pDC->SetTextColor(RGB(0, 0, 255));
		else
			pDC->SetTextColor(RGB(255, 0, 0));
	}

	if (pWnd->GetDlgCtrlID() == IDC_STATIC_WLAN0_RESULT)
	{
		if (pDlg->m_RptTESTWIFI.Compare(_T("OK")) == 0)
			pDC->SetTextColor(RGB(0, 0, 255));
		else
			pDC->SetTextColor(RGB(255, 0, 0));
	}
	/*
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_TEST_MONITOR)
	{
		pDC->SetTextColor(RGB(255, 0, 0));
	}
	*/
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_RSSI)
	{
		pDC->SetTextColor(RGB(255, 0, 255));
	}

	return hbr;
}


void CCommon::OnBnClickedButtonAutoTest()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	RECT  rectParent;
	CRect rect;
	CPoint pos;

	CIOTManufactureDlg* pDlg = (CIOTManufactureDlg*)AfxGetApp()->GetMainWnd();

	if (m_pAautoDlg == NULL)
	{
		m_pAautoDlg = new CAutoTest;
		m_pAautoDlg->Create(IDD_DIALOG_AUTO_TEST);
	}		

	pDlg->GetWindowRect(&rectParent);
	m_pAautoDlg->GetClientRect(&rect); // 출력할 다이얼로그의 영역을 얻는다.

	// 시작지점 지정
	pos.x = rectParent.left + (rectParent.right - rectParent.left) / 2 - rect.Width() / 2;
	pos.y = rectParent.top + (rectParent.bottom - rectParent.top) / 2 - rect.Height() / 2;

	// 표시위치 지정
	m_pAautoDlg->SetWindowPos(NULL, pos.x, pos.y, 0, 0, SWP_NOSIZE);

	BOOL chk = m_pAautoDlg->IsWindowVisible();
	if (chk)
	{
		m_pAautoDlg->ShowWindow(SW_HIDE);
	}
	else
	{
		m_pAautoDlg->ShowWindow(SW_SHOW);
	}

	m_isWorkingThread = true;

	m_pThread = AfxBeginThread(ThreadForCounting, this);
}

UINT ThreadForCounting(LPVOID param)
{
	CCommon* pMain = (CCommon*)param;
	CIOTManufactureDlg* pDlg = (CIOTManufactureDlg*)AfxGetApp()->GetMainWnd();

	pMain->OnBnClickedButtonMemTest();
	if (pMain->m_pAautoDlg->IsWindowVisible() == FALSE)
		return 0;
	pMain->OnBnClickedButtonEmmcTest();
	if (pMain->m_pAautoDlg->IsWindowVisible() == FALSE)
		return 0;
	pMain->OnBnClickedButtonFlashTest();
	if (pMain->m_pAautoDlg->IsWindowVisible() == FALSE)
		return 0;
	pMain->OnBnClickedButtonEth0Test();
	if (pMain->m_pAautoDlg->IsWindowVisible() == FALSE)
		return 0;
	pMain->OnBnClickedButtonEth1Test();
	if (pMain->m_pAautoDlg->IsWindowVisible() == FALSE)
		return 0;
	pMain->OnBnClickedButtonWlanTest();
	if (pMain->m_pAautoDlg->IsWindowVisible() == FALSE)
		return 0;
	pMain->OnBnClickedButtonLedTest();
	if (pMain->m_pAautoDlg->IsWindowVisible() == FALSE)
		return 0;
	/*
	while (pMain->m_isWorkingThread)
	{
		Sleep(30);

		//Do something...
	}
	*/
	return 0;
}


void CCommon::OnBnClickedButtonFlashTest()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString StrTestCode;
	int rst, cntNULL = 0, cntTime = 0;

	CIOTManufactureDlg* pDlg = (CIOTManufactureDlg*)AfxGetApp()->GetMainWnd();

	pDlg->m_ResultFlag = TEST_FLASH;
	pDlg->AllButtonDisable();

	StrTestCode = "f\n";
	pDlg->SendAsciiData(StrTestCode);
	pDlg->Wait(1000);

	while (1)
	{
		TRACE("cntNULL : %d , %d!! \n", cntNULL, cntTime);

		if (pDlg->m_Comm.m_bConnected == false)
			break;

		cntTime++;
		if (pDlg->GetterResult.GetLength() == 0 || cntTime >= 100) {
			cntNULL++;
			if (cntNULL >= 15) {
				pDlg->m_ResultFlag = 0;
				pDlg->AllButtonEnable();
				pDlg->m_RptFLASHTEST = "NG";
				return;
			}
		}
		else {
			cntNULL = 0;
		}

		rst = pDlg->GetterResult.Find(_T("fpga_ddwrite complete"));
		if (rst >= 1) {
			rst = 1;
		}

		if (rst > 0)
		{
			TRACE("100 percent detected !! \n");
			break;
		}
		else {
			TRACE("Buffer Clear !! \n");
			pDlg->GetterResult = _T("");
		}
		pDlg->Wait(500);

	}

	rst = pDlg->GetterResult.Find(_T("fpga update time"));

	if (rst > 0)
	{
		pDlg->m_RptFLASHTEST = "OK";
		//AfxMessageBox(_T("FLASH Success."), MB_ICONINFORMATION | MB_OK);
	}
	else {
		pDlg->m_RptFLASHTEST = "NG";
		//AfxMessageBox(_T("FLASH Fail."), MB_ICONINFORMATION | MB_OK);
	}

	StrTestCode = "\n";
	pDlg->SendAsciiData(StrTestCode);

	//if (!m_ListExcelCtrl.GetItemCount())
	//	m_ListExcelCtrl.InsertItem(0, m_strSerialNum, 0); //컬럼줄
	//m_ListExcelCtrl.SetItemText(0, 5, m_RptFLASHTEST);

	GetDlgItem(IDC_STATIC_FLASH_RESULT)->SetWindowText(pDlg->m_RptFLASHTEST);
	if (m_pAautoDlg) {
		if (m_pAautoDlg->IsWindowVisible() == TRUE)
			m_pAautoDlg->GetDlgItem(IDC_STATIC_FLASH_RESULT)->SetWindowText(pDlg->m_RptFLASHTEST);
	}

	pDlg->m_ResultFlag = 0;
	pDlg->AllButtonEnable();
}
