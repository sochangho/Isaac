#include "framework.h"
#include "CItemRoom1.h"
#include "CBackGround.h"
#include "CMap.h"
#include "CIsaacPlayer.h"
#include "CCharacter.h"
#include "CIsaacPlayer2.h"
#include "CDropRedBayby.h"
#include "CDoor.h"
CItemRoom1::CItemRoom1()
{
}

CItemRoom1::~CItemRoom1()
{
}

void CItemRoom1::update()
{
	CScene::update();
}

void CItemRoom1::init()
{
	// ¾À ¸Ê ¼³Á¤--------------------------------------------
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



	//

	CDropRedBayby* item = new CDropRedBayby;
	CDropRedBayby* item1 = new CDropRedBayby;
	item->SetPos(fPoint(map->GetScale().x / 2, map->GetScale().y / 2));
	AddObject(item, GROUP_GAMEOBJ::DROPITEM);


	item1->SetPos(fPoint(map->GetScale().x / 2 - 200, map->GetScale().y / 2));
	AddObject(item1, GROUP_GAMEOBJ::DROPITEM);

	CDoor* doorleft = new CDoor;
	doorleft->SetPos(fPoint(DOORLEFT_X, DOORLFET_Y));
	doorleft->Load(DOOR_DIR::LEFT, GROUP_SCENE::STARTROOM);
	AddObject(doorleft, GROUP_GAMEOBJ::DOOR);
}

void CItemRoom1::Enter()
{
	
	
	CIsaacPlayer* player = CGameManager::getInst()->LoadPlayer();

	GroupCheckSetting();
	CCameraManager::getInst()->SetLookAt(fPoint(MAPCENTER_X , MAPCENTER_Y));
	
}

void CItemRoom1::Exit()
{
	CGameManager::getInst()->SavePlayer();
	PlayerDelete();

	CCollisionManager::getInst()->Reset();
}
