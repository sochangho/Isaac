#pragma once
#include "CGameObject.h"
#include "CCharacter.h"
class CD2DImage;

class CMonster : public CCharacter 
{
private:
	fVec2 m_dirVec2;
	
	float m_hp = 100.f;
	bool is_stop = true;

	CGameObject* m_destinationObj;


	list<iPoint> m_destinations;
	list<iPoint>::iterator m_curIter;
	

public:
	float m_veclocity = 150.f;
	CMonster();
	virtual ~CMonster();

	virtual void update();
	virtual void render();
	virtual void finalupdate();

	void SetDestination(const list<iPoint>& des);
	void GoDestition();
	
	fVec2 GetMonsterDir();
	bool GetStop();

};

