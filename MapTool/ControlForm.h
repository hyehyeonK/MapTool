#pragma once
#include "DebugDialog.h"


// CControlForm �� ���Դϴ�.

class CControlForm : public CFormView
{
	DECLARE_DYNCREATE(CControlForm)

protected:
	CControlForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CControlForm();

private:
	CSplitterWnd		m_MainSplitter;
	CSplitterWnd		m_SecondSplitter;

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONTROLFORM };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickShowDebug();

public:
	CDebugDialog m_DebugDialog;
};


