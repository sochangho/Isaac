#include "framework.h"
#include "CNomalRoom2.h"
#include "CBackGround.h"
#include "CMap.h"
#include "CIsaacPlayer.h"
#include "CCharacter.h"
#include "CIsaacPlayer2.h"
#include "CDropRedBayby.h"
#include "CGaperBodyMonster.h"
#include "CDoor.h"


CNomalRoom2::CNomalRoom2()
{
}

CNomalRoom2::~CNomalRoom2()
{
}

void CNomalRoom2::update()
{
	CScene::update();
}

void CNomalRoom2::init()
{
	wstring path = CPathManager::getInst()->GetContentPath();
	path += L"tile\\ROOM2";
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
	map->Load(L"NomalRoom1", L"texture\\map\\basement.png");
	AddObject(map, GROUP_GAMEOBJ::MAP);

	CDoor* doorDown = new CDoor;
	doorDown->SetPos(fPoint(DOORDOWN_X, DOORDOWN_Y));
	doorDown->Load(DOOR_DIR::DOWN, GROUP_SCENE::NOMALROOM1);
	AddObject(doorDown, GROUP_GAMEOBJ::DOOR);



	vector<CMonster*> monsters;


	for (int i = 0; i < 10; i++) {


		monsters.push_back(new CGaperBodyMonster);

	}
	for (int i = 0; i < monsters.size(); i++) {

		AddObject(monsters[i], GROUP_GAMEOBJ::MONSTER);

	}

}

void CNomalRoom2::Enter()
{
	CIsaacPlayer* player = CGameManager::getInst()->LoadPlayer();

	GroupCheckSetting();
	CCameraManager::getInst()->SetLookAt(fPoint(MAPCENTER_X, MAPCENTER_Y));
}

void CNomalRoom2::Exit()
{
	CGameManager::getInst()->SavePlayer();
	PlayerDelete();

	CCollisionManager::getInst()->Reset();
}
