#include "framework.h"
#include "CBossRoom.h"
#include "CBackGround.h"
#include "CMap.h"
#include "CIsaacPlayer.h"
#include "CCharacter.h"
#include "CIsaacPlayer2.h"
#include "CDropRedBayby.h"
#include "CDoor.h"

CBossRoom::CBossRoom()
{
}

CBossRoom::~CBossRoom()
{
}

void CBossRoom::update()
{
	CScene::update();
}

void CBossRoom::init()
{
	wstring path = CPathManager::getInst()->GetContentPath();
	path += L"tile\\BossRoom";
	LoadTile(path);

	CBackGround* backGround = new CBackGround;
	backGround->Load(L"BackGround", L"texture\\map\\bgblack.png");

	fPoint scale = backGround->GetScale();
	scale.x *= 10;
	scale.y *= 10;
	backGround->SetScale(scale);
	backGround->SetPos(fPoint(-100.f, 0));
	AddObject(backGround, GROUP_GAMEOBJ::BACKGROUND);

	CMap* map = new CMap;
	map->Load(L"Bossroom", L"texture\\map\\bossRoom.png");
	AddObject(map, GROUP_GAMEOBJ::MAP);

	CDoor* doorleft = new CDoor;
	doorleft->SetPos(fPoint(DOORLEFT_X, DOORLFET_Y));
	doorleft->Load(DOOR_DIR::LEFT, GROUP_SCENE::NOMALROOM2);
	AddObject(doorleft, GROUP_GAMEOBJ::DOOR);

}

void CBossRoom::Enter()
{
	CIsaacPlayer* player = CGameManager::getInst()->LoadPlayer();

	GroupCheckSetting();
	CCameraManager::getInst()->SetLookAt(fPoint(MAPCENTER_X, MAPCENTER_Y));
}

void CBossRoom::Exit()
{
	CGameManager::getInst()->SavePlayer();
	PlayerDelete();

	CCollisionManager::getInst()->Reset();
}
