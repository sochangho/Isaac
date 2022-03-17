#pragma once
#include "CGameObject.h"
class CTestObject : public CGameObject
{
public:

	CTestObject();
	~CTestObject();
   
	virtual CTestObject* Clone();
	virtual void update();
	virtual void render();
	

};

