#pragma once
#include "../Headers/Include.h"

#define g_MGR_TILE CTileMgr::GetInstance()

class CTileMgr
{
	DECLARE_SINGLETON(CTileMgr)

private:
	CTileMgr();
	~CTileMgr();

public:
	vector<vector<TILE*>>&		GetTiles() { return m_vecTile; }
	void	InitTiles();
	void Release();
public:
	void Notify();

private:
	vector<vector<TILE*>> m_vecTile;

};

