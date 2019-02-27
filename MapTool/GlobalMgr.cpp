#include "stdafx.h"
#include "GlobalMgr.h"

IMPLEMENT_SINGLETON(CGlobalMgr)

CGlobalMgr::CGlobalMgr()
{
}


CGlobalMgr::~CGlobalMgr()
{
	Release();
}

void CGlobalMgr::Initialize()
{
	m_BackGround.Initialize();
}

void CGlobalMgr::Release()
{
}
