#include "stdafx.h"
#include "ValueMgr.h"


IMPLEMENT_SINGLETON(CValueMgr)

CValueMgr::CValueMgr()
	: m_pBackground()
{
}


CValueMgr::~CValueMgr()
{
	Release();
}

void CValueMgr::Initialize()
{
	m_pBackground[QUARTER] = new CQuarterViewBack;
	m_pBackground[TOPVIEW] = new CTopViewBack;
	m_pBackground[QUARTER]->Initialize();
	m_pBackground[TOPVIEW]->Initialize();
	D3DXMatrixIdentity(&m_WorldMat);
	m_WorldScale = D3DXVECTOR3(1.f, 1.f, 0.f);
	m_TileScale = D3DXVECTOR3(1.f, 1.f, 0.f);

	m_Mouse = CPoint(0, 0);
	m_bLineDraw = true;
}

void CValueMgr::Progress()
{
	D3DXMatrixScaling(&m_ScaleMat, m_WorldScale.x, m_WorldScale.y, m_WorldScale.z);
	m_WorldMat = m_ScaleMat;
	if (pMainView) pMainView->Invalidate(FALSE);
	if (pDebugView) pDebugView->Update();
}

void CValueMgr::Release()
{
	Safe_Delete(m_pBackground[QUARTER]);
	Safe_Delete(m_pBackground[TOPVIEW]);
}

void CValueMgr::BackGroundRender()
{
	if (m_bLineDraw)
	{
		m_pBackground[eViewPoint]->LineRender();
	}
	else
	{
		m_pBackground[eViewPoint]->Render();
	}
}

CBackground* CValueMgr::GetBackGround()
{
	return m_pBackground[eViewPoint];
}
