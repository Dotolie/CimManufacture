#pragma once


// CAutoTest 대화 상자

class CAutoTest : public CDialogEx
{
	DECLARE_DYNAMIC(CAutoTest)

public:
	CAutoTest(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CAutoTest();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_AUTO_TEST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
