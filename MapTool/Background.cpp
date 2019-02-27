#include "stdafx.h"
#include "Background.h"
#include "MapToolView.h"
#include "TileMgr.h"

CBackground::CBackground()
	:m_pGraphicDev(g_MGR_GRAPHIC),
	m_pMainView(g_MGR_VALUE->pMainView),
	m_vecTile(g_MGR_TILE->GetTiles()),
	m_pValueMgr(g_MGR_VALUE)
{
	//Test
}


CBackground::~CBackground()
{
}

POINT CBackground::GetTileIdx(const D3DXVECTOR3 & _vPos)
{
	float fSlop = float(TILECY) / TILECX;
	float fY = 0;
	float fX = 0;
	int		m_iTargetIdxY = 0;
	int		m_iTargetIdxX = 0;
	for (int i = 1; i <= TILEY; ++i)
	{
		fY = fSlop * _vPos.x - (HalfMaxHeight - TILECY * i);
		if (fY >  _vPos.y)
		{
			m_iTargetIdxY = i - 1;
			break;
		}
	}
	if (!(0 <= m_iTargetIdxY && signed int(m_vecTile.size()) > m_iTargetIdxY))
		return{ -1,-1 };

	m_iTargetIdxX =int( _vPos.x / (TILECX >> 1) - (TILEX - 1 - m_iTargetIdxY));
	fY = -fSlop * _vPos.x + (HalfMaxHeight + TILECY * m_iTargetIdxX);
	if (fY > _vPos.y)
	{
		--m_iTargetIdxX;
	}

	if (!(0 <= m_iTargetIdxX && m_iTargetIdxX < signed int(m_vecTile[0].size())))
		return{ -1,-1 };

	return{ m_iTargetIdxY,m_iTargetIdxX };
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