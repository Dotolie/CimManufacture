#pragma once
#include "AutoTest.h"

// CCommon 대화 상자

class CCommon : public CDialogEx
{
	DECLARE_DYNAMIC(CCommon)

public:
	CCommon(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CCommon();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_COMMON };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonMemTest();
	afx_msg void OnBnClickedButtonEmmcTest();
	afx_msg void OnBnClickedButtonLedTest();
	afx_msg void OnBnClickedButtonEth0Test();
	afx_msg void OnBnClickedButtonEth1Test();
	afx_msg void OnBnClickedButtonWlanTest();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonAutoTest();

	CAutoTest* m_pAautoDlg;
	CWinThread* m_pThread;
	bool m_isWorkingThread;
	afx_msg void OnBnClickedButtonFlashTest();
};
