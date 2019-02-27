#include "stdafx.h"
#include "ObjMgr.h"
#include "GraphicDev.h"


IMPLEMENT_SINGLETON(CObjMgr)

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::Initialize(void)
{
	for (size_t i = 0; i < CValueMgr::OBJ_END; ++i)
	{
		for (auto obj : m_vecObj[i])
		{
			obj->byDrawID = TILE_COUNT;
		}
	}
}

void CObjMgr::Render(void)
{
	D3DXMATRIX	matTrans;
	TCHAR			szIdx[MIN_STR] = L"";
	const TEXINFO*		pTexTexture;
	//D3DXVECTOR2 vList[5] = {};
	multimap<float, INFO*> mMapSort;

	for (auto& objVec : m_vecObj)
	{
		for (auto& obj : objVec)
		{
			mMapSort.emplace(obj->vPos.y, obj);
		}
	}

	for (auto& obj : mMapSort)
	{
		D3DXMatrixTranslation(&matTrans,
			obj.second->vPos.x - g_MGR_VALUE->pMainView->GetScrollPos(0),
			obj.second->vPos.y - g_MGR_VALUE->pMainView->GetScrollPos(1),
			0.f);
		g_MGR_GRAPHIC->GetSprite()->SetTransform(&matTrans);

		pTexTexture = CTextureMgr::GetInstance()->GetTexture(L"OBJECT", L"Object", obj.second->byDrawID);

		g_MGR_GRAPHIC->GetSprite()->Draw(
			pTexTexture->pTexture,
			NULL, // 보여줄 이미지 크기
			&D3DXVECTOR3(pTexTexture->tImgInfo.Width >> 1, pTexTexture->tImgInfo.Height >> 1, 0.f), // 출력할 이미지의 센터 지점	
			NULL,  // 출력할 이미지 포지션(출력 위치)
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CObjMgr::Release(void)
{
	for (size_t i = 0; i < CValueMgr::OBJ_END; ++i)
	{
		for_each(m_vecObj[i].begin(), m_vecObj[i].end(), DeleteOBJ());
		m_vecObj[i].clear();
	}
}
