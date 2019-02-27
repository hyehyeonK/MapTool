// TabObject.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MapTool.h"
#include "TabObject.h"
#include "afxdialogex.h"


// CTabObject 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTabObject, CDialog)

CTabObject::CTabObject(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_TAB_OBJ, pParent)
{

}

CTabObject::~CTabObject()
{
}

void CTabObject::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTabObject, CDialog)
END_MESSAGE_MAP()


// CTabObject 메시지 처리기입니다.
