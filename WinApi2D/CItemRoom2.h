#pragma once
#include "CScene.h"
class CItemRoom2 : public CScene
{
private:

public:
	CItemRoom2();
	~CItemRoom2();

	virtual void update();
	virtual void init();
	virtual void Enter();
	virtual void Exit();
};

