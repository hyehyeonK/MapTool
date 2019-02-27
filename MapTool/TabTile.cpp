// TabTile.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MapTool.h"
#include "TabTile.h"
#include "afxdialogex.h"


// CTabTile 대화 상자입니다.

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
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_PICTURE, m_Picture);
}


BEGIN_MESSAGE_MAP(CTabTile, CDialog)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CTabTile 메시지 처리기입니다.


void CTabTile::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialog::OnDropFiles(hDropInfo);
}
