#pragma once
#include "Obj.h"
class CCharactor : public CObj
{
public:
	CCharactor();
	~CCharactor();

public:
	virtual HRESULT Initialize() override;
	virtual int Progress() override;
	virtual void Render() override;
	virtual void Release() override;


};

