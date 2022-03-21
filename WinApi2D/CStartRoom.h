#pragma once
#include "CScene.h"
#include "CTile.h"
#include "CTileNavMap.h"
class CStartRoom : public CScene
{
private:

	float m_duration = 1.f;
	float m_curTime = 0.f;

public:
	CStartRoom();
	virtual ~CStartRoom();

	virtual void update();

	virtual void Enter();
	virtual void Exit();

	
};

