// AutoTest.cpp: 구현 파일
//

#include "pch.h"
#include "IOTManufacture.h"
#include "AutoTest.h"
#include "afxdialogex.h"
#include "IOTManufactureDlg.h"


// CAutoTest 대화 상자

IMPLEMENT_DYNAMIC(CAutoTest, CDialogEx)

CAutoTest::CAutoTest(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_AUTO_TEST, pParent)
{

}

CAutoTest::~CAutoTest()
{
}

void CAutoTest::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAutoTest, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAutoTest::OnBnClickedOk)
END_MESSAGE_MAP()


// CAutoTest 메시지 처리기


void CAutoTest::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CIOTManufactureDlg* pDlg = (CIOTManufactureDlg*)AfxGetApp()->GetMainWnd();
	DWORD nExitCode = NULL;	
	
	GetExitCodeThread(pDlg->m_CommonDlg.m_pThread, &nExitCode);
	TerminateThread(pDlg->m_CommonDlg.m_pThread, nExitCode);

	pDlg->m_ResultFlag = 0;
	pDlg->GetterResult = _T("");
	pDlg->AllButtonEnable();

	CDialogEx::OnOK();
}
