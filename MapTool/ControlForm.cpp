// ControlForm.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MapTool.h"
#include "ControlForm.h"


// CControlForm

IMPLEMENT_DYNCREATE(CControlForm, CFormView)

CControlForm::CControlForm()
	: CFormView(IDD_CONTROLFORM)
{

}

CControlForm::~CControlForm()
{
}

void CControlForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CControlForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CControlForm::OnClickShowDebug)
END_MESSAGE_MAP()


// CControlForm �����Դϴ�.

#ifdef _DEBUG
void CControlForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CControlForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CControlForm �޽��� ó�����Դϴ�.


void CControlForm::OnClickShowDebug()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (m_DebugDialog.GetSafeHwnd() == NULL)
	{
		m_DebugDialog.Create(IDD_DEBUGDIALOG);
	}
	m_DebugDialog.ShowWindow(SW_SHOW);

}
