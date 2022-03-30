#pragma once
#include "CDropItem.h"
#include "CD2DImage.h"
#include "CLilloki.h"
#include "CItem.h"
class CDropLilloki : public CDropItem
{
private:

	CD2DImage* m_Img;

public:
	CDropLilloki();
	~CDropLilloki();

	virtual CDropLilloki* Clone();
	virtual void update();
	virtual void render();


	virtual void OnCollision(CCollider* pOther);
	virtual void OnCollisionEnter(CCollider* pOther);
	virtual void OnCollisionExit(CCollider* pOther);

};

