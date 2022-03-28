#pragma once
#include "CGameObject.h"
#include "CCharacter.h"
class CD2DImage;

class CMonster : public CCharacter 
{

private:

	float m_moveDuration = 2.f;
	float m_time = 0.f;

	fVec2 m_dirVec2;
	fVec2 m_Anidir;

	fPoint randomDestonaion;

	
	float  m_hp = 100.f;
	float m_attackedDuration = 0.4f;
	float m_attackedTime = 0.f;

	bool is_stop = true;
	bool is_init = false;
	bool is_attacked = false;


	CGameObject* m_destitionobj;

	list<iPoint> m_destinations;
	list<iPoint>::iterator m_curIter;
	
	
public:
	float m_veclocity = 40.f;
	float m_attackedV = 30.f;
	CMonster();
	virtual ~CMonster();

	virtual void update();
	virtual void render();
	virtual void finalupdate();


	void SetDestinaionObj(CGameObject* obj);
	void SetDestination(const list<iPoint>& des);
	void SetStop(bool stop);

	bool GoDestition();
	bool GoRandom();

	fVec2 GetMonsterDir();
	bool GetStop();
	CGameObject* getDestination();

	void ChangeDir(fPoint startPoint);
	void Attacked();
	void MonsterRandomPosInit();
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);
	
};

