#include "stdafx.h"
#include "ValueMgr.h"


IMPLEMENT_SINGLETON(CValueMgr)

CValueMgr::CValueMgr()
	: m_pBackground()
{
}


CValueMgr::~CValueMgr()
{
	Release();
}

void CValueMgr::Initialize()
{
	m_pBackground[QUARTER] = new CQuarterViewBack;
	m_pBackground[TOPVIEW] = new CTopViewBack;
	m_pBackground[QUARTER]->Initialize();
	m_pBackground[TOPVIEW]->Initialize();
}

void CValueMgr::Progress()
{
	if (pMainView) pMainView->Invalidate(FALSE);
}

void CValueMgr::Release()
{
	Safe_Delete(m_pBackground[QUARTER]);
	Safe_Delete(m_pBackground[TOPVIEW]);
}

CBackground* CValueMgr::GetBackGround()
{
	return m_pBackground[eViewPoint];
}
