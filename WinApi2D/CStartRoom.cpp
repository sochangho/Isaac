#include "framework.h"
#include "CStartRoom.h"

#include "CGameObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CMap.h"
#include "CBackGround.h"

#include "CSound.h"
#include "CD2DImage.h"


#include "CIsaacPlayer.h"
#include "CTestObject.h"
#include "CCollider.h"
#include "CCenterObject.h"
#include "CTile.h"
#include "CTileNavMap.h"
#include "CMonster.h"
#include "CGaper.h"
#include "CDropRedBayby.h"
CStartRoom::CStartRoom()
{
}

CStartRoom::~CStartRoom()
{
	
}

void CStartRoom::update()
{
	CScene::update();
	if (KeyDown(VK_TAB))
	{
		ChangeScn(GROUP_SCENE::TOOL);
	}





	
}

void CStartRoom::Enter()
{
	wstring path = CPathManager::getInst()->GetContentPath();
	path += L"tile\\stageRoom01.tile";
	LoadTile(path);

	
	
	CBackGround* backGround = new CBackGround;
	backGround->Load(L"BackGround", L"texture\\map\\bgblack.png");
	//backGround->SetPos(fPoint(-100.f, -500.f));
	 fPoint scale = backGround->GetScale();
	 scale.x *= 10;
	 scale.y *= 10;
	backGround->SetScale(scale);
	backGround->SetPos(fPoint(-100.f, 0 ));
	AddObject(backGround, GROUP_GAMEOBJ::BACKGROUND);



	CMap* map = new CMap;
	map->Load(L"Map_Start", L"texture\\map\\basement.png");
	AddObject(map, GROUP_GAMEOBJ::MAP);


	CMap* map1 = new CMap;
	map1->Load(L"Map_Control", L"texture\\map\\controls.png");
	map1->SetPos(fPoint(map->GetScale().x / 6, map->GetScale().y / 3));
	AddObject(map1, GROUP_GAMEOBJ::MAP);

	CIsaacPlayer* player = new CIsaacPlayer;
	player->SetPos(fPoint(map->GetScale().x / 2, map->GetScale().y / 2));
	AddObject(player, GROUP_GAMEOBJ::PLAYER);

	CCenterObject* center = new CCenterObject;
	center->SetPos(player->GetPos());
	AddObject(center, GROUP_GAMEOBJ::UI);

	CGaper* monster = new CGaper;
	monster->SetPos(fPoint(map->GetScale().x / 2 + 100, map->GetScale().y / 2 + 100));
	monster->SetScale(fPoint(50, 50));
	monster->SetDestinaionObj(player);
	AddObject(monster, GROUP_GAMEOBJ::MONSTER);

	CGaper* monster1 = new CGaper;
	monster1->SetPos(fPoint(map->GetScale().x / 2 + 50, map->GetScale().y / 2 + 50));
	monster1->SetScale(fPoint(50, 50));
	monster1->SetDestinaionObj(player);
	AddObject(monster1, GROUP_GAMEOBJ::MONSTER);
	
	CDropRedBayby* redbaby = new CDropRedBayby;
	redbaby->SetPos(fPoint(map->GetScale().x / 2 + 50, map->GetScale().y / 2 + 50));
	AddObject(redbaby, GROUP_GAMEOBJ::DROPITEM);

	GroupCheckSetting();
	CCameraManager::getInst()->SetLookAt(fPoint(WINSIZEX / 2, WINSIZEY / 2));
	CCameraManager::getInst()->SetTargetObj(center);
	
	
}

void CStartRoom::Exit()
{
	DeleteAll();

	CCollisionManager::getInst()->Reset();
}

