#pragma once
#include "CCharacter.h"
#include "CCollider.h"
#include "CIsaacPlayer.h"
class CPlayerLeft : public CCharacter
{
	
		 
private:

public:
	CPlayerLeft();
	~CPlayerLeft();

	virtual CPlayerLeft* Clone();
	virtual void update();
	virtual void render();
	virtual void finalupdate();


	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);
};

