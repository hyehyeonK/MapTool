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
