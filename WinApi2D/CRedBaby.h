#pragma once
#include "CIsaacPlayer2.h"
#include "CD2DImage.h"
class CRedBaby : public CIsaacPet
{

private:
	CD2DImage* m_pImg;
	PetState cur_state = PetState::IDLE;
public:

	CRedBaby();
	~CRedBaby();

	virtual CRedBaby* Clone();
	virtual CRedBaby* Create();
	virtual void update();
	virtual void render();
	
	virtual void ItemUse(fVec2 dir);
	void ChangeAnimation(CIsaacPet::PetState state);
};

