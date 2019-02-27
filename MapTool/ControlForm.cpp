// ControlForm.cpp : 구현 파일입니다.
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


// CControlForm 진단입니다.

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


// CControlForm 메시지 처리기입니다.


void CControlForm::OnClickShowDebug()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_DebugDialog.GetSafeHwnd() == NULL)
	{
		m_DebugDialog.Create(IDD_DEBUGDIALOG);
	}
	m_DebugDialog.ShowWindow(SW_SHOW);

}


void CControlForm::OnClickApplySetting()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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

	//화면갱신
	g_MGR_VALUE->pMainView->m_pBackground[g_MGR_VALUE->eViewPoint]->Initialize();
	g_MGR_VALUE->pMainView->SetScrollSizes(MM_TEXT, CSize((m_iTileW * m_iRow), m_iTileH * m_iColum));
	g_MGR_VALUE->pMainView->Invalidate(FALSE);
}


void CControlForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_pRadioView[0].SetCheck(TRUE);
}
