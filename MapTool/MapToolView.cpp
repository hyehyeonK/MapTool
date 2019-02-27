
// MapToolView.cpp : CMapToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CMapToolView 생성/소멸

CMapToolView::CMapToolView()
	:m_pGraphicDev(g_MGR_GRAPHIC),
	m_pTextureMgr(g_MGR_TEXTURE)
{
	// TODO: 여기에 생성 코드를 추가합니다.
}

CMapToolView::~CMapToolView()
{
}

BOOL CMapToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMapToolView 그리기

void CMapToolView::OnDraw(CDC* /*pDC*/)
{
	CMapToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	
	m_pGraphicDev->Render_Begin();

	g_MGR_VALUE->BackGroundRender();
	g_MGR_OBJ->Render();

	m_pGraphicDev->Render_End();

}


// CMapToolView 인쇄

BOOL CMapToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMapToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMapToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMapToolView 진단

#ifdef _DEBUG
void CMapToolView::AssertValid() const
{
	CView::AssertValid();
}

void CMapToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMapToolDoc* CMapToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapToolDoc)));
	return (CMapToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMapToolView 메시지 처리기


void CMapToolView::OnInitialUpdate()
{
	g_hWnd = m_hWnd;

	SetScrollSizes(MM_TEXT, CSize((TILECX * TILEX), TILECY * TILEY));

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
		int(WINCX + fRowFrm),
		int(WINCY + fColFrm),
		SWP_NOZORDER);

	if (FAILED(m_pGraphicDev->Initialize()))
	{
		AfxMessageBox(L"디바이스 초기화 실패");
		return;
	}

	if (FAILED(m_pTextureMgr->InsertTexture(L"../Texture/Tile/Tile%d.png", L"TILE", TEX_MULTI, L"Tile", TILE_COUNT)))
	{
		AfxMessageBox(L"타일 텍스쳐 생성 실패");
		return;
	}

	if (FAILED(m_pTextureMgr->InsertTexture(L"../Texture/Object/Obj (%d).png", L"OBJECT", TEX_MULTI, L"Object", 24)))
	{
		AfxMessageBox(L"오브젝트 텍스처 생성 실패");
		return;
	}


	SetTimer(1, 20, NULL);

	CView::OnInitialUpdate();
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}


void CMapToolView::OnDestroy()
{
	CView::OnDestroy();

	m_pTextureMgr->DestroyInstance();
	m_pGraphicDev->DestroyInstance();
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CMapToolView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	g_MGR_VALUE->Progress();
	//Invalidate(FALSE);

	CScrollView::OnTimer(nIDEvent);
}


void CMapToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
