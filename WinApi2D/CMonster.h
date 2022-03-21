#pragma once
#include "CGameObject.h"
#include "CCharacter.h"
class CD2DImage;

class CMonster : public CCharacter 
{
private:
	fVec2 m_dirVec2;
	float m_veclocity = 100.f;	
	float m_hp = 100.f;
	bool is_stop = true;

	list<iPoint> m_destinations;
	list<iPoint>::iterator m_curIter;
	

public:
	CMonster();
	virtual ~CMonster();

	virtual void update();
	virtual void render();

	void SetDestination(const list<iPoint>& des);
	void GoDestition();
};

