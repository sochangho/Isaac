#pragma once
#include "CCharacter.h"
class CGaperHead : public CCharacter
{
public:
	
	CGaperHead();
	~CGaperHead();

	virtual CGaperHead* Clone();


	virtual void update();
	virtual void render();
	


};

