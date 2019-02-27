#pragma once
#include "MapToolView.h"
#include "ControlForm.h"

#define g_MGR_VALUE CValueMgr::GetInstance()

class CValueMgr
{
	DECLARE_SINGLETON(CValueMgr)

public:
	enum VIEWPOINT{TOPVIEW, QUARTER};

private:
	CValueMgr();
	~CValueMgr();


public:	//View
	CMapToolView*	pMainView = nullptr;
	CControlForm*	pCtrlView = nullptr;

public:	//Value
	VIEWPOINT		eViewPoint = TOPVIEW;
	int					iColum = 0;
	int					iRow = 0;
	int					iTileW = TILECX;
	int					iTileH = TILECY;

};

