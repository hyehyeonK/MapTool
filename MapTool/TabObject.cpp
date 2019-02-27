// TabObject.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MapTool.h"
#include "TabObject.h"
#include "afxdialogex.h"
#include "FileInfo.h"


// CTabObject 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTabObject, CDialog)

CTabObject::CTabObject(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_TAB_OBJ, pParent)
{

}

CTabObject::~CTabObject()
{
}

void CTabObject::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1_S, m_ListBox);
	DDX_Control(pDX, IDC_PICTURE_S, m_Picture);
}


BEGIN_MESSAGE_MAP(CTabObject, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1_S, &CTabObject::OnSaveObjFile)
	ON_WM_DROPFILES()
	ON_LBN_SELCHANGE(IDC_LIST1_S, &CTabObject::OnListBox)
END_MESSAGE_MAP()


// CTabObject 메시지 처리기입니다.


void CTabObject::OnSaveObjFile()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog Dlg(FALSE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"*.dat", this);

	if (Dlg.DoModal() == IDCANCEL)
		return;

	TCHAR szDirPath[MAX_PATH];
	GetCurrentDirectory(sizeof(szDirPath), szDirPath);
	SetCurrentDirectory(szDirPath);
	PathRemoveFileSpec(szDirPath);
	lstrcat(szDirPath, L"\\Data");

	// 파일 다이얼로그 초기 폴더 지정
	Dlg.m_ofn.lpstrInitialDir = szDirPath;

	HANDLE hFile = CreateFile(
		Dlg.GetPathName(), GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD dwByte;

	//WriteFile();

	CloseHandle(hFile);
}


void CTabObject::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	UpdateData(TRUE);

	CFileInfo FileInfo;

	int iFileNum = DragQueryFile(hDropInfo, -1, NULL, 0);

	TCHAR szFullPath[MAX_PATH] = L"";
	CString strImageName;

	for (int i = 0; i < iFileNum; ++i)
	{
		DragQueryFile(hDropInfo, i, (LPWSTR)szFullPath, MAX_PATH);

		wstring wstrRelativePath = FileInfo.ConvertRelativePath(szFullPath);

		strImageName = PathFindFileName(szFullPath);

		PathRemoveExtension((LPWSTR)strImageName.operator LPCWSTR());

		auto iter = m_mapPngImage.find(strImageName);

		if (iter == m_mapPngImage.end())
		{
			CImage* pPngImage = new CImage;
			pPngImage->Load(wstrRelativePath.c_str());
			m_mapPngImage.emplace(strImageName, pPngImage);
			m_ListBox.AddString(strImageName);
		}
	}

	CDialog::OnDropFiles(hDropInfo);

	UpdateData(FALSE);
}


void CTabObject::OnListBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CString strSelectName;

	int iSelectIndex = m_ListBox.GetCurSel();
	if (0 > iSelectIndex)
		return;

	m_ListBox.GetText(iSelectIndex, strSelectName);

	auto iter = m_mapPngImage.find(strSelectName);
	if (iter == m_mapPngImage.end())
		return;

	m_Picture.SetBitmap(*iter->second);

	int i = 0;
	for (i = 0; i < strSelectName.GetLength(); ++i)
	{
		if (isdigit(strSelectName[i]) != 0)
			break;
	}

	strSelectName.Delete(0, i);
	m_iDrawID = _tstoi(strSelectName);


	UpdateData(FALSE);
}
