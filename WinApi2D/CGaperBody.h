#pragma once
#include "CCharacter.h"
class CGaperBody : public CCharacter
{
private:
	CD2DImage* m_pImg;
public:
	CGaperBody();
	~CGaperBody();

	virtual CGaperBody* Clone();
	virtual void update();
	virtual void render();
	virtual void finalupdate();

};

