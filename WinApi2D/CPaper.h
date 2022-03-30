#pragma once
#include "CGameObject.h"
class CPaper : public CGameObject
{
private:
	CD2DImage* m_pImg;
public:
	CPaper();
	~CPaper();

	virtual CPaper* Clone();
	virtual void update();
	virtual void render();
};

