#pragma once
#include "afxwin.h"


// CTabTile ��ȭ �����Դϴ�.

class CTabTile : public CDialog
{
	DECLARE_DYNAMIC(CTabTile)

public:
	CTabTile(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTabTile();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_TILE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_ListBox;
	CStatic m_Picture;
	afx_msg void OnDropFiles(HDROP hDropInfo);
};
