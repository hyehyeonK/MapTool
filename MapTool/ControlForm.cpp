// ControlForm.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MapTool.h"
#include "ControlForm.h"


// CControlForm

IMPLEMENT_DYNCREATE(CControlForm, CFormView)

CControlForm::CControlForm()
	: CFormView(IDD_CONTROLFORM)
	, m_iColum(g_MGR_VALUE->iColum)
	, m_iRow(g_MGR_VALUE->iRow)
	, m_iTileW(g_MGR_VALUE->iTileW)
	, m_iTileH(g_MGR_VALUE->iTileH)
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
	UpdateData(TRUE);

	if (m_pRadioView[0].GetCheck())
	{
		g_MGR_VALUE->eViewPoint = CValueMgr::TOPVIEW;
	}
	else
	{
		g_MGR_VALUE->eViewPoint = CValueMgr::QUARTER;
	}

	g_MGR_VALUE->iColum = m_iColum;
	g_MGR_VALUE->iRow = m_iRow;
	g_MGR_VALUE->iTileW = m_iTileW;
	g_MGR_VALUE->iTileH = m_iTileH;

	UpdateData(FALSE);

	//ȭ�鰻��
	g_MGR_VALUE->pMainView->m_pBackground[g_MGR_VALUE->eViewPoint]->Initialize();
	g_MGR_VALUE->pMainView->SetScrollSizes(MM_TEXT, CSize((m_iTileW * m_iRow), m_iTileH * m_iColum));
	g_MGR_VALUE->pMainView->Invalidate(FALSE);
}


void CControlForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_pRadioView[0].SetCheck(TRUE);
}
