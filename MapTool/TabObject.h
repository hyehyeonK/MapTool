#pragma once


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
public:
	afx_msg void OnSaveObjFile();
	afx_msg void OnDropFiles(HDROP hDropInfo);
};
