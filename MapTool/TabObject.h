#pragma once
#include "afxwin.h"


// CTabObject ��ȭ �����Դϴ�.

class CTabObject : public CDialog
{
	DECLARE_DYNAMIC(CTabObject)

public:
	CTabObject(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTabObject();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_OBJ };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public: // control
	CListBox m_ListBox;
	CStatic m_Picture;

public: // General
	map<CString, CImage*> m_mapPngImage;
	int m_iDrawID = 0;

public:
	afx_msg void OnSaveObjFile();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnListBox();
	afx_msg void OnIndexBoxCheck();
};
