#pragma once
#include "../Headers/Include.h"

#define g_MGR_OBJ CObjMgr::GetInstance()

class CObjMgr
{
	DECLARE_SINGLETON(CObjMgr)

public:
	enum OBJID
	{

		OBJ_END
	};

private:
	CObjMgr();
	~CObjMgr();

public:
	//vector<INFO*> m_vecObj&	GetObjects() { return m_vecObj; }
	//void InitTiles();
	//void Release();

private:
	vector<INFO*> m_vecObj[OBJ_END];

};

  