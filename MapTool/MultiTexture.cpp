#include "stdafx.h"
#include "MultiTexture.h"
#include "GraphicDev.h"

CMultiTexture::CMultiTexture()
{
}


CMultiTexture::~CMultiTexture()
{
	Release();
}

HRESULT CMultiTexture::InsertTexture(const wstring & _wstrPath, 
													const wstring & _wstrStateKey, 
													const int & _iCount)
{
	TCHAR	szPath[MAX_PATH] = L"";

	vector<TEXINFO*> vecTexture;

	for (int i = 0; i < _iCount; ++i)
	{
		wsprintf(szPath, _wstrPath.c_str(), i);

		TEXINFO*		pTexInfo = new TEXINFO;
		ZeroMemory(pTexInfo, sizeof(TEXINFO));

		if (FAILED(D3DXGetImageInfoFromFile(szPath, &pTexInfo->tImgInfo)))
		{
			AfxMessageBox(szPath);
			return E_FAIL;
		}

		if (FAILED(D3DXCreateTextureFromFileEx(g_MGR_GRAPHIC->GetDevice(),
			szPath,
			pTexInfo->tImgInfo.Width,
			pTexInfo->tImgInfo.Height,
			pTexInfo->tImgInfo.MipLevels,
			0,
			pTexInfo->tImgInfo.Format,
			D3DPOOL_MANAGED,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			NULL,
			&pTexInfo->tImgInfo,
			NULL,
			&pTexInfo->pTexture)))
		{
			AfxMessageBox(L"Multi Texture Image Load Failed");
			return E_FAIL;
		}
		vecTexture.push_back(pTexInfo);
	}
	m_mapMultiTexture.emplace(_wstrStateKey, vecTexture);
	return S_OK;
}

void CMultiTexture::Release()
{
	for (auto& vecTexture : m_mapMultiTexture)
	{
		for (size_t i = 0; i < vecTexture.second.size(); ++i)
		{
			vecTexture.second[i]->pTexture->Release();
			Safe_Delete(vecTexture.second[i]);
		}
		vecTexture.second.clear();
	}
	m_mapMultiTexture.clear();
}

const TEXINFO * CMultiTexture::GetTexture(const wstring & _wstrStateKey, const int & _iCount)
{
	auto iter = m_mapMultiTexture.find(_wstrStateKey);

	if (iter == m_mapMultiTexture.end())
		return nullptr;
	return iter->second[_iCount];
}
