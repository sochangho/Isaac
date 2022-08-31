#pragma once
#include "CCharacter.h"

class CIsaacPet : public CCharacter
{
	
public:

	enum class PetState {
		IDLE,
		UP,
		DOWN,
		LEFT,
		RIGHT
	};




	CIsaacPet();
	~CIsaacPet();
	
	virtual CIsaacPet* Clone();
	virtual CIsaacPet* Create();
	virtual void update();
	virtual void render();
	virtual void ItemUse(fVec2 dir){};


	PetState GetPlayer2State();

private:
	PetState state;
	PetState cur_state = PetState::IDLE;
	float m_velocity;
	float m_distance;
	fPoint m_destination;
};

