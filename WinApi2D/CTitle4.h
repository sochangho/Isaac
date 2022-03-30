#pragma once
#include "CGameObject.h"
#include "CD2DImage.h"
class CTitle4 : public CGameObject
{
private:
	CD2DImage* m_pImg;

public:
	CTitle4();
	~CTitle4();

	virtual CTitle4* Clone();
	virtual void update();
	virtual void render();
};

