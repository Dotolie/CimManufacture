
// IOTManufactureDlg.h: 헤더 파일
//

#pragma once
#include "CommThread.h"
#include "Common.h"
#include "AnalogBox.h"
#include "DigitalBox.h"
#include "IolinkBox.h"
#include "VibrationBox.h"

#define		TESTETH0		   0x10001
#define		TESTETH1		   0x10002
#define		TESTWIFI		   0x10003

#define     VIEWMAC		       0x10010
#define     VIEWSERIAL         0x10020

#define		TEST_MEMORY         0x10030
#define     TEST_EMMC			0x10040

#define		TEST_OLED		   0x10050
#define		TEST_ETH0		   0x10060

#define     TEST_ETH1			0x10070
#define     TEST_WLAN0			0x10080

#define		TEST_VIB			0x10090
#define     TEST_IOLINK			0x100A0
#define		TEST_DIGITAL        0x100B0
#define     TEST_ANALOG			0x100C0

#define     TEST_FLASH			0x100D0


#define     SERIALCODEA        'I'
#define     SERIALCODEB        'L'
#define     SERIALCODEC        '2'


#define		DIGITAL_BOX			_T("SE1")
#define		IOLINK_BOX			_T("IL2")
#define		ANALOG_BOX			_T("AL3")
#define		VIB_BOX				_T("VB4")

#define		SDC_CIM				_T("SD4")

#define ETHERNET_WAIT_TIME		20

// CIOTManufactureDlg 대화 상자
class CIOTManufactureDlg : public CDialogEx
{
// 생성입니다.
public:
	CIOTManufactureDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	CCommon m_CommonDlg;
	CDigitalBox m_DigitalDlg;
	CIolinkBox m_IolinkDlg;
	CAnalogBox m_AnalogDlg;
	CVibrationBox m_VibrationDlg;

	CWnd* m_pWndShow;
	CCommThread m_Comm;

	int m_iSize; //설정창에 시리얼로 들어온 데이터 갯수를 보여주기 위해  갯수를 받을 변수 
	int m_iCount;// 받은 데이터를 화면에 보여줄때 정렬 하기 위해 사용 한줄에 8묶음 2개 (16개 데이터)
	//int nMakeHexData(); //보낼 데이터 타입이 hex일 경우 hex데이터로 만들어서 전송
	//int nMakeAsciiData();//보낼 데이터 타입이 ascii일 경우 ascii데이터로 만들어서 전송
	int m_ResultFlag;
	int m_TestFlag;
	int ReadyTestFlag;

	int		m_iSendDataType;
	int		m_iReceiveDataType;

	CString GetterResult;

	CString m_RptETH0MAC;
	CString m_RptETH1MAC;
	CString m_RptWLAN0MAC;
	CString m_RptSERIAL;

	CString m_RptTESTETH0;
	CString m_RptTESTETH1;
	CString m_RptTESTWIFI;
	CString m_RptFLASHTEST;
	CString m_RptMEMTEST;
	CString m_RptEMMCTEST;
	CString m_RptOLEDTEST;
	CString  m_strComPortList[20];

	CString m_strDBM;

	CFont m_FontResult;;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IOTMANUFACTURE_DIALOG };
#endif

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
	afx_msg long OnCommunication(WPARAM wParam, LPARAM lParam);// 추가 시킨 내용
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnDropdownComboComport();
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CTabCtrl m_tabMenu;
	afx_msg void OnTcnSelchangeTabMenu(NMHDR* pNMHDR, LRESULT* pResult);
	CEdit m_EditReceive;
	void getSerialPort();
	CComboBox m_comboComPort;
	void AllButtonDisable();
	void AllButtonEnable();
	CComboBox m_comboModel;
	CEdit m_EditControl;
	afx_msg void OnEnMaxtextEditReceive();
	afx_msg void OnBnClickedButtonReceiveDataClear();
	CString m_strMACETH0;
	CString m_strMACETH1;
	afx_msg void OnBnClickedButtonViewMac();
	afx_msg void OnBnClickedButtonEth0Mac();
	afx_msg void OnBnClickedButtonEth1Mac();
	void Wait(DWORD dwMillisecond);
	int SendHEXData(CString strSend);
	int WaitSting(CString CompStr, int n_timeout);
	int SendAsciiData(CString strSend);
	int Discrimination(CString strDist);
	CString char2CString(char* inp);
	BYTE byCode2AsciiValue(char cData);
	afx_msg void OnBnClickedButtonStart();
	CString m_strSerialNum;
	afx_msg void OnBnClickedButtonSerialNumber();
	CListCtrl m_listExcelCtrl;
	afx_msg void OnCbnSelchangeComboModel();
	afx_msg void OnBnClickedButtonSerialInc();
	afx_msg void OnBnClickedButtonExcelSave();
};
