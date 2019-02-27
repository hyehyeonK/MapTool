#pragma once
#include "Background.h"
class CTopViewBack : public CBackground
{
public:
	CTopViewBack();
	~CTopViewBack();

	// CBackground��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Progress() override;
	virtual void Render() override;
	virtual void Release() override;

	// CBackground��(��) ���� ��ӵ�
	virtual POINT GetTileIdx(const D3DXVECTOR3 & _vPos) override;
	virtual void LineRender() override;
};

