#include "framework.h"
#include "CBossRoom.h"
#include "CBackGround.h"
#include "CMap.h"
#include "CIsaacPlayer.h"
#include "CCharacter.h"
#include "CIsaacPlayer2.h"
#include "CDropRedBayby.h"
#include "CDoor.h"
#include "Monstro.h"
#include "CBossHealthBar.h"
#include "CBoosDoor.h"
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

	CDoor* down = new CBoosDoor;
	down->SetPos(fPoint(DOORDOWN_X, DOORDOWN_Y));
	down->Load(DOOR_DIR::DOWN, GROUP_SCENE::NOMALROOM2);
	AddObject(down, GROUP_GAMEOBJ::DOOR);


	Monstro* monstro = new Monstro;
    monstro->SetPos(fPoint(MAPCENTER_X, MAPCENTER_Y));
    AddObject(monstro, GROUP_GAMEOBJ::MONSTER);

	CBossHealthBar* bossHealthBar = new CBossHealthBar;
	AddObject(bossHealthBar, GROUP_GAMEOBJ::UI);
	bossHealthBar->SetPos(fPoint(WINSIZEX/2-200, WINSIZEY/2 - 300));
	bossHealthBar->SetScale(fPoint(400.f, 100.f));
	bossHealthBar->SetMonster(monstro);


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
