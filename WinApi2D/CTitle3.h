#pragma once
#include "CGameObject.h"
#include "CD2DImage.h"
class CTitle3 : public CGameObject
{
private:
	CD2DImage* m_pImg;

public:
	CTitle3();
	~CTitle3();

	virtual CTitle3* Clone();
	virtual void update();
	virtual void render();
};

