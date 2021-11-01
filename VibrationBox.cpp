// VibrationBox.cpp: 구현 파일
//

#include "pch.h"
#include "IOTManufacture.h"
#include "VibrationBox.h"
#include "afxdialogex.h"


// CVibrationBox 대화 상자

IMPLEMENT_DYNAMIC(CVibrationBox, CDialogEx)

CVibrationBox::CVibrationBox(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_VIB, pParent)
{

}

CVibrationBox::~CVibrationBox()
{
}

void CVibrationBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVibrationBox, CDialogEx)
END_MESSAGE_MAP()


// CVibrationBox 메시지 처리기
