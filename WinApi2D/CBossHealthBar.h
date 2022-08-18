#pragma once
#include "CGameObject.h"
#include "CD2DImage.h"
#include "CMonster.h"
class CBossHealthBar : public CGameObject
{

private:
	CD2DImage* m_pImg;
	CMonster* m_monster;
public:
	CBossHealthBar();
	~CBossHealthBar();

	virtual CBossHealthBar* Clone();
	virtual void update();
	virtual void render();

	void SetMonster(CMonster* monster);
};

