#pragma once
#include "CGameObject.h"
#include "CD2DImage.h"
#include "CCollider.h"
#include "CScaleAnimation.h"
class CBomb : public CGameObject
{
private:
	CD2DImage* m_pImg;
	CScaleAnimation* scaleAnimation;
    
	fVec2 m_dir;

	float m_duration = 3.f;
	float m_curTime = 0.f;
	float m_velocity = 0.f;

	float m_adDuration = 0.2f;
	float m_adCurTime = 0.f;

	bool m_isPlayerCol = false;

    


public:

	CBomb();
	~CBomb();

	virtual CBomb* Clone();
	virtual void update();
	virtual void render();



	void OnCollisionEnter(CCollider* pOther);
	void OnCollisionExit(CCollider* pOther);

};

