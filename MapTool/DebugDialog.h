#pragma once
#include "afxwin.h"


// CDebugDialog ��ȭ �����Դϴ�.

class CDebugDialog : public CDialog
{
	DECLARE_DYNAMIC(CDebugDialog)

public:
	CDebugDialog(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDebugDialog();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEBUGDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	void Update();

public: // control
	CButton m_LineCheck;
	afx_msg void OnLineCheckBox();
};
