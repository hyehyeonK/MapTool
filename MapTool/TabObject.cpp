// TabObject.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MapTool.h"
#include "TabObject.h"
#include "afxdialogex.h"


// CTabObject ��ȭ �����Դϴ�.

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


// CTabObject �޽��� ó�����Դϴ�.
