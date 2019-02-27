
// MapToolView.cpp : CMapToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "MapTool.h"
#endif

#include "MapToolDoc.h"
#include "MapToolView.h"
#include "MainFrm.h"

#include "ObjMgr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND g_hWnd;

// CMapToolView

IMPLEMENT_DYNCREATE(CMapToolView, CScrollView)

BEGIN_MESSAGE_MAP(CMapToolView, CScrollView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CMapToolView ����/�Ҹ�

CMapToolView::CMapToolView()
	:m_pGraphicDev(g_MGR_GRAPHIC),
	m_pTextureMgr(g_MGR_TEXTURE)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
}

CMapToolView::~CMapToolView()
{
}

BOOL CMapToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMapToolView �׸���

void CMapToolView::OnDraw(CDC* /*pDC*/)
{
	CMapToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.

	
	m_pGraphicDev->Render_Begin();

	g_MGR_VALUE->BackGroundRender();
	g_MGR_OBJ->Render();

	m_pGraphicDev->Render_End();

}


// CMapToolView �μ�

BOOL CMapToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMapToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMapToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CMapToolView ����

#ifdef _DEBUG
void CMapToolView::AssertValid() const
{
	CView::AssertValid();
}

void CMapToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMapToolDoc* CMapToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapToolDoc)));
	return (CMapToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMapToolView �޽��� ó����


void CMapToolView::OnInitialUpdate()
{
	g_hWnd = m_hWnd;

	SetScrollSizes(MM_TEXT, CSize((TILECX * TILEX), TILECY * TILEY));

	CMainFrame*		pMainFrm = ((CMainFrame*)AfxGetMainWnd());

	RECT		rcWindow;
	pMainFrm->GetWindowRect(&rcWindow);	 // ������ â �������� ����� ������ �Լ�

	SetRect(&rcWindow,	// ������ ũ���� ���ο� ���� ����� ���ο� ��Ʈ�� right, bottom�� ����
		0,
		0,
		rcWindow.right - rcWindow.left,
		rcWindow.bottom - rcWindow.top);


	RECT	rcMainView;
	GetClientRect(&rcMainView);	// ������ �� â�� ũ�⸦ ������ �Լ�

	float	fRowFrm = float(rcWindow.right - rcMainView.right);
	float	fColFrm = float(rcWindow.bottom - rcMainView.bottom);

	// �� â�� ��ǥ���� 0,0 �������� ����� �� �ְ� â�� ��ġ�� �������ϴ� �Լ�
	pMainFrm->SetWindowPos(NULL,
		0,
		0,
		int(WINCX + fRowFrm),
		int(WINCY + fColFrm),
		SWP_NOZORDER);

	if (FAILED(m_pGraphicDev->Initialize()))
	{
		AfxMessageBox(L"����̽� �ʱ�ȭ ����");
		return;
	}

	if (FAILED(m_pTextureMgr->InsertTexture(L"../Texture/Tile/Tile%d.png", L"TILE", TEX_MULTI, L"Tile", TILE_COUNT)))
	{
		AfxMessageBox(L"Ÿ�� �ؽ��� ���� ����");
		return;
	}

	if (FAILED(m_pTextureMgr->InsertTexture(L"../Texture/Object/Obj (%d).png", L"OBJECT", TEX_MULTI, L"Object", 24)))
	{
		AfxMessageBox(L"������Ʈ �ؽ�ó ���� ����");
		return;
	}


	SetTimer(1, 20, NULL);

	CView::OnInitialUpdate();
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}


void CMapToolView::OnDestroy()
{
	CView::OnDestroy();

	m_pTextureMgr->DestroyInstance();
	m_pGraphicDev->DestroyInstance();
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


void CMapToolView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	g_MGR_VALUE->Progress();
	//Invalidate(FALSE);

	CScrollView::OnTimer(nIDEvent);
}


void CMapToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	g_MGR_VALUE->m_Mouse = point;
	D3DXVECTOR3	vMouse = D3DXVECTOR3(float(point.x) + GetScrollPos(0) * g_MGR_VALUE->m_WorldScale.x, float(point.y) + GetScrollPos(1) * g_MGR_VALUE->m_WorldScale.y, 0.f);


	switch (g_MGR_VALUE->currTool)
	{
	case CValueMgr::TOOL_TILE:
		g_MGR_VALUE->GetBackGround()->HighLightIndex(vMouse);
		g_MGR_VALUE->GetBackGround()->TIleChange();
		break;
	case CValueMgr::TOOL_OBJ:
		if (g_MGR_VALUE->m_bObjPosFromTile)
		{
			g_MGR_VALUE->GetBackGround()->HighLightIndex(vMouse);
		}
		/*else
		{
			g_MGR_VALUE->GetBackGround()->HighLightIndex({ -1.f,-1.f,-1.f });
		}*/
			
		break;
	case CValueMgr::TOOL_COLLI:

		break;
	}



	CScrollView::OnMouseMove(nFlags, point);
}


void CMapToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	D3DXVECTOR3 vMouse = { float(point.x) + GetScrollPos(0), float(point.y) + GetScrollPos(1), 0.f };

	switch (g_MGR_VALUE->currTool)
	{
	case CValueMgr::TOOL_TILE:
			g_MGR_VALUE->GetBackGround()->TIleChange();
		break;
	case CValueMgr::TOOL_OBJ:
		g_MGR_VALUE->GetBackGround()->AddObject(vMouse);
		break;
	case CValueMgr::TOOL_COLLI:
		break;
	}

	CScrollView::OnLButtonDown(nFlags, point);
}
