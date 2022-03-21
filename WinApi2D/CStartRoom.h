#pragma once
#include "CScene.h"
#include "CTile.h"
#include "CTileNavMap.h"
class CStartRoom : public CScene
{
private:

	CTileNavMap* tileNav;

public:
	CStartRoom();
	virtual ~CStartRoom();

	virtual void update();

	virtual void Enter();
	virtual void Exit();

	
};

