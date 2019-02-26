#pragma once

#include "../Headers/Include.h"

#define		g_MGR_GRAPHIC CGraphicDev::GetInstance()

class CGraphicDev
{
	DECLARE_SINGLETON(CGraphicDev)

private:
	CGraphicDev();
	~CGraphicDev();

private:
	LPDIRECT3D9					m_pSDK	= nullptr;
	LPDIRECT3DDEVICE9		m_pDevice = nullptr;
	LPD3DXSPRITE				m_pSprite	= nullptr;
	LPD3DXFONT					m_pFont	= nullptr;
	LPD3DXLINE					m_pLine		= nullptr;

public:
	HRESULT		Initialize();
	void				Release();
	void				SetParameters(D3DPRESENT_PARAMETERS& _d3dpp);

	void				Render_Begin();
	void				Render_End(HWND _hWnd = NULL);

public:
	LPDIRECT3DDEVICE9		GetDevice(void) { return m_pDevice; }
	LPD3DXSPRITE			GetSprite(void) { return m_pSprite; }
	LPD3DXFONT				GetFont(void) { return m_pFont; }
	LPD3DXLINE				GetLine(void) { return m_pLine; }

private:
	HRESULT		CreateDevieObj();
	HRESULT		CreateSpriteObj();
	HRESULT		CreateFontObj();
	HRESULT		CreateLineObj();
};

