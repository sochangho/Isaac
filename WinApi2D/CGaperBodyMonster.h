#pragma once
#include "CMonster.h"
#include "CD2DImage.h"
class CGaperBodyMonster : public CMonster
{

private:
	enum class GaperBodyState {

		IDLE,
		LEFT,
		RIGHT,
		UP,
		DOWN,

	};

	CD2DImage* m_pImg;
	GaperBodyState m_state;

	float m_attackduration = 3.f; // ·£´ýÀ¸·Î 
	float m_attackTime = 0.f;

public:
	CGaperBodyMonster();
	~CGaperBodyMonster();

	virtual CGaperBodyMonster* Clone();
	virtual void update();
	virtual void render();
	virtual void finalupdate();


	void stateChange(GaperBodyState state);
	void ChangeAni(bool change);
	virtual void OnCollisionEnter(CCollider* _pOther);
};

