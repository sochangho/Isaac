#include "framework.h"
#include "CItemRoom2.h"
#include "CBackGround.h"
#include "CMap.h"
#include "CIsaacPlayer.h"
#include "CCharacter.h"
#include "CIsaacPlayer2.h"
#include "CDropRedBayby.h"
#include "CDoor.h"
#include "CDropLilloki.h"
CItemRoom2::CItemRoom2()
{
}

CItemRoom2::~CItemRoom2()
{
}

void CItemRoom2::update()
{
	CScene::update();
}

void CItemRoom2::init()
{
	wstring path = CPathManager::getInst()->GetContentPath();
	path += L"tile\\ItemRoom0";
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
	map->Load(L"Map_Item", L"texture\\map\\Blue.png");
	AddObject(map, GROUP_GAMEOBJ::MAP);

	CDoor* doorRight = new CDoor;
	doorRight->SetPos(fPoint(DOORRIGHT_X, DOORRIGHT_Y));
	doorRight->Load(DOOR_DIR::RIGHT, GROUP_SCENE::STARTROOM);
	AddObject(doorRight, GROUP_GAMEOBJ::DOOR);

	CDropLilloki* lilloki = new CDropLilloki();
	lilloki->SetPos(fPoint(MAPCENTER_X, MAPCENTER_Y));
	AddObject(lilloki, GROUP_GAMEOBJ::DROPITEM);



}

void CItemRoom2::Enter()
{
	CIsaacPlayer* player = CGameManager::getInst()->LoadPlayer();

	GroupCheckSetting();
	CCameraManager::getInst()->SetLookAt(fPoint(MAPCENTER_X, MAPCENTER_Y));
}

void CItemRoom2::Exit()
{
	CGameManager::getInst()->SavePlayer();
	PlayerDelete();

	CCollisionManager::getInst()->Reset();
}
