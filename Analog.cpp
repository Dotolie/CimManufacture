// Analog.cpp: 구현 파일
//

#include "pch.h"
#include "IOTManufacture.h"
#include "Analog.h"
#include "afxdialogex.h"


// CAnalog 대화 상자

IMPLEMENT_DYNAMIC(CAnalog, CDialogEx)

CAnalog::CAnalog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ANALOG, pParent)
{

}

CAnalog::~CAnalog()
{
}

void CAnalog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAnalog, CDialogEx)
END_MESSAGE_MAP()


// CAnalog 메시지 처리기
