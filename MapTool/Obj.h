#pragma once
#include "../Headers/Include.h"

class CObj
{
public:
	virtual HRESULT Initialize() PURE;
	virtual int			Progress() PURE;
	virtual void			Render() PURE;
	virtual void			Release() PURE;

public:
	CObj();
	virtual ~CObj();
};

