// TabTile.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MapTool.h"
#include "TabTile.h"
#include "afxdialogex.h"


// CTabTile ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CTabTile, CDialog)

CTabTile::CTabTile(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_TAB_TILE, pParent)
{

}

CTabTile::~CTabTile()
{
}

void CTabTile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTabTile, CDialog)
END_MESSAGE_MAP()


// CTabTile �޽��� ó�����Դϴ�.
