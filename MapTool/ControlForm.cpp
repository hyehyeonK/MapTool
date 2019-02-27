// ControlForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MapTool.h"
#include "ControlForm.h"
#include "TabTile.h"
#include "TabCollider.h"
#include "TabObject.h"
#include "MainFrm.h"

// CControlForm

IMPLEMENT_DYNCREATE(CControlForm, CFormView)

CControlForm::CControlForm()
	: CFormView(IDD_CONTROLFORM)
	, m_iColum(g_MGR_VALUE->iColum)
	, m_iRow(g_MGR_VALUE->iRow)
	, m_iTileW(g_MGR_VALUE->iTileW)
	, m_iTileH(g_MGR_VALUE->iTileH)
	, m_WorldScaleX(1.f)
	, m_WorldScaleY(1.f)
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
	DDX_Control(pDX, IDC_TAB1, m_Tab);
	DDX_Text(pDX, IDC_EDIT1, m_WorldScaleX);
	DDX_Text(pDX, IDC_EDIT2, m_WorldScaleY);
}

BEGIN_MESSAGE_MAP(CControlForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CControlForm::OnClickShowDebug)
	ON_BN_CLICKED(IDC_APLYSET, &CControlForm::OnClickApplySetting)
	ON_BN_CLICKED(IDC_NEXT, &CControlForm::OnClickNext)
//	ON_WM_HSCROLL()
ON_WM_SIZE()
ON_BN_CLICKED(IDC_NEXT2, &CControlForm::OnClickBack)
ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CControlForm::OnSelectTab)
ON_BN_CLICKED(IDC_BUTTON2, &CControlForm::OnScaleApply)
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
	g_MGR_VALUE->GetBackGround()->Initialize();
	g_MGR_VALUE->pMainView->SetScrollSizes(MM_TEXT, CSize(int(WINCX + (g_MGR_VALUE->GetBackGround()->m_fMaxWidth - WINCX) * g_MGR_VALUE->m_WorldScale.x), int(WINCY + (g_MGR_VALUE->GetBackGround()->m_fMaxHeight - WINCY) * g_MGR_VALUE->m_WorldScale.y)));
	//g_MGR_VALUE->pMainView->Invalidate(FALSE);
}


void CControlForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_pRadioView[0].SetCheck(TRUE);


	//
	CMainFrame*		pMainFrm = ((CMainFrame*)AfxGetMainWnd());
	RECT		rcWindow;
	pMainFrm->GetWindowRect(&rcWindow);	 // 윈도우 창 프레임의 사이즈를 얻어오는 함수

	SetRect(&rcWindow,	// 프레임 크기의 가로와 세로 사이즈를 새로운 렉트에 right, bottom에 저장
		0,
		0,
		rcWindow.right - rcWindow.left,
		rcWindow.bottom - rcWindow.top);


	RECT	rcMainView;
	GetClientRect(&rcMainView);	// 순수한 뷰 창의 크기를 얻어오는 함수

	float	fRowFrm = float(rcWindow.right - rcMainView.right);
	float	fColFrm = float(rcWindow.bottom - rcMainView.bottom);

	// 뷰 창의 좌표들을 0,0 기준으로 출력할 수 있게 창의 위치를 재조정하는 함수
	pMainFrm->SetWindowPos(NULL,
		0,
		0,
		int(300 + fRowFrm),
		int(WINCY + fColFrm),
		SWP_NOZORDER);

	//
	//Tab Insert
	m_Tab.InsertItem(0, _T("Tile"));
	m_Tab.InsertItem(1, _T("Object"));
	m_Tab.InsertItem(2, _T("Collider"));

	CRect rect;
	m_Tab.GetWindowRect(&rect);

	m_pTabTIle = new CTabTile;
	m_pTabTIle->Create(IDD_TAB_TILE, &m_Tab);
	m_pTabTIle->MoveWindow(0, 25, rect.Width(), rect.Height());
	m_pTabTIle->ShowWindow(SW_SHOW);

	m_pTabObject = new CTabObject;
	m_pTabObject->Create(IDD_TAB_OBJ, &m_Tab);
	m_pTabObject->MoveWindow(0, 25, rect.Width(), rect.Height());
	m_pTabObject->ShowWindow(SW_HIDE);

	m_pCollider = new CTabCollider;
	m_pCollider->Create(IDD_TAB_COLLI, &m_Tab);
	m_pCollider->MoveWindow(0, 25, rect.Width(), rect.Height());
	m_pCollider->ShowWindow(SW_HIDE);


	//Scroll Bar 없애기
	SetScrollSizes(MM_TEXT, CSize(0,0));
}


void CControlForm::OnClickNext()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	ScrollToPosition({300,0});
	Invalidate(FALSE);
}



void CControlForm::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CSize sizeTotal(WINCX, WINCY);
	CSize sizePage(cx - 50, cy - 50);
	CSize sizeLine(50, 50);
	SetScrollSizes(MM_TEXT, sizeTotal, sizePage, sizeLine);
}


void CControlForm::OnClickBack()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ScrollToPosition({ 0,0 });
	Invalidate(FALSE);
}


void CControlForm::OnSelectTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int sel = m_Tab.GetCurSel();

	switch (sel)
	{
	case 0:
		m_pTabTIle->ShowWindow(SW_SHOW);
		m_pTabObject->ShowWindow(SW_HIDE);
		m_pCollider->ShowWindow(SW_HIDE);
		g_MGR_VALUE->currTool = CValueMgr::TOOL_TILE;
		break;

	case 1:
		m_pTabTIle->ShowWindow(SW_HIDE);
		m_pTabObject->ShowWindow(SW_SHOW);
		m_pCollider->ShowWindow(SW_HIDE);
		g_MGR_VALUE->currTool = CValueMgr::TOOL_OBJ;
		break;

	case 2:
		m_pTabTIle->ShowWindow(SW_HIDE);
		m_pTabObject->ShowWindow(SW_HIDE);
		m_pCollider->ShowWindow(SW_SHOW);
		g_MGR_VALUE->currTool = CValueMgr::TOOL_COLLI;
		break;
	}
	Invalidate(FALSE);
	*pResult = 0;
}


void CControlForm::OnScaleApply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	g_MGR_VALUE->m_WorldScale.x = m_WorldScaleX;
	g_MGR_VALUE->m_WorldScale.y = m_WorldScaleY;

	UpdateData(FALSE);

	g_MGR_VALUE->pMainView->SetScrollSizes(MM_TEXT, CSize(int(WINCX + (g_MGR_VALUE->GetBackGround()->m_fMaxWidth - WINCX) * g_MGR_VALUE->m_WorldScale.x), int(WINCY + (g_MGR_VALUE->GetBackGround()->m_fMaxHeight - WINCY) * g_MGR_VALUE->m_WorldScale.y)));
}
