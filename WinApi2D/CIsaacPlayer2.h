#pragma once
#include "CCharacter.h"

class CIsaacPlayer2 : public CCharacter
{
	
public:

	enum class Player2State {
		IDLE,
		UP,
		DOWN,
		LEFT,
		RIGHT
	};




	CIsaacPlayer2();
	~CIsaacPlayer2();
	
	virtual CIsaacPlayer2* Clone();
	virtual CIsaacPlayer2* Create();
	virtual void update();
	virtual void render();
	virtual void ItemUse(fVec2 dir){};


	Player2State GetPlayer2State();

private:
	Player2State state;
	Player2State cur_state = Player2State::IDLE;
	float m_velocity;
	float m_distance;
	fPoint m_destination;
};

