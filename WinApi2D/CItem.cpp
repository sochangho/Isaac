#include "framework.h"
#include "CItem.h"

CItem::CItem()
{
	objOwn = nullptr;
}

CItem::~CItem()
{
	if (objOwn != nullptr) {
		objOwn = nullptr;
	}
}

void CItem::SetOwnObj(CGameObject* obj)
{
	objOwn = obj;
}

CGameObject* CItem::GetOwnObj()
{
	return objOwn;
}
