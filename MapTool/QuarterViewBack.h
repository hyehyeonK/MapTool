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
};

