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
#include "CDoor.h"
#include "Monstro.h"
#include "CBossHealthBar.h"
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

	

	CIsaacPlayer* player;
	if (!CGameManager::getInst()->GetSaveCheck()) {
		player = new CIsaacPlayer;
		player->SetPos(fPoint(MAPCENTER_X, MAPCENTER_Y));
		AddObject(player, GROUP_GAMEOBJ::PLAYER);
	}
	else {

	 player = CGameManager::getInst()->LoadPlayer();

	}
	
	


	GroupCheckSetting();
	CCameraManager::getInst()->SetLookAt(fPoint(MAPCENTER_X , MAPCENTER_Y));
;
	
	
}

void CStartRoom::init()
{

	CGameManager::getInst()->init();

	wstring path = CPathManager::getInst()->GetContentPath();
	path += L"tile\\stageRoom01.tile";
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
	map->Load(L"Map_Start", L"texture\\map\\basement.png");
	AddObject(map, GROUP_GAMEOBJ::MAP);


	CMap* map1 = new CMap;
	map1->Load(L"Map_Control", L"texture\\map\\controls.png");
	map1->SetPos(fPoint(map->GetScale().x / 6, map->GetScale().y / 3));
	AddObject(map1, GROUP_GAMEOBJ::MAP);



	CDoor* doorright = new CDoor;
	doorright->SetPos(fPoint(DOORRIGHT_X, DOORRIGHT_Y));
	doorright->Load(DOOR_DIR::RIGHT, GROUP_SCENE::ITEMROOM);
	AddObject(doorright, GROUP_GAMEOBJ::DOOR);


	CDoor* doorleft = new CDoor;
	doorleft->SetPos(fPoint(DOORLEFT_X, DOORLFET_Y));
	doorleft->Load(DOOR_DIR::LEFT, GROUP_SCENE::ITEMROOM1);
	AddObject(doorleft, GROUP_GAMEOBJ::DOOR);



	CDoor* doorup = new CDoor;
	doorup->SetPos(fPoint(DOORUP_X, DOORUP_Y));
	doorup->Load(DOOR_DIR::UP, GROUP_SCENE::NOMALROOM1);
	AddObject(doorup, GROUP_GAMEOBJ::DOOR);
	//CSoundManager::getInst()->Play(L"basement");


	/*Monstro* monstro = new Monstro;
	monstro->SetPos(fPoint(MAPCENTER_X, MAPCENTER_Y));
	AddObject(monstro, GROUP_GAMEOBJ::MONSTER);

	CBossHealthBar* bossHealthBar = new CBossHealthBar;
	AddObject(bossHealthBar, GROUP_GAMEOBJ::UI);
	bossHealthBar->SetPos(fPoint(WINSIZEX/2-200, WINSIZEY/2 - 300));
	bossHealthBar->SetScale(fPoint(400.f, 100.f));
	bossHealthBar->SetMonster(monstro);*/

}
void CStartRoom::Exit()
{
	CGameManager::getInst()->SavePlayer();

	PlayerDelete();
    
	CCollisionManager::getInst()->Reset();
}

