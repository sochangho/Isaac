#pragma once
#include "CGameObject.h"
#include "CD2DImage.h"
class CTitle2 : public CGameObject
{private:
	CD2DImage* m_pImg;

public:
	CTitle2();
	~CTitle2();

	virtual CTitle2* Clone();
	virtual void update();
	virtual void render();




};

