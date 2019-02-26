#pragma once
#include "SingleTexture.h"
#include "MultiTexture.h"

#define g_MGR_TEXTURE CTextureMgr::GetInstance()

class CTextureMgr
{
	DECLARE_SINGLETON(CTextureMgr)

private:
	CTextureMgr();
	~CTextureMgr();

public:
	HRESULT					InsertTexture(const wstring& _wstrPath,
														const wstring& _wstrObjKey,
														TEXTYPE _eTexType,
														const wstring& _wstrStateKey = L"",
														const int& _iCount = 0);

	void					Release(void);
	const	TEXINFO*		GetTexture(const wstring& _wstrObjKey,
												const wstring& _wstrStateKey = L"",
												const int& _iCount = 0);

private:
	map<wstring, CTexture*>			m_MapTexture;
};

