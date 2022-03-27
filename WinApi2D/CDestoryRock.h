#pragma once
#include "CGameObject.h"
class CDestoryRock : public CGameObject
{private:
	CD2DImage* m_pImg;

public:
	CDestoryRock();
	~CDestoryRock();

	virtual CDestoryRock* Clone();
	virtual void update();
	virtual void render();



};

