#pragma once
#include "CScene.h"
class CNomalRoom1 : public CScene
{
private:
public:

	CNomalRoom1();
	~CNomalRoom1();

	virtual void update();
	virtual void init();
	virtual void Enter();
	virtual void Exit();
};

