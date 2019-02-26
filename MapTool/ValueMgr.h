#pragma once
#include "../Headers/Include.h"

#define g_MGR_DATA CValueMgr::GetInstance()

class CValueMgr
{
	DECLARE_SINGLETON(CValueMgr)

private:
	CValueMgr();
	~CValueMgr();

public:

};

