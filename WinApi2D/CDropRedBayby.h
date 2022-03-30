#pragma once
#include "CDropItem.h"
#include "CD2DImage.h"
#include "CIsaacPlayer2.h"
class CDropRedBayby :public CDropItem
{
private:

	CD2DImage* m_Img;

public:

	CDropRedBayby();
	~CDropRedBayby();

	virtual CDropRedBayby* Clone();
	virtual void update();
	virtual void render();


	virtual void OnCollision(CCollider* pOther);
	virtual void OnCollisionEnter(CCollider* pOther);
	virtual void OnCollisionExit(CCollider* pOther);

};

