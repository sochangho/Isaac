#pragma once
#include "CD2DImage.h"
#include "CCharacter.h"
class CPlayerHead : public CCharacter
{
private:
	CD2DImage* m_pImg;
public:
	CPlayerHead();
	~CPlayerHead();

	virtual CPlayerHead* Clone();
	virtual void update();
	virtual void render();
	virtual void finalupdate();

	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);
};

