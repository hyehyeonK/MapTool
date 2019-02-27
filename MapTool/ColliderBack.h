#pragma once
#include "Background.h"
class CColliderBack : public CBackground
{
public:
	CColliderBack();
	~CColliderBack();

public:
	virtual HRESULT Initialize() override;
	virtual int Progress() override;
	virtual void Render() override;
	virtual void Release() override;

public:


	// CBackground��(��) ���� ��ӵ�
	virtual POINT GetTileIdx(const D3DXVECTOR3 & _vPos) override;
	virtual void LineRender() override;
};

