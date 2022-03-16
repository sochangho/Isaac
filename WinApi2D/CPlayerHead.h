#pragma once
#include "CD2DImage.h"
#include "CCharacter.h"
class CPlayerHead : public CCharacter
{
private:
	CD2DImage* m_pImg;
public:
	CPlayerHead();
	~CPlayerHead();

	virtual CPlayerHead* Clone();
	virtual void update();
	virtual void render();
	virtual void finalupdate();


};

