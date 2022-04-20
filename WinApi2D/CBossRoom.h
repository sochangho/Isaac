#pragma once
#include "CScene.h"
class CBossRoom : public CScene
{
private:

public:

	CBossRoom();
	~CBossRoom();



	virtual void update();
	virtual void init();
	virtual void Enter();
	virtual void Exit();
};

