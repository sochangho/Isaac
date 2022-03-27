#pragma once
#include "CGameObject.h"
#include "CD2DImage.h"
#include "CCollider.h"
#include "CEffect.h"


class CDefaultTears : public CGameObject
{

private:


	fVec2 m_fvDir;
	float m_velocity = 400.f;
	float m_lifeTime = 0.f;

	CD2DImage* m_pImg;
	CEffect* m_effect;
public:

	enum class AttackType {

		PLAYER, MONSATER

	};

	AttackType type = AttackType::MONSATER;


	float m_dmg = 10.f;

	CDefaultTears();
	~CDefaultTears();
	virtual CDefaultTears* Clone();

	virtual void update();
	virtual void render();


	void OnCollisionEnter(CCollider* pOther);
	void SetDir(fVec2 fv2);
	void SetImg(CD2DImage* img);
	void SetEffect(CEffect* effect);


	CD2DImage* GetImg();
	CEffect* GetEffect();

};

