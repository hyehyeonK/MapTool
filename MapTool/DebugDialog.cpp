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
