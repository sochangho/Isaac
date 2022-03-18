#pragma once
#include "CCharacter.h"
class CPlayerRight : public CCharacter
{
private:


public:

	CPlayerRight();
	~CPlayerRight();

	virtual CPlayerRight* Clone();
	virtual void update();
	virtual void render();
	virtual void finalupdate();


	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);
};

