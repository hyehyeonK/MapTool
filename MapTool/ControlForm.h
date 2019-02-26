#pragma once
#include "DebugDialog.h"
#include "afxwin.h"


// CControlForm �� ���Դϴ�.

class CControlForm : public CFormView
{
	DECLARE_DYNCREATE(CControlForm)

protected:
	CControlForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CControlForm();

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
	bool m_bStart = true;
	int m_iColum;
	int m_iRow;
	int m_iTileW;
	int m_iTileH;

public:
	CButton m_pRadioView[2];
	CDebugDialog m_DebugDialog;

public:


	
public:
	afx_msg void OnClickShowDebug();
	afx_msg void OnClickApplySetting();

};


