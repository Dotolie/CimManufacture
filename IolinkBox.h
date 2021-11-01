#pragma once


// CIolinkBox 대화 상자

class CIolinkBox : public CDialogEx
{
	DECLARE_DYNAMIC(CIolinkBox)

public:
	CIolinkBox(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CIolinkBox();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IOLINK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonDockerStart();

	CWinThread* m_pThread;
	bool m_isWorkingThread;
};
