// AnalogBox.cpp: 구현 파일
//

#include "pch.h"
#include "IOTManufacture.h"
#include "AnalogBox.h"
#include "afxdialogex.h"


// CAnalogBox 대화 상자

IMPLEMENT_DYNAMIC(CAnalogBox, CDialogEx)

CAnalogBox::CAnalogBox(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ANALOG, pParent)
{

}

CAnalogBox::~CAnalogBox()
{
}

void CAnalogBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAnalogBox, CDialogEx)
END_MESSAGE_MAP()


// CAnalogBox 메시지 처리기
