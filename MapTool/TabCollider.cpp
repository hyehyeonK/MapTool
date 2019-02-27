// TabCollider.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MapTool.h"
#include "TabCollider.h"
#include "afxdialogex.h"


// CTabCollider 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTabCollider, CDialog)

CTabCollider::CTabCollider(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_TAB_COLLI, pParent)
{

}

CTabCollider::~CTabCollider()
{
}

void CTabCollider::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTabCollider, CDialog)
END_MESSAGE_MAP()


// CTabCollider 메시지 처리기입니다.
