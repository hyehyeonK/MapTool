#pragma once
#include "../Headers/Include.h"

class CTexture
{

public:
	virtual HRESULT				InsertTexture(const wstring& _wstrPath, 
															const wstring& _wstrStateKey = L"", 
															const int& _iCount = 0) PURE;
	virtual void						Release() PURE;
	virtual const TEXINFO*		GetTexture(const wstring& _wstrStateKey = L"",
														const int& _iCount = 0) PURE;

public:
	CTexture();
	virtual ~CTexture();
};

