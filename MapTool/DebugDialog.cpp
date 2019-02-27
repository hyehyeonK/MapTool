// DebugDialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MapTool.h"
#include "DebugDialog.h"
#include "afxdialogex.h"


// CDebugDialog ��ȭ �����Դϴ�.

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


// CDebugDialog �޽��� ó�����Դϴ�.


BOOL CDebugDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	g_MGR_VALUE->pDebugView = this;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
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
