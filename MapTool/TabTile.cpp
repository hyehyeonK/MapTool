// TabTile.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MapTool.h"
#include "TabTile.h"
#include "afxdialogex.h"
#include "TileMgr.h"

// CTabTile 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTabTile, CDialog)

CTabTile::CTabTile(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_TAB_TILE, pParent)
	, m_ScaleX(1.f)
	, m_ScaleY(1.f)
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
	DDX_Text(pDX, IDC_EDIT1, m_ScaleX);
	//DDV_MinMaxFloat(pDX, m_ScaleX, 0.1, 3.0);
	DDX_Text(pDX, IDC_EDIT2, m_ScaleY);
	//DDV_MinMaxFloat(pDX, m_ScaleY, 0.1, 3.0);
	DDX_Control(pDX, IDC_SLIDER_SCALE, m_SliderScale);
	DDX_Control(pDX, IDC_EDIT1, m_EditScale);
}


BEGIN_MESSAGE_MAP(CTabTile, CDialog)
	ON_WM_DROPFILES()
	ON_LBN_SELCHANGE(IDC_LIST1, &CTabTile::OnTileList)
	ON_EN_CHANGE(IDC_EDIT1, &CTabTile::OnScaleX)
	ON_EN_CHANGE(IDC_EDIT2, &CTabTile::OnScaleY)
	ON_WM_HSCROLL()
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


void CTabTile::OnScaleX()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);
	g_MGR_VALUE->m_TileScale.x = m_ScaleX;
	UpdateData(FALSE);
}


void CTabTile::OnScaleY()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);
	g_MGR_VALUE->m_TileScale.y = m_ScaleY;
	UpdateData(FALSE);
}


BOOL CTabTile::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	UpdateData(TRUE);
	m_ScaleX = 1.f;
	m_ScaleY = 1.f;
	UpdateData(FALSE);


	m_SliderScale.SetRange(0, 20);
	m_SliderScale.SetRangeMin(0);
	m_SliderScale.SetRangeMax(20);
	m_SliderScale.SetPos(10);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CTabTile::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	UpdateData(TRUE);
	D3DXVECTOR3 scale;
	if (pScrollBar)
	{
		// 어떤 슬라이더인지 검사
		if (pScrollBar == (CScrollBar*)&m_SliderScale)
		{
			// 슬라이더의 위치를 검사한다.
			int nPos = m_SliderScale.GetPos();
			m_ScaleX = float(nPos / 10.f);
			scale = { m_ScaleX ,m_ScaleX ,0.f };
			g_MGR_TILE->GetTiles()[g_MGR_VALUE->m_SelectTileIdx.y][g_MGR_VALUE->m_SelectTileIdx.x]->vSize = scale;
		}
	}
	UpdateData(FALSE);
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
