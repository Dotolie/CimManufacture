// DigitalBox.cpp: 구현 파일
//

#include "pch.h"
#include "IOTManufacture.h"
#include "DigitalBox.h"
#include "afxdialogex.h"


// CDigitalBox 대화 상자

IMPLEMENT_DYNAMIC(CDigitalBox, CDialogEx)

CDigitalBox::CDigitalBox(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DIGITAL, pParent)
{

}

CDigitalBox::~CDigitalBox()
{
}

void CDigitalBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDigitalBox, CDialogEx)
END_MESSAGE_MAP()


// CDigitalBox 메시지 처리기
