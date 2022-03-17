#pragma once
#include "CEffect.h"
class CTearsEffect : public CEffect
{
private:

public:
	CTearsEffect();
	~CTearsEffect();

	virtual CTearsEffect* Clone();

	virtual void update();
	virtual void render();

	
};

