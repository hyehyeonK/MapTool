// ControlForm.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MapTool.h"
#include "ControlForm.h"


// CControlForm

IMPLEMENT_DYNCREATE(CControlForm, CFormView)

CControlForm::CControlForm()
	: CFormView(IDD_CONTROLFORM)
	, m_iColum(0)
	, m_iRow(0)
	, m_iTileW(TILECX)
	, m_iTileH(TILECY)
{

}

CControlForm::~CControlForm()
{
}

void CControlForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO_TV, m_pRadioView[0]);
	DDX_Control(pDX, IDC_RADIO_QV, m_pRadioView[1]);
	if (true == m_bStart)
	{
		m_pRadioView[0].SetCheck(TRUE);
		m_bStart = false;
	}
	DDX_Text(pDX, IDC_EDIT_COL, m_iColum);
	DDX_Text(pDX, IDC_EDIT_ROW, m_iRow);
	DDX_Text(pDX, IDC_EDIT_TILECX, m_iTileW);
	DDX_Text(pDX, IDC_EDIT_TILECY, m_iTileH);
}

BEGIN_MESSAGE_MAP(CControlForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CControlForm::OnClickShowDebug)
	ON_BN_CLICKED(IDC_APLYSET, &CControlForm::OnClickApplySetting)
END_MESSAGE_MAP()


// CControlForm �����Դϴ�.

#ifdef _DEBUG
void CControlForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CControlForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CControlForm �޽��� ó�����Դϴ�.


void CControlForm::OnClickShowDebug()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (m_DebugDialog.GetSafeHwnd() == NULL)
	{
		m_DebugDialog.Create(IDD_DEBUGDIALOG);
	}
	m_DebugDialog.ShowWindow(SW_SHOW);

}


void CControlForm::OnClickApplySetting()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (m_pRadioView[0].GetCheck())
	{

	}
	else
	{

	}

}
