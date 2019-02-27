#pragma once
#include "DebugDialog.h"
#include "afxwin.h"
#include "afxcmn.h"


// CControlForm 폼 뷰입니다.

class CTabTile;
class CTabCollider;
class CTabObject;

class CControlForm : public CFormView
{
	DECLARE_DYNCREATE(CControlForm)

protected:
	CControlForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	int m_iColum;
	int m_iRow;
	int m_iTileW;
	int m_iTileH;

public:
	CTabTile*	m_pTabTIle;
	CTabObject*	m_pTabObject;
	CTabCollider*	m_pCollider;
public:
	CButton m_pRadioView[2];
	CDebugDialog m_DebugDialog;
	CTabCtrl m_Tab;
public:


	
public:
	afx_msg void OnClickShowDebug();
	afx_msg void OnClickApplySetting();

	virtual void OnInitialUpdate();
	afx_msg void OnClickNext();

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClickBack();

	afx_msg void OnSelectTab(NMHDR *pNMHDR, LRESULT *pResult);
};


