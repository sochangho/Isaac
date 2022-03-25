#pragma once
#include "CGameObject.h"
class CItem
{
public:

	CGameObject* objOwn;

public:
	CItem();
	~CItem();


	virtual void ItemUse(fVec2 dir) = 0;
	virtual CItem* Create() = 0;
	void SetOwnObj(CGameObject* obj);
	CGameObject* GetOwnObj();
};

