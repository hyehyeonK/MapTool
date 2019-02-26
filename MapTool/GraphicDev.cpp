#include "stdafx.h"
#include "GraphicDev.h"

IMPLEMENT_SINGLETON(CGraphicDev)

CGraphicDev::CGraphicDev()
{
}


CGraphicDev::~CGraphicDev()
{
	Release();
}

HRESULT CGraphicDev::Initialize()
{
	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);

	if (CreateDevieObj()	 != S_OK)	return E_FAIL;
	if (CreateSpriteObj()	 != S_OK)	return E_FAIL;
	if (CreateFontObj()	 != S_OK)	return E_FAIL;
	if (CreateLineObj()	 != S_OK)	return E_FAIL;

	return S_OK;
}

void CGraphicDev::Release()
{
	//해제 순서 중요
	m_pLine->Release();
	m_pFont->Release();
	m_pSprite->Release();
	m_pDevice->Release();
	m_pSDK->Release();
}

void CGraphicDev::SetParameters(D3DPRESENT_PARAMETERS & _d3dpp)
{
	_d3dpp.BackBufferWidth = WINCX;
	_d3dpp.BackBufferHeight = WINCY;
	_d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	_d3dpp.BackBufferCount = 1;

	_d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	_d3dpp.MultiSampleQuality = 0;

	_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	_d3dpp.hDeviceWindow = g_hWnd;

	_d3dpp.Windowed = TRUE;

	_d3dpp.EnableAutoDepthStencil = TRUE;
	_d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
}

void CGraphicDev::Render_Begin()
{
	m_pDevice->Clear(0, NULL,
		D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_ARGB(255, 0, 0, 255),
		1.f, 0);
	m_pDevice->BeginScene();
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void CGraphicDev::Render_End(HWND _hWnd)
{
	m_pSprite->End();
	m_pDevice->EndScene();
	m_pDevice->Present(NULL, NULL, _hWnd, NULL);
}

HRESULT CGraphicDev::CreateDevieObj()
{
	D3DCAPS9		DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));

	if (FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps)))
	{
		AfxMessageBox(L"장치 생성 실패");
		return E_FAIL;
	}

	DWORD		vp;

	if (DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	SetParameters(d3dpp);

	if (FAILED(m_pSDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, vp, &d3dpp, &m_pDevice)))
	{
		AfxMessageBox(L"디바이스 장치 생성 실패");
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CGraphicDev::CreateSpriteObj()
{
	if (FAILED(D3DXCreateSprite(m_pDevice, &m_pSprite)))
	{
		AfxMessageBox(L"스프라이트 생성 실패");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CGraphicDev::CreateFontObj()
{
	D3DXFONT_DESCW		tFontInfo;
	ZeroMemory(&tFontInfo, sizeof(D3DXFONT_DESCW));

	tFontInfo.Height = 20;
	tFontInfo.Width = 10;
	tFontInfo.Weight = FW_HEAVY;
	tFontInfo.CharSet = HANGEUL_CHARSET;
	lstrcpy(tFontInfo.FaceName, L"궁서");

	if (FAILED(D3DXCreateFontIndirect(m_pDevice, &tFontInfo, &m_pFont)))
	{
		AfxMessageBox(L"폰트 생성 실패");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CGraphicDev::CreateLineObj()
{
	if (FAILED(D3DXCreateLine(m_pDevice, &m_pLine)))
	{
		AfxMessageBox(L"라인 생성 실패");
		return E_FAIL;
	}
	return S_OK;
}
