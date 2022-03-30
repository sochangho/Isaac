#pragma once
#include "CIsaacPlayer2.h"
#include "CD2DImage.h"
class CRedBaby : public CIsaacPlayer2
{

private:
	CD2DImage* m_pImg;
	Player2State cur_state = Player2State::IDLE;
public:

	CRedBaby();
	~CRedBaby();

	virtual CRedBaby* Clone();
	virtual CRedBaby* Create();
	virtual void update();
	virtual void render();
	
	virtual void ItemUse(fVec2 dir);
	void ChangeAnimation(CIsaacPlayer2::Player2State state);
};

