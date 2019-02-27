#pragma once


// CDebugDialog 대화 상자입니다.

class CDebugDialog : public CDialog
{
	DECLARE_DYNAMIC(CDebugDialog)

public:
	CDebugDialog(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDebugDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEBUGDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	void Update();
};
