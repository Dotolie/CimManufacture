#pragma once


// CVibrationBox 대화 상자

class CVibrationBox : public CDialogEx
{
	DECLARE_DYNAMIC(CVibrationBox)

public:
	CVibrationBox(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CVibrationBox();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_VIB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
