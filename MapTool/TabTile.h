#pragma once
#include "afxwin.h"
#include "FileInfo.h"


// CTabTile 대화 상자입니다.

class CTabTile : public CDialog
{
	DECLARE_DYNAMIC(CTabTile)

public:
	CTabTile(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTabTile();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_TILE };
#endif
private:
	void HorizontalScroll();

public: // value
	map<CString, CImage*>		m_mapPngImage;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
