#include "stdafx.h"
#include "Background.h"
#include "MapToolView.h"
#include "TileMgr.h"

CBackground::CBackground()
	:m_pGraphicDev(g_MGR_GRAPHIC),
	m_vecTile(g_MGR_TILE->GetTiles())
{
	//Test
}


CBackground::~CBackground()
{
	Release();
}

HRESULT CBackground::Initialize()
{
	//Tile vec
	HalfMaxWidth = TILEX * TILECX >> 1;
	HalfMaxHeight = TILEY * TILECY >> 1;

	TILE*		pTile = nullptr;
	float fX = 0;
	float fY = 0;
	m_vecTile.resize(TILEY);
	for (int iY = 0; iY < TILEY; ++iY)
	{
		m_vecTile[iY].resize(TILEX);
		for (int iX = 0; iX < TILEX; ++iX)
		{
			fX = HalfMaxWidth + (TILECX >> 1) * float(iX - iY);
			fY = (TILECY >> 1) * float(iX + iY + 1);

			pTile = new TILE;
			pTile->vPos = D3DXVECTOR3(fX, fY, 0.f);
			pTile->vSize = D3DXVECTOR3((float)TILECX, (float)TILECY, 0.f);
			pTile->byOption = 0;
			pTile->byDrawID = TILE_COUNT;

			m_vecTile[iY][iX] = pTile;
		}
	}

	return S_OK;
}

int CBackground::Progress()
{
	return 0;
}

void CBackground::Render()
{
	D3DXMATRIX	matTrans;
	TCHAR			szIdx[MIN_STR] = L"";
	const TEXINFO*		pTexTexture;
	D3DXVECTOR2 vList[5] = {};

	//float	fX, fY = 0;
	m_pGraphicDev->GetLine()->Begin();
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			//fX = HalfMaxWidth + ((signed int(pTexTexture->tImgInfo.Width) >> 1) * (j - i));
			//fY = (pTexTexture->tImgInfo.Height >> 1) * (j + i + 1);
			D3DXMatrixTranslation(&matTrans,
				m_vecTile[i][j]->vPos.x - m_pMainView->GetScrollPos(0),
				m_vecTile[i][j]->vPos.y - m_pMainView->GetScrollPos(1),
				0.f);
			m_pGraphicDev->GetSprite()->SetTransform(&matTrans);

			if (TILE_COUNT > m_vecTile[i][j]->byDrawID)
			{
				pTexTexture = CTextureMgr::GetInstance()->GetTexture(L"TILE", L"Tile", m_vecTile[i][j]->byDrawID);

				m_pGraphicDev->GetSprite()->Draw(
					pTexTexture->pTexture,
					NULL, // 보여줄 이미지 크기
					&D3DXVECTOR3(TILEIMG_SIZE >> 1, TILEIMG_SIZE >> 1, 0.f), // 출력할 이미지의 센터 지점	
					NULL,  // 출력할 이미지 포지션(출력 위치)
					D3DCOLOR_ARGB(255, 255, 255, 255));;
			}
			else
			{

				vList[0] = { m_vecTile[i][j]->vPos.x - m_pMainView->GetScrollPos(0),
								m_vecTile[i][j]->vPos.y - (TILECY >> 1) - m_pMainView->GetScrollPos(1) };
				vList[1] = { m_vecTile[i][j]->vPos.x + (TILECX >> 1) - m_pMainView->GetScrollPos(0),
								m_vecTile[i][j]->vPos.y - m_pMainView->GetScrollPos(1) };
				vList[2] = { m_vecTile[i][j]->vPos.x - m_pMainView->GetScrollPos(0), 
								m_vecTile[i][j]->vPos.y + (TILECY >> 1) - m_pMainView->GetScrollPos(1) };
				vList[3] = { m_vecTile[i][j]->vPos.x - (TILECX >> 1) - m_pMainView->GetScrollPos(0), 
								m_vecTile[i][j]->vPos.y - m_pMainView->GetScrollPos(1) };
				vList[4] = { m_vecTile[i][j]->vPos.x - m_pMainView->GetScrollPos(0), 
								m_vecTile[i][j]->vPos.y - (TILECY >> 1) - m_pMainView->GetScrollPos(1) };

				m_pGraphicDev->GetLine()->Draw(vList, 5, D3DCOLOR_XRGB(0, 255, 0));
			}

			D3DXMatrixTranslation(&matTrans,
				m_vecTile[i][j]->vPos.x - m_pMainView->GetScrollPos(0) - TILECX/4,
				m_vecTile[i][j]->vPos.y - m_pMainView->GetScrollPos(1) - TILECY / 4,
				0.f);
			m_pGraphicDev->GetSprite()->SetTransform(&matTrans);

			wsprintf(szIdx, L"(%d,%d)", i, j);
			m_pGraphicDev->GetFont()->DrawTextW(m_pGraphicDev->GetSprite(), szIdx,
				lstrlen(szIdx), NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
	m_pGraphicDev->GetLine()->End();

	m_pGraphicDev->GetSprite()->End();

	m_pGraphicDev->GetDevice()->EndScene();

	m_pGraphicDev->GetDevice()->BeginScene();

	m_pGraphicDev->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);




	if (m_ptCurrIdx.x != -1)
	{
		m_pGraphicDev->GetLine()->SetWidth(5.f);
		m_pGraphicDev->GetLine()->Begin();

		vList[0] = { m_vecTile[m_ptCurrIdx.x][m_ptCurrIdx.y]->vPos.x - m_pMainView->GetScrollPos(0),
			m_vecTile[m_ptCurrIdx.x][m_ptCurrIdx.y]->vPos.y - (TILECY >> 1) - m_pMainView->GetScrollPos(1) };
		vList[1] = { m_vecTile[m_ptCurrIdx.x][m_ptCurrIdx.y]->vPos.x + (TILECX >> 1) - m_pMainView->GetScrollPos(0),
			m_vecTile[m_ptCurrIdx.x][m_ptCurrIdx.y]->vPos.y - m_pMainView->GetScrollPos(1) };
		vList[2] = { m_vecTile[m_ptCurrIdx.x][m_ptCurrIdx.y]->vPos.x - m_pMainView->GetScrollPos(0),
			m_vecTile[m_ptCurrIdx.x][m_ptCurrIdx.y]->vPos.y + (TILECY >> 1) - m_pMainView->GetScrollPos(1) };
		vList[3] = { m_vecTile[m_ptCurrIdx.x][m_ptCurrIdx.y]->vPos.x - (TILECX >> 1) - m_pMainView->GetScrollPos(0),
			m_vecTile[m_ptCurrIdx.x][m_ptCurrIdx.y]->vPos.y - m_pMainView->GetScrollPos(1) };
		vList[4] = { m_vecTile[m_ptCurrIdx.x][m_ptCurrIdx.y]->vPos.x - m_pMainView->GetScrollPos(0),
			m_vecTile[m_ptCurrIdx.x][m_ptCurrIdx.y]->vPos.y - (TILECY >> 1) - m_pMainView->GetScrollPos(1) };

		m_pGraphicDev->GetLine()->Draw(vList, 5, D3DCOLOR_XRGB(255, 0, 0));
		m_pGraphicDev->GetLine()->End();
		m_pGraphicDev->GetLine()->SetWidth(1.f);
	}
}

