#pragma once
#include "../Headers/Include.h"

class CFileInfo
{
public:
	std::wstring ConvertRelativePath(wstring szFullPath);

public:
	CFileInfo();
	~CFileInfo();
};

