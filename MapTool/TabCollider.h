#pragma once


// CTabCollider ��ȭ �����Դϴ�.

class CTabCollider : public CDialog
{
	DECLARE_DYNAMIC(CTabCollider)

public:
	CTabCollider(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTabCollider();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_COLLI };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
