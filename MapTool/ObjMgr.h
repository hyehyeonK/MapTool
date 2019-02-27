#pragma once
#include "../Headers/Include.h"

#define g_MGR_OBJ CObjMgr::GetInstance()

class CObjMgr
{
	DECLARE_SINGLETON(CObjMgr)

public:


private:
	CObjMgr();
	~CObjMgr();

public:
	vector<INFO*>& GetObjects() { return *m_vecObj; }
	vector<INFO*>& GetObjects(CValueMgr::OBJID _id) { return m_vecObj[_id]; }
public:
	void Initialize(void);
	void Render(void);
	void Release(void);

private:
	vector<INFO*> m_vecObj[CValueMgr::OBJ_END];

};

  