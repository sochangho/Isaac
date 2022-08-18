#pragma once
#include "framework.h"
#include "CGameObject.h"
#include "CD2DImage.h"
#include "CCollider.h"
#include "CDoor.h"

class CBoosDoor : public CDoor
{
public:

	CBoosDoor();
	~CBoosDoor();

	virtual void LoadDoor(DOOR_DIR doorDir, GROUP_SCENE scene);

};

