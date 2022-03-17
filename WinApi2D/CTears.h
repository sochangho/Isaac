#pragma once
#include "CGameObject.h"
#include "CD2DImage.h"
#include "CCollider.h"
class CTears : public CGameObject
{
private:
	fVec2 m_fvDir;
	float m_velocity = 400.f;
	float m_lifeTime = 0.f;
	CD2DImage* m_pImg;

public:
	CTears();
	~CTears();
	virtual CTears* Clone();

	virtual void update();
	virtual void render();

	
	void OnCollisionEnter(CCollider* pOther);
	void SetDir(fVec2 fv2);
};

