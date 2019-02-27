#include "stdafx.h"
#include "Background.h"
#include "MapToolView.h"
#include "TileMgr.h"
#include "ObjMgr.h"

CBackground::CBackground()
	:m_pGraphicDev(g_MGR_GRAPHIC),
	m_pMainView(g_MGR_VALUE->pMainView),
	m_vecTile(g_MGR_TILE->GetTiles()),
	m_pValueMgr(g_MGR_VALUE),
	m_byDrawID(TILE_COUNT)
{
	//Test
}


CBackground::~CBackground()
{
}

bool CBackground::Picking(const D3DXVECTOR3 & _vPos, const int & _iIdx)
{
	return false;
}

bool CBackground::DotPicking(const D3DXVECTOR3 & _vPos, const int & _iIdx)
{
	return false;
}

void CBackground::TileChange(const D3DXVECTOR3 & _vPos, const BYTE & _byDrawID)
{
	POINT vIdx = GetTileIdx(_vPos);
	
	if (-1 == vIdx.x)
		return;

	++m_vecTile[vIdx.x][vIdx.y]->byDrawID;

	if (m_vecTile[vIdx.x][vIdx.y]->byDrawID > TILE_COUNT)
		m_vecTile[vIdx.x][vIdx.y]->byDrawID = 0;
	m_vecTile[vIdx.x][vIdx.y]->byOption = 1; //충돌 여부
}

void CBackground::HighLightIndex(const D3DXVECTOR3 & _vPos)
{
	POINT vIdx = GetTileIdx(_vPos);

	if (-1 == vIdx.x)
	{
		m_ptCurrIdx = { -1,-1 };
	}
	else
	{
		m_ptCurrIdx = vIdx;
	}
}

void CBackground::TIleChange()
{
	if (m_ptCurrIdx.x != -1 && (GetAsyncKeyState(VK_LBUTTON) & 0x8000))
	{
		g_MGR_TILE->GetTiles()[m_ptCurrIdx.y][m_ptCurrIdx.x]->byDrawID = m_byDrawID;
	}
}

void CBackground::AddObject()
{
	if (m_ptCurrIdx.x != -1 && (GetAsyncKeyState(VK_LBUTTON) & 0x8000))
	{
		if (m_byDrawID == 119)
			return;

		INFO* pNewObj = new INFO;
		pNewObj->vPos = g_MGR_TILE->GetTiles()[m_ptCurrIdx.y][m_ptCurrIdx.x]->vPos;
		pNewObj->byDrawID = m_byDrawID;
		g_MGR_OBJ->GetObjects(g_MGR_VALUE->currObj).push_back(pNewObj);
	}
}
