#pragma once
#include "CMonster.h"
#include "CIsaacPlayer.h"

class Monstro : public CMonster
{private: 
	CD2DImage* m_pImg;
	CGameObject* m_playerObj;
	enum class MonstroAnimatonState {
		NONE_LEFT,
		NONE_RIGHT,
		LEFE_MOVE,
		LEFT_JUMP,

		RIGHT_MOVE,
	    RIGHT_JUMP,

		ATTACK1_LEFT,
		ATTACK2_LEFT,
		ATTACK3_LEFT,


		ATTACK1_RIGHT,
		ATTACK2_RIGHT,
		ATTACK3_RIGHT,

		TEARS_LEFT,
		TEARS_RIGHT

	 };

	enum class MonstroState {
		NONE,
		TRACE,
		ATTACK,
		TREAS_ATTACk,
	};


	 MonstroAnimatonState anistate = MonstroAnimatonState::NONE_LEFT;
	 MonstroState monstroState = MonstroState::NONE;


	 float m_anicur = 0;
	 float m_animduration;

	 bool is_tearsAttack = false;
	 bool is_animationStop = false;

	 fPoint m_dir;
	 fPoint m_playerPos;

	 void ChangeAnimation(MonstroAnimatonState state, float duration);
	 void UpdateAniState();
	 void MonstroMove();
	 void Attack();
	 void TearsAttack();
	 void CreateRandomTearsAttack(fPoint dir);

public:

	Monstro();
	~Monstro();

 virtual Monstro* Clone();
 virtual void update();
 virtual void render();
 virtual void finalupdate();

 
};