void CBackground::Release()
{

}

POINT CBackground::GetTileIdx(const D3DXVECTOR3 & _vPos)
{
	float fSlop = float(TILECY) / TILECX;
	float fY = 0;
	float fX = 0;
	int		m_iTargetIdxY = 0;
	int		m_iTargetIdxX = 0;
	for (int i = 1; i <= TILEY; ++i)
	{
		fY = fSlop * _vPos.x - (HalfMaxHeight - TILECY * i);
		if (fY >  _vPos.y)
		{
			m_iTargetIdxY = i - 1;
			break;
		}
	}
	if (!(0 <= m_iTargetIdxY && signed int(m_vecTile.size()) > m_iTargetIdxY))
		return{ -1,-1 };

	m_iTargetIdxX =int( _vPos.x / (TILECX >> 1) - (TILEX - 1 - m_iTargetIdxY));
	fY = -fSlop * _vPos.x + (HalfMaxHeight + TILECY * m_iTargetIdxX);
	if (fY > _vPos.y)
	{
		--m_iTargetIdxX;
	}

	if (!(0 <= m_iTargetIdxX && m_iTargetIdxX < signed int(m_vecTile[0].size())))
		return{ -1,-1 };

	return{ m_iTargetIdxY,m_iTargetIdxX };
}

bool CBackground::Picking(const D3DXVECTOR3 & _vPos, const int & _iIdx)
{
	return false;
}

bool CBackground::DotPicking(const D3DXVECTOR3 & _vPos, const int & _iIdx)
{
	return false;
}

void CBackground::TileChange(const D3DXVECTOR3 & _vPos, const BYTE & _byDrawID)
{
	POINT vIdx = GetTileIdx(_vPos);
	
	if (-1 == vIdx.x)
		return;

	++m_vecTile[vIdx.x][vIdx.y]->byDrawID;

	if (m_vecTile[vIdx.x][vIdx.y]->byDrawID > TILE_COUNT)
		m_vecTile[vIdx.x][vIdx.y]->byDrawID = 0;
	m_vecTile[vIdx.x][vIdx.y]->byOption = 1; //충돌 여부
}

void CBackground::HighLightIndex(const D3DXVECTOR3 & _vPos)
{
	POINT vIdx = GetTileIdx(_vPos);

	if (-1 == vIdx.x)
	{
		m_ptCurrIdx = { -1,-1 };
	}
	else
	{
		m_ptCurrIdx = vIdx;
	}
}