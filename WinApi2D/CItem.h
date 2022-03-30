#pragma once
#include "CGameObject.h"
class CItem
{
public:

	CGameObject* objOwn;

public:
	CItem();
	~CItem();


	virtual void ItemUse(fVec2 dir) {}
	virtual CItem* Create() { return new CItem(); }
	void SetOwnObj(CGameObject* obj);
	CGameObject* GetOwnObj();
};

