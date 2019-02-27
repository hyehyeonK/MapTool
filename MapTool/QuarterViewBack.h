#pragma once
#include "Background.h"
class CQuarterViewBack : public CBackground
{
public:
	CQuarterViewBack();
	virtual~CQuarterViewBack();

	// CBackground을(를) 통해 상속됨
	virtual HRESULT Initialize() override;

	// CBackground을(를) 통해 상속됨
	virtual int Progress() override;
	virtual void Render() override;
	virtual void Release() override;

	// CBackground을(를) 통해 상속됨
	virtual POINT GetTileIdx(const D3DXVECTOR3 & _vPos) override;

	// CBackground을(를) 통해 상속됨
	virtual void LineRender() override;
};

