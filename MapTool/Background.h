#pragma once
#include "Obj.h"

class CGraphicDev;
class CMapToolView;

class CBackground : public CObj
{
public:
	CBackground();
	~CBackground();

public:
	virtual HRESULT Initialize() override;
	virtual int Progress() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	POINT GetTileIdx(const D3DXVECTOR3& _vPos);
	bool Picking(const D3DXVECTOR3& _vPos, const int& _iIdx);
	bool DotPicking(const D3DXVECTOR3& _vPos, const int& _iIdx);

public:
	void TileChange(const D3DXVECTOR3& _vPos, const BYTE& _byDrawID = 1);
	void SetMainView(CMapToolView* _pMainView) { m_pMainView = _pMainView; }
	void HighLightIndex(const D3DXVECTOR3& _vPos);

private:

	vector<vector<TILE*>>& m_vecTile;

	CGraphicDev*			m_pGraphicDev = nullptr;
	CMapToolView*		m_pMainView = nullptr;
	float HalfMaxWidth = 0.f;
	float HalfMaxHeight = 0.f;

	POINT m_ptCurrIdx = {-1,-1};
};

