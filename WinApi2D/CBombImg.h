#pragma once
#include "CGameObject.h"
#include "CD2DImage.h"
class CBombImg : public CGameObject
{
private:
	CD2DImage* m_pImg;
public:
	CBombImg();
	~CBombImg();
	virtual void update();
	virtual CBombImg* Clone();
	virtual void render();



};

