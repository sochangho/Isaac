#include "framework.h"
#include "CNomalRoom1.h"
#include "CBackGround.h"
#include "CMap.h"
#include "CIsaacPlayer.h"
#include "CCharacter.h"
#include "CIsaacPlayer2.h"
#include "CDropRedBayby.h"
#include "CDoor.h"
#include "CGaper.h"
CNomalRoom1::CNomalRoom1()
{
}

CNomalRoom1::~CNomalRoom1()
{
}

void CNomalRoom1::update()
{
	CScene::update();
}

void CNomalRoom1::init()
{
	wstring path = CPathManager::getInst()->GetContentPath();
	path += L"tile\\NomalRoom1";
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
	doorDown->Load(DOOR_DIR::DOWN, GROUP_SCENE::STARTROOM);
	AddObject(doorDown, GROUP_GAMEOBJ::DOOR);

	vector<CGameObject*>& players = GetPlayer();

	CIsaacPlayer* isaacplayer = nullptr;
	for (int i = 0; i < players.size(); i++) {

		CIsaacPlayer* player = dynamic_cast<CIsaacPlayer*>(players[i]);
		if (player != nullptr) {

			isaacplayer = player;
		
			break;
		}
	}

	if (isaacplayer != nullptr) {
		CGaper* gaper1 = new CGaper;
		gaper1->SetPos(fPoint(MAPCENTER_X, MAPCENTER_Y));
		gaper1->SetScale(fPoint(50, 50));
		AddObject(gaper1, GROUP_GAMEOBJ::MONSTER);
		gaper1->SetDestinaionObj(isaacplayer);



		CGaper* gaper2 = new CGaper;
		gaper2->SetPos(fPoint(MAPCENTER_X - 100, MAPCENTER_Y));
		gaper2->SetScale(fPoint(50, 50));
		AddObject(gaper2, GROUP_GAMEOBJ::MONSTER);
		gaper2->SetDestinaionObj(isaacplayer);


		CGaper* gaper3 = new CGaper;
		gaper3->SetPos(fPoint(MAPCENTER_X - 150, MAPCENTER_Y));
		gaper3->SetScale(fPoint(50, 50));
		AddObject(gaper3, GROUP_GAMEOBJ::MONSTER);
		gaper3->SetDestinaionObj(isaacplayer);
		
	}
}

void CNomalRoom1::Enter()
{
	CIsaacPlayer* player = CGameManager::getInst()->LoadPlayer();

	GroupCheckSetting();
	CCameraManager::getInst()->SetLookAt(fPoint(MAPCENTER_X, MAPCENTER_Y));
}

void CNomalRoom1::Exit()
{
	CGameManager::getInst()->SavePlayer();
	PlayerDelete();

	CCollisionManager::getInst()->Reset();
}
