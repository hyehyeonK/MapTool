#pragma once
#include "Background.h"
class CQuarterViewBack : public CBackground
{
public:
	CQuarterViewBack();
	virtual~CQuarterViewBack();

	// CBackground��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;

	// CBackground��(��) ���� ��ӵ�
	virtual int Progress() override;
	virtual void Render() override;
	virtual void Release() override;

	// CBackground��(��) ���� ��ӵ�
	virtual POINT GetTileIdx(const D3DXVECTOR3 & _vPos) override;

	// CBackground��(��) ���� ��ӵ�
	virtual void LineRender() override;
};

