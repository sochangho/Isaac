#pragma once
#include "CCharacter.h"
class CIsaacPlayer : public CCharacter
{private:

	fVec2 m_dirVec2;
	
	float m_veclocity;
	float m_bodyDelay = 0.f;
	float m_attackTime = 0.f;

	bool  m_isMove;
	bool  m_isAttack = false;
	bool  m_isAttackKey = false;
	
	


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

	void CreateWaterballoon(fVec2 dir );
	void CreateBomb();
	

     

	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);
};

