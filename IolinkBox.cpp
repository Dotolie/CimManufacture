// IolinkBox.cpp: 구현 파일
//

#include "pch.h"
#include "IOTManufacture.h"
#include "IolinkBox.h"
#include "afxdialogex.h"
#include "IOTManufactureDlg.h"

// CIolinkBox 대화 상자
UINT ThreadForIolink(LPVOID param);

IMPLEMENT_DYNAMIC(CIolinkBox, CDialogEx)

CIolinkBox::CIolinkBox(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_IOLINK, pParent)
{

}

CIolinkBox::~CIolinkBox()
{
}

void CIolinkBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CIolinkBox, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_DOCKER_START, &CIolinkBox::OnBnClickedButtonDockerStart)
END_MESSAGE_MAP()


// CIolinkBox 메시지 처리기


void CIolinkBox::OnBnClickedButtonDockerStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString StrTestCode;
	CIOTManufactureDlg* pDlg = (CIOTManufactureDlg*)AfxGetApp()->GetMainWnd();

	StrTestCode = "\ni\n";
	pDlg->SendAsciiData(StrTestCode);

	pDlg->Wait(100);

	pDlg->AllButtonEnable();

	m_isWorkingThread = true;

	//m_pThread = AfxBeginThread(ThreadForIolink, this);
}

UINT ThreadForIolink(LPVOID param)
{
	CIolinkBox* pMain = (CIolinkBox*)param;
	CIOTManufactureDlg* pDlg = (CIOTManufactureDlg*)AfxGetApp()->GetMainWnd();

	BOOL chk = pMain->IsWindowVisible();
	if (chk)
	{
		pMain->ShowWindow(SW_HIDE);
	}
	else
	{
		pMain->ShowWindow(SW_SHOW);
	}

	//pMain->m_isWorkingThread = false;
	pDlg->m_ResultFlag = TEST_IOLINK;

	while (pMain->m_isWorkingThread)
	{
		Sleep(30);

		//Do something...
		if (pDlg->GetterResult.GetLength() == 0) {

			//rst = pDlg->GetterResult.Find(_T("{"));
			
		}
		else {

		}
	}

	return 0;
}