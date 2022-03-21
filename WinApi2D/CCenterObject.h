#pragma once
#include "CGameObject.h"
class CCenterObject : public CGameObject
{

public:
	CCenterObject();
	~CCenterObject();

	virtual CCenterObject* Clone();
	virtual void update();
	virtual void render();

};

