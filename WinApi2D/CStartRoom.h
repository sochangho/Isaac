#pragma once
#include "CScene.h"
#include "CTile.h"
class CStartRoom : public CScene
{
private:

	CTile** roadTile;

public:
	CStartRoom();
	virtual ~CStartRoom();

	virtual void update();

	virtual void Enter();
	virtual void Exit();

};

