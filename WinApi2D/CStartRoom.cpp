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


	if (m_curTime < m_duration) {

		m_curTime +=fDT;
	}
	else {
		GettileNav()->CTileNavAstarUpdate();
		m_curTime = 0.f;
		
	}


	
}

void CStartRoom::Enter()
{
	wstring path = CPathManager::getInst()->GetContentPath();
	path += L"tile\\stageRoom01.tile";
	LoadTile(path);

	SetTileNav(new CTileNavMap);

	
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

	CMonster* monster = new CMonster;
	monster->SetPos(fPoint(map->GetScale().x / 2 + 100, map->GetScale().y / 2 + 100));
	monster->SetScale(fPoint(50, 50));
	AddObject(monster, GROUP_GAMEOBJ::MONSTER);

	GroupCheckSetting();
	CCameraManager::getInst()->SetLookAt(fPoint(WINSIZEX / 2, WINSIZEY / 2));
	CCameraManager::getInst()->SetTargetObj(center);
	
	GettileNav()->SetDestinaion(player);
	GettileNav()->SetStartingPoint(monster);
	GettileNav()->CTileNavAstarUpdate();
}

void CStartRoom::Exit()
{
	DeleteAll();

	CCollisionManager::getInst()->Reset();
}

