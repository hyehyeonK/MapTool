#pragma once
#include "MapToolView.h"
#include "ControlForm.h"
#include "QuarterViewBack.h"
#include "TopViewBack.h"
#include "DebugDialog.h"

#define g_MGR_VALUE CValueMgr::GetInstance()

class CValueMgr
{
	DECLARE_SINGLETON(CValueMgr)

public:
	enum VIEWPOINT{TOPVIEW, QUARTER};
	enum TOOLTYPE { TOOL_TILE, TOOL_OBJ,TOOL_COLLI };
	enum OBJID
	{
		OBJ_A,
		OBJ_B,
		BJ_C,
		OBJ_D,
		OBJ_END
	};
private:
	CValueMgr();
	~CValueMgr();


public:	//View

	CMapToolView*	pMainView = nullptr;
	CControlForm*	pCtrlView = nullptr;
	CDebugDialog*	pDebugView = nullptr;

	CBackground*	m_pBackground[2];
	CPoint			m_Mouse;

	bool			m_bLineDraw;
	bool			m_bObjPosFromTile = true;

public:	//Value
	VIEWPOINT		eViewPoint = TOPVIEW;
	TOOLTYPE		currTool = TOOL_TILE;
	OBJID			currObj = OBJ_A;
	int					iColum = 0;
	int					iRow = 0;
	int					iTileW = TILECX;
	int					iTileH = TILECY;

	D3DXVECTOR3         m_Scale;
	D3DXMATRIX			m_WorldMat;

private:
	D3DXMATRIX			m_ScaleMat;

public:
	void Initialize();
	void Progress();
	void Release();
	void BackGroundRender();
	CBackground* GetBackGround();
};

