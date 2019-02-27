#pragma once
#include "Background.h"

class CGlobalMgr
{
	DECLARE_SINGLETON(CGlobalMgr)

private:
	CGlobalMgr();
	~CGlobalMgr();

private:
	CBackground		m_BackGround;

public:
	void Initialize();
	void Release();

public:
	CBackground*	GetBackGround() { return &m_BackGround; }
};

