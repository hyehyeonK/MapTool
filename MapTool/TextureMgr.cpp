#include "stdafx.h"
#include "TextureMgr.h"

IMPLEMENT_SINGLETON(CTextureMgr)

CTextureMgr::CTextureMgr()
{
}


CTextureMgr::~CTextureMgr()
{
	Release();
}

HRESULT CTextureMgr::InsertTexture(const wstring & _wstrPath, const wstring & _wstrObjKey, TEXTYPE _eTexType, const wstring & _wstrStateKey, const int & _iCount)
{
	auto iter = m_MapTexture.find(_wstrObjKey);

	if (iter == m_MapTexture.end())
	{
		CTexture*		pTexture = nullptr;

		switch (_eTexType)
		{
		case TEX_SINGLE:
			pTexture = new CSingleTexture;
			break;

		case TEX_MULTI:
			pTexture = new CMultiTexture;
			break;
		}

		if (FAILED(pTexture->InsertTexture(_wstrPath, _wstrStateKey, _iCount)))
		{
			AfxMessageBox(_wstrObjKey.c_str());
			return E_FAIL;
		}

		m_MapTexture.emplace(_wstrObjKey, pTexture);
	}
	return S_OK;
}

void CTextureMgr::Release(void)
{
	for_each(m_MapTexture.begin(), m_MapTexture.end(), DeleteMap());
	m_MapTexture.clear();
}

const TEXINFO * CTextureMgr::GetTexture(const wstring & _wstrObjKey, const wstring & _wstrStateKey, const int & _iCount)
{
	auto iter = m_MapTexture.find(_wstrObjKey);

	if (iter == m_MapTexture.end())
		return nullptr;
	return iter->second->GetTexture(_wstrStateKey, _iCount);
}

