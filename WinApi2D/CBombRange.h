#pragma once
#include "CGameObject.h"
class CBombRange :public CGameObject
{
private:

	float m_duration;
	float m_cur;


public:

	float m_dmg = 50.f;

	CBombRange();
	~CBombRange();

	virtual CBombRange* Clone();

	virtual void update();
	virtual void render();
	virtual void finalupdate();

};

