#include "stdafx.h"
#include "SingleTexture.h"

#include "GraphicDev.h"

CSingleTexture::CSingleTexture()
{
}


CSingleTexture::~CSingleTexture()
{
	Release();
}

HRESULT CSingleTexture::InsertTexture(const wstring & _wstrPath, 
														const wstring & _wstrStateKey, 
														const int & _iCount)
{
	m_pTexInfo = new TEXINFO;
	ZeroMemory(m_pTexInfo, sizeof(TEXINFO));

	if (FAILED(D3DXGetImageInfoFromFile(_wstrPath.c_str(), &m_pTexInfo->tImgInfo)))
	{
		wstring Msg = _wstrPath + L" : 로드 실패";
		AfxMessageBox(Msg.c_str() );
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFileEx(g_MGR_GRAPHIC->GetDevice(),
																_wstrPath.c_str(),
																m_pTexInfo->tImgInfo.Width,
																m_pTexInfo->tImgInfo.Height,
																m_pTexInfo->tImgInfo.MipLevels,
																0,
																m_pTexInfo->tImgInfo.Format,
																D3DPOOL_MANAGED,
																D3DX_DEFAULT,
																D3DX_DEFAULT,
																NULL,
																&m_pTexInfo->tImgInfo,
																NULL,
																&m_pTexInfo->pTexture )))
	{
		AfxMessageBox(L"Single Texture Image Load 실패");
		return E_FAIL;
	}
	return S_OK;
}

void CSingleTexture::Release()
{
	m_pTexInfo->pTexture->Release();
	Safe_Delete(m_pTexInfo);
}

const TEXINFO * CSingleTexture::GetTexture(const wstring & _wstrStateKey, const int & _iCount)
{
	return m_pTexInfo;
}
