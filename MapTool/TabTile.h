#pragma once
#include "afxwin.h"
#include "FileInfo.h"


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
private:
	void HorizontalScroll();

public: // value
	map<CString, CImage*>		m_mapPngImage;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_ListBox;
	CStatic m_Picture;

public:
	float m_ScaleX;
	float m_ScaleY;

public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnTileList();
	afx_msg void OnScaleX();
	afx_msg void OnScaleY();
	virtual BOOL OnInitDialog();
};
