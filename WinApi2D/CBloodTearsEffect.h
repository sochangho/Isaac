#pragma once
#include "CEffect.h"
class CBloodTearsEffect :  public CEffect
{
private:


public:
	CBloodTearsEffect();
	~CBloodTearsEffect();

	virtual CBloodTearsEffect* Clone();

	virtual void update();
	virtual void render();

};

