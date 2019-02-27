#include "stdafx.h"
#include "TileMgr.h"


IMPLEMENT_SINGLETON(CTileMgr)

CTileMgr::CTileMgr()
{
}


CTileMgr::~CTileMgr()
{
	Release();
}

void CTileMgr::InitTiles()
{
	for (auto vecT : m_vecTile)
	{
		for (auto tile : vecT)
		{
			tile->byDrawID = TILE_COUNT;
		}
	}
}

void CTileMgr::Release()
{
	for (auto& vec : m_vecTile)
	{
		for_each(vec.begin(), vec.end(), DeleteOBJ());
		vec.clear();
	}

	m_vecTile.clear();
}
