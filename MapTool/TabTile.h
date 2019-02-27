#pragma once
#include "afxwin.h"
#include "FileInfo.h"
#include "afxcmn.h"


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
	float m_ScaleX;
	float m_ScaleY;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_ListBox;
	CStatic m_Picture;
	CSliderCtrl m_SliderScale;
	CEdit m_EditScale;

public:
	virtual BOOL OnInitDialog();

public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnTileList();
	afx_msg void OnScaleX();
	afx_msg void OnScaleY();


	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

};
