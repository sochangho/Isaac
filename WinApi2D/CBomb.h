#pragma once
#include "CGameObject.h"
#include "CD2DImage.h"
#include "CCollider.h"
#include "CScaleAnimation.h"
#include "CTile.h"
#include "CIsaacPlayer.h"
#include "CCollider.h"
#include "CDropItem.h"
class CBomb : public CDropItem
{
private:
	CD2DImage* m_pImg;
	CScaleAnimation* scaleAnimation;
    


	float m_duration = 3.f;
	float m_curTime = 0.f;



public:

	CBomb();
	~CBomb();

	virtual CBomb* Clone();
	virtual void update();
	virtual void render();
	
	void Explosion();


};

