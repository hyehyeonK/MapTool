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
	vector<INFO*>& GetObjects() { return *m_vecObj; }

public:
	void Initialize(void);
	void Progress(void);
	void Render(void);
	void Release(void);

private:
	vector<INFO*> m_vecObj[OBJ_END];

};

  