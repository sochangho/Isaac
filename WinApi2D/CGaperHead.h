#pragma once
#include "CCharacter.h"
class CGaperHead : public CCharacter
{
private:
	CD2DImage* m_pImg;
public:
	
	CGaperHead();
	~CGaperHead();

	virtual CGaperHead* Clone();


	virtual void update();
	virtual void render();
	virtual void finalupdate();


};

