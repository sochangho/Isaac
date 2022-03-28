#pragma once
#include "CGameObject.h"
#include "CD2DImage.h"
class CTitle : public CGameObject
{
private:
	CD2DImage* m_pImg;


public:
	CTitle();
	~CTitle();
	
	virtual CTitle* Clone();
	virtual void update();
	virtual void render();




};

