#pragma once
#include "CD2DImage.h"
#include "CCharacter.h"
class CPlayerBody : public CCharacter
{private:
	CD2DImage* m_pImg;
public:
	CPlayerBody();
	~CPlayerBody();

	virtual CPlayerBody* Clone();
	virtual void update();
	virtual void render();
	virtual void finalupdate();
	



};

