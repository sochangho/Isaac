#pragma once
#include "CGameObject.h"
#include "CD2DImage.h"
class CTitle1 : public CGameObject
{
private:

	CD2DImage* m_pImg;

public:
	CTitle1();
	~CTitle1();
	virtual CTitle1* Clone();
	virtual void update();
	virtual void render();
};

