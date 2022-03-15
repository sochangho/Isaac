#pragma once
#include "CCharacter.h"
class CIsaacPlayer : public CCharacter
{private:

	fVec2 m_dirVec2;
	float m_veclocity;
	bool  m_isMove;
	bool  m_isAttack;
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
	void CreateWaterballoon(fVec2 dir );
	void CreateBomb();
	
};

