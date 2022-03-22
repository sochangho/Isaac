#pragma once
#include "CMonster.h"
class CGaper : public CMonster
{
public:


private:

	CGaper();
	~CGaper();
	virtual CGaper* Clone();
	virtual void update();
	virtual void render();

	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);


};

