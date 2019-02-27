#include "stdafx.h"
#include "QuarterViewBack.h"
#include "TileMgr.h"

CQuarterViewBack::CQuarterViewBack()
{
}


CQuarterViewBack::~CQuarterViewBack()
{
	Release();
}

HRESULT CQuarterViewBack::Initialize()
{
	g_MGR_TILE->Release();
	TILE*		pTile = nullptr;
	float fX = 0;
	float fY = 0;
	//Tile vec
	HalfMaxWidth = float(((m_pValueMgr->iColum + m_pValueMgr->iRow) * m_pValueMgr->iTileW >> 1)>>1);
	HalfMaxHeight = float(((m_pValueMgr->iColum + m_pValueMgr->iRow - 1) * m_pValueMgr->iTileH >> 1)>>1);

	m_vecTile.resize(m_pValueMgr->iColum);
	for (int iY = 0; iY < m_pValueMgr->iColum; ++iY)
	{
		m_vecTile[iY].resize(m_pValueMgr->iRow);
		for (int iX = 0; iX < m_pValueMgr->iRow; ++iX)
		{
			fX = (m_pValueMgr->iColum * (m_pValueMgr->iTileW >> 1)) + (m_pValueMgr->iTileW >> 1) * float(iX - iY);
			fY = (m_pValueMgr->iTileH >> 1) * float(iX + iY + 1);

			pTile = new TILE;
			pTile->vPos = D3DXVECTOR3(fX, fY, 0.f);
			pTile->vSize = D3DXVECTOR3((float)m_pValueMgr->iTileW, (float)m_pValueMgr->iTileH, 0.f);
			pTile->byOption = 0;
			pTile->byDrawID = TILE_COUNT;

			m_vecTile[iY][iX] = pTile;
		}
	}
	m_ptCurrIdx.x = -1;

	return S_OK;
}

int CQuarterViewBack::Progress()
{
	return 0;
}

void CQuarterViewBack::Render()
{
	D3DXMATRIX	matTrans;
	TCHAR			szIdx[MIN_STR] = L"";
	const TEXINFO*		pTexTexture;
	D3DXVECTOR2 vList[5] = {};

	//float	fX, fY = 0;
	m_pGraphicDev->GetLine()->Begin();
	for (int i = 0; i < m_pValueMgr->iColum; ++i)
	{
		for (int j = 0; j < m_pValueMgr->iRow; ++j)
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
					m_vecTile[i][j]->vPos.y - (m_pValueMgr->iTileH >> 1) - m_pMainView->GetScrollPos(1) };
				vList[1] = { m_vecTile[i][j]->vPos.x + (m_pValueMgr->iTileW >> 1) - m_pMainView->GetScrollPos(0),
					m_vecTile[i][j]->vPos.y - m_pMainView->GetScrollPos(1) };
				vList[2] = { m_vecTile[i][j]->vPos.x - m_pMainView->GetScrollPos(0),
					m_vecTile[i][j]->vPos.y + (m_pValueMgr->iTileH >> 1) - m_pMainView->GetScrollPos(1) };
				vList[3] = { m_vecTile[i][j]->vPos.x - (m_pValueMgr->iTileW >> 1) - m_pMainView->GetScrollPos(0),
					m_vecTile[i][j]->vPos.y - m_pMainView->GetScrollPos(1) };
				vList[4] = { m_vecTile[i][j]->vPos.x - m_pMainView->GetScrollPos(0),
					m_vecTile[i][j]->vPos.y - (m_pValueMgr->iTileH >> 1) - m_pMainView->GetScrollPos(1) };

				m_pGraphicDev->GetLine()->Draw(vList, 5, D3DCOLOR_XRGB(0, 255, 0));
			}

			D3DXMatrixTranslation(&matTrans,
				m_vecTile[i][j]->vPos.x - m_pMainView->GetScrollPos(0) - m_pValueMgr->iTileW / 4,
				m_vecTile[i][j]->vPos.y - m_pMainView->GetScrollPos(1) - m_pValueMgr->iTileH / 4,
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

		vList[0] = { m_vecTile[m_ptCurrIdx.y][m_ptCurrIdx.x]->vPos.x - m_pMainView->GetScrollPos(0),
			m_vecTile[m_ptCurrIdx.y][m_ptCurrIdx.x]->vPos.y - (m_pValueMgr->iTileH >> 1) - m_pMainView->GetScrollPos(1) };
		vList[1] = { m_vecTile[m_ptCurrIdx.y][m_ptCurrIdx.x]->vPos.x + (m_pValueMgr->iTileW >> 1) - m_pMainView->GetScrollPos(0),
			m_vecTile[m_ptCurrIdx.y][m_ptCurrIdx.x]->vPos.y - m_pMainView->GetScrollPos(1) };
		vList[2] = { m_vecTile[m_ptCurrIdx.y][m_ptCurrIdx.x]->vPos.x - m_pMainView->GetScrollPos(0),
			m_vecTile[m_ptCurrIdx.y][m_ptCurrIdx.x]->vPos.y + (m_pValueMgr->iTileH >> 1) - m_pMainView->GetScrollPos(1) };
		vList[3] = { m_vecTile[m_ptCurrIdx.y][m_ptCurrIdx.x]->vPos.x - (m_pValueMgr->iTileW >> 1) - m_pMainView->GetScrollPos(0),
			m_vecTile[m_ptCurrIdx.y][m_ptCurrIdx.x]->vPos.y - m_pMainView->GetScrollPos(1) };
		vList[4] = { m_vecTile[m_ptCurrIdx.y][m_ptCurrIdx.x]->vPos.x - m_pMainView->GetScrollPos(0),
			m_vecTile[m_ptCurrIdx.y][m_ptCurrIdx.x]->vPos.y - (m_pValueMgr->iTileH >> 1) - m_pMainView->GetScrollPos(1) };

		m_pGraphicDev->GetLine()->Draw(vList, 5, D3DCOLOR_XRGB(255, 0, 0));
		m_pGraphicDev->GetLine()->End();
		m_pGraphicDev->GetLine()->SetWidth(1.f);
	}
}

void CQuarterViewBack::Release()
{
}
