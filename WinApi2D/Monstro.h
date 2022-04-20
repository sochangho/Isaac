#pragma once
#include "CMonster.h"
class Monstro : public CMonster
{private: 
	CD2DImage* m_pImg;

public:

	Monstro();
	~Monstro();

 virtual Monstro* Clone();
 virtual void update();
 virtual void render();
 virtual void finalupdate();
};
