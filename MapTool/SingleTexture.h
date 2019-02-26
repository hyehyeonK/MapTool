#pragma once
#include "Texture.h"
class CSingleTexture : public CTexture
{
public:
	CSingleTexture();
	~CSingleTexture();

public:
	virtual HRESULT InsertTexture(const wstring & _wstrPath, const wstring & _wstrStateKey = L"", const int & _iCount = 0) override;
	virtual void Release() override;
	virtual const TEXINFO * GetTexture(const wstring & _wstrStateKey = L"", const int & _iCount = 0) override;

private:
	TEXINFO*		m_pTexInfo = nullptr;
};

