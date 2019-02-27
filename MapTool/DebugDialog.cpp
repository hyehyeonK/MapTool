// DebugDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MapTool.h"
#include "DebugDialog.h"
#include "afxdialogex.h"


// CDebugDialog 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDebugDialog, CDialog)

CDebugDialog::CDebugDialog(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DEBUGDIALOG, pParent)
{

}

CDebugDialog::~CDebugDialog()
{
}

void CDebugDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	
}


BEGIN_MESSAGE_MAP(CDebugDialog, CDialog)
END_MESSAGE_MAP()


// CDebugDialog 메시지 처리기입니다.


BOOL CDebugDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	g_MGR_VALUE->pDebugView = this;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDebugDialog::Update()
{
	TCHAR str[128];

	wsprintf(str, L"Mouse LX : %d", g_MGR_VALUE->m_Mouse.x);
	SetDlgItemText(IDC_MOUSELX, str);

	wsprintf(str, L"Mouse LY : %d", g_MGR_VALUE->m_Mouse.y);
	SetDlgItemText(IDC_MOUSELY, str);

	wsprintf(str, L"Mouse WX : %d", g_MGR_VALUE->m_Mouse.x + g_MGR_VALUE->pMainView->GetScrollPos(0));
	SetDlgItemText(IDC_MOUSEWX, str);

	wsprintf(str, L"Mouse WY : %d", g_MGR_VALUE->m_Mouse.y + g_MGR_VALUE->pMainView->GetScrollPos(1));
	SetDlgItemText(IDC_MOUSEWY, str);

	wsprintf(str, L"Scroll X : %d", g_MGR_VALUE->pMainView->GetScrollPos(0));
	SetDlgItemText(IDC_SCROLLX, str);

	wsprintf(str, L"Scroll Y : %d", g_MGR_VALUE->pMainView->GetScrollPos(1));
	SetDlgItemText(IDC_SCROLLY, str);

	wsprintf(str, L"Colum : %d", g_MGR_VALUE->iColum);
	SetDlgItemText(IDC_COLUM, str);

	wsprintf(str, L"Row : %d", g_MGR_VALUE->iRow);
	SetDlgItemText(IDC_ROW, str);

	wsprintf(str, L"TileW : %d", g_MGR_VALUE->iTileW);
	SetDlgItemText(IDC_TILEW, str);

	wsprintf(str, L"TileH : %d", g_MGR_VALUE->iTileH);
	SetDlgItemText(IDC_TILEH, str);
}
