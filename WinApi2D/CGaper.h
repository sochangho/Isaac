#pragma once
#include "CMonster.h"
class CGaper : public CMonster
{
private:

	enum class GaperState {

		IDLE,
		LEFT,
		RIGHT,
		UP,
		DOWN,

	};

	GaperState m_state;




public:

	CGaper();
	~CGaper();
	virtual CGaper* Clone();
	virtual void update();
	virtual void render();
	virtual void finalupdate();



	void StateChange(GaperState state);

};

