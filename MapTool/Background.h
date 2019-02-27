#pragma once
#include "Obj.h"

class CGraphicDev;
class CMapToolView;
class CValueMgr;
class CBackground : public CObj
{
public:
	CBackground();
	virtual ~CBackground();

protected:
	virtual POINT GetTileIdx(const D3DXVECTOR3& _vPos) PURE;
	bool Picking(const D3DXVECTOR3& _vPos, const int& _iIdx);
	bool DotPicking(const D3DXVECTOR3& _vPos, const int& _iIdx);

public:
	void TileChange(const D3DXVECTOR3& _vPos, const BYTE& _byDrawID = 1);
	void HighLightIndex(const D3DXVECTOR3& _vPos);
	virtual void LineRender() PURE;

public:
	BYTE m_byDrawID;

protected:
	vector<vector<TILE*>>& m_vecTile;

	CGraphicDev*			m_pGraphicDev = nullptr;
	CMapToolView*		m_pMainView = nullptr;
	CValueMgr*			m_pValueMgr = nullptr;

	POINT m_ptCurrIdx = { -1,-1 };

public:
	float m_fMaxWidth = 0.f;
	float m_fMaxHeight = 0.f;

public:
	void TIleChange();
	void AddObject();
};

