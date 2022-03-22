#pragma once
#include "CCharacter.h"
#include "CPlayerBody.h"
#include "CPlayerHead.h"

class CIsaacPlayer : public CCharacter
{
	friend class CPlayerBody;
	friend class CPlayerHead;

private:

	CD2DImage* m_pImg;

	fVec2 m_dirVec2;
	
	float m_veclocity;
	float m_bodyDelay = 0.f;
	float m_attackTime = 0.f;

	float m_ColDuration = 0.3f;
	float m_ColTime = 0.f;

	float m_AttackedDuration = 0.3f;
	float m_attacedTime = 0.f;

	float m_invincibilityD = 2.f;
	float m_invincibilityT = 0.f;

	bool  m_isColCheck = false;
	bool  m_isMove;
	bool  m_isAttack = false;
	bool  m_isAttackKey = false;
	bool  m_isAttacked =  false;
	bool  m_isInvincibility = false;

	enum class IsaacStateHead {
		IDLE,
		LEFT_MOVE,
		RIGHT_MOVE,
		UP_MOVE,
		DOWN_MOVE,

		LEFT_ATTACK,
		RIGHT_ATTACK,
		UP_ATTACK,
		DOWN_ATTACK,

	};

	enum class IsaacStateBody {
		IDLE,
		LEFT_MOVE , 
		RIGHT_MOVE,
		UP_MOVE,
		DOWN_MOVE,


	};

	IsaacStateHead m_stHead;
	IsaacStateBody m_stBody;

public:
	CIsaacPlayer();
	~CIsaacPlayer();

	virtual CIsaacPlayer* Clone();
	
	virtual void update();
	virtual void render();
	virtual void finalupdate();

	void HeadState(IsaacStateHead head);
	void BodyState(IsaacStateBody body);

	void Attack();

	void Move();
	void OppositeMove();
	void AttackedMove();
	void Invincibility();


	void CreateWaterballoon(fVec2 dir );
	void CreateBomb();
	
	float GetVelocity();
     

	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);
};

