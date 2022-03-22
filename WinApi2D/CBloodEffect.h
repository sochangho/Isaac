#pragma once
#include "CEffect.h"
class CBloodEffect :public CEffect
{
public:
	CBloodEffect();
	~CBloodEffect();

	virtual CBloodEffect* clone();


	virtual void update();
	virtual void render();

};

