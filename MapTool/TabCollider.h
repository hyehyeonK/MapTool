#pragma once


// CTabCollider 대화 상자입니다.

class CTabCollider : public CDialog
{
	DECLARE_DYNAMIC(CTabCollider)

public:
	CTabCollider(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTabCollider();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_COLLI };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
