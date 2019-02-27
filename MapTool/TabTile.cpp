// TabTile.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MapTool.h"
#include "TabTile.h"
#include "afxdialogex.h"
#include "TileMgr.h"

// CTabTile ��ȭ �����Դϴ�.

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


// CTabTile �޽��� ó�����Դϴ�.


void CTabTile::OnDropFiles(HDROP hDropInfo)
{
	UpdateData(TRUE);

	CFileInfo	FileInfo;

	int iFileNumber = DragQueryFile(hDropInfo, -1, NULL, 0);
	// �巡�� �� ����� ������ ������ ��ȯ���ִ� �Լ�
	// 1���� : ��ӵ� ���� ���� ����ü
	// 2���� : ������ �ε��� ����, ���ڰ��� -1�� �ִ� ��� �Լ��� ��ȯ������ ���� ���� ��ȯ
	// 3���� : ���� ������(���ڿ� ������)
	// 4���� : ������ ���� ������ 0 : �ִ� ������

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
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);
	g_MGR_VALUE->m_TileScale.x = m_ScaleX;
	UpdateData(FALSE);
}


void CTabTile::OnScaleY()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);
	g_MGR_VALUE->m_TileScale.y = m_ScaleY;
	UpdateData(FALSE);
}


BOOL CTabTile::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	UpdateData(TRUE);
	m_ScaleX = 1.f;
	m_ScaleY = 1.f;
	UpdateData(FALSE);


	m_SliderScale.SetRange(0, 20);
	m_SliderScale.SetRangeMin(0);
	m_SliderScale.SetRangeMax(20);
	m_SliderScale.SetPos(10);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CTabTile::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	UpdateData(TRUE);
	D3DXVECTOR3 scale;
	if (pScrollBar)
	{
		// � �����̴����� �˻�
		if (pScrollBar == (CScrollBar*)&m_SliderScale)
		{
			// �����̴��� ��ġ�� �˻��Ѵ�.
			int nPos = m_SliderScale.GetPos();
			m_ScaleX = float(nPos / 10.f);
			scale = { m_ScaleX ,m_ScaleX ,0.f };
			g_MGR_TILE->GetTiles()[g_MGR_VALUE->m_SelectTileIdx.y][g_MGR_VALUE->m_SelectTileIdx.x]->vSize = scale;
		}
	}
	UpdateData(FALSE);
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
