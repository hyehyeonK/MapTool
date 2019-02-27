#include "stdafx.h"
#include "ObjMgr.h"


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
}

void CObjMgr::Progress(void)
{
}

void CObjMgr::Render(void)
{
}

void CObjMgr::Release(void)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for_each(m_vecObj[i].begin(), m_vecObj[i].end(), DeleteOBJ());
		m_vecObj[i].clear();
	}
}
