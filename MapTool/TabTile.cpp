// TabTile.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MapTool.h"
#include "TabTile.h"
#include "afxdialogex.h"


// CTabTile 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTabTile, CDialog)

CTabTile::CTabTile(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_TAB_TILE, pParent)
{

}

CTabTile::~CTabTile()
{
}

void CTabTile::HorizontalScroll()
{
	CString strName;
	CSize csize;

	int iDCX = 0;

	CDC* pDC = m_ListBox.GetDC();

	for (int i = 0; i < m_ListBox.GetCount(); ++i)
	{
		m_ListBox.GetText(i, strName);
		csize = pDC->GetTextExtent(strName);

		if (csize.cx > iDCX)
			iDCX = csize.cx;
	}
	m_ListBox.ReleaseDC(pDC);

	if (m_ListBox.GetHorizontalExtent() < iDCX)
		m_ListBox.SetHorizontalExtent(iDCX);
}

void CTabTile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_PICTURE, m_Picture);
}


BEGIN_MESSAGE_MAP(CTabTile, CDialog)
	ON_WM_DROPFILES()
	ON_LBN_SELCHANGE(IDC_LIST1, &CTabTile::OnTileList)
END_MESSAGE_MAP()


// CTabTile 메시지 처리기입니다.


void CTabTile::OnDropFiles(HDROP hDropInfo)
{
	UpdateData(TRUE);

	CFileInfo	FileInfo;

	int iFileNumber = DragQueryFile(hDropInfo, -1, NULL, 0);
	// 드래그 및 드롭한 파일의 개수를 반환해주는 함수
	// 1인자 : 드롭된 파일 정보 구조체
	// 2인자 : 파일의 인덱스 지정, 인자값에 -1을 넣는 경우 함수의 반환값으로 파일 개수 반환
	// 3인자 : 버퍼 포인터(문자열 사이즈)
	// 4인자 : 지정한 버퍼 사이즈 0 : 최대 사이즈

	TCHAR szFullPath[MAX_PATH] = L"";
	CString strImagName;

	for (int i = 0; i < iFileNumber; ++i)
	{
		DragQueryFile(hDropInfo, i, (LPWSTR)szFullPath, MAX_PATH);

		wstring wstrRelativePath = FileInfo.ConvertRelativePath(szFullPath);

		strImagName = PathFindFileName(szFullPath);

		PathRemoveExtension((LPWSTR)strImagName.operator LPCWSTR());

		auto iter = m_mapPngImage.find(strImagName);

		if (iter == m_mapPngImage.end())
		{
			CImage* pPngImage = new CImage;
			pPngImage->Load(wstrRelativePath.c_str());

			m_mapPngImage.emplace(strImagName, pPngImage);
			m_ListBox.AddString(strImagName);
		}
	}

	HorizontalScroll();

	CDialog::OnDropFiles(hDropInfo);

	UpdateData(FALSE);
}


void CTabTile::OnTileList()
{
	UpdateData(TRUE);

	CString strSelectName;

	int iSelectIndex = m_ListBox.GetCurSel();
	if (0 > iSelectIndex)
		return;

	m_ListBox.GetText(iSelectIndex, strSelectName);

	auto iter = m_mapPngImage.find(strSelectName);

	if (iter == m_mapPngImage.end())
		return;

	m_Picture.SetBitmap(*(iter->second));

	CString TextureID = strSelectName;
	TextureID.TrimRight(L"0123456789");
	TextureID += L"%d";
	int iTileNumber = 20;
	sscanf_s((CStringA)strSelectName, (CStringA)TextureID, &iTileNumber);

	g_MGR_VALUE->GetBackGround()->m_byDrawID = ((BYTE)iTileNumber);

	UpdateData(FALSE);
}
