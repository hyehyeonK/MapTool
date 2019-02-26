#pragma once
#include "Texture.h"
class CMultiTexture : public CTexture
{
public:
	CMultiTexture();
	~CMultiTexture();

public:
	virtual HRESULT InsertTexture(const wstring & _wstrPath, const wstring & _wstrStateKey = L"", const int & _iCount = 0) override;
	virtual void Release() override;
	virtual const TEXINFO * GetTexture(const wstring & _wstrStateKey = L"", const int & _iCount = 0) override;

private:
	map<wstring, vector<TEXINFO*>> m_mapMultiTexture;
};

