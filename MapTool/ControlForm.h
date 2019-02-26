#pragma once
#include "DebugDialog.h"
#include "afxwin.h"


// CControlForm 폼 뷰입니다.

class CControlForm : public CFormView
{
	DECLARE_DYNCREATE(CControlForm)

protected:
	CControlForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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


