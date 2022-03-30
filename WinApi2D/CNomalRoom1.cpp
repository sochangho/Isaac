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
#include "CRock.h"
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
	path += L"tile\\ROOM1";
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

	CDoor* doorup = new CDoor;
	doorup->SetPos(fPoint(DOORUP_X, DOORUP_Y));
	doorup->Load(DOOR_DIR::UP, GROUP_SCENE::NOMALROOM2);
	AddObject(doorup, GROUP_GAMEOBJ::DOOR);

	CSoundManager::getInst()->Play(L"basement");



	/*CRock* rock = new CRock;
	rock->SetPos(fPoint(MAPCENTER_X, MAPCENTER_Y));
	AddObject(rock, GROUP_GAMEOBJ::ROCK);

	CRock* rock1 = new CRock;
	rock1->SetPos(fPoint(MAPCENTER_X + 40, MAPCENTER_Y));
	AddObject(rock1, GROUP_GAMEOBJ::ROCK);
	CRock* rock2 = new CRock;
	rock2->SetPos(fPoint(MAPCENTER_X - 45, MAPCENTER_Y));
	AddObject(rock2, GROUP_GAMEOBJ::ROCK);

	CRock* rock3 = new CRock;
	rock3->SetPos(fPoint(MAPCENTER_X - 45, MAPCENTER_Y - 40));
	AddObject(rock3, GROUP_GAMEOBJ::ROCK);
	
	CRock* rock5 = new CRock;
	rock5->SetPos(fPoint(MAPCENTER_X - 90, MAPCENTER_Y - 100));
	AddObject(rock5, GROUP_GAMEOBJ::ROCK);

	CRock* rock6 = new CRock;
	rock6->SetPos(fPoint(MAPCENTER_X - 50, MAPCENTER_Y - 100));
	AddObject(rock6, GROUP_GAMEOBJ::ROCK);

	CRock* rock7 = new CRock;
	rock7->SetPos(fPoint(MAPCENTER_X , MAPCENTER_Y - 100));
	AddObject(rock7, GROUP_GAMEOBJ::ROCK);

	
	CRock* rock8 = new CRock;
	rock8->SetPos(fPoint(MAPCENTER_X + 40, MAPCENTER_Y - 100));
	AddObject(rock8, GROUP_GAMEOBJ::ROCK);

	CRock* rock9 = new CRock;
	rock9->SetPos(fPoint(MAPCENTER_X + 40, MAPCENTER_Y - 70));
	AddObject(rock9, GROUP_GAMEOBJ::ROCK);

	CRock* rock10 = new CRock;
	rock10->SetPos(fPoint(MAPCENTER_X + 40, MAPCENTER_Y - 40));
	AddObject(rock10, GROUP_GAMEOBJ::ROCK);


	CRock* rock4 = new CRock;
	rock4->SetPos(fPoint(MAPCENTER_X - 90, MAPCENTER_Y - 70));
	AddObject(rock4, GROUP_GAMEOBJ::ROCK);*/




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

		
		const vector<CGameObject*>& tiles = GetGroupObject(GROUP_GAMEOBJ::TILE);

		for (int i = 0; i < tiles.size(); i++) {
			CTile* tile = dynamic_cast<CTile*>(tiles[i]);

			if (tile != nullptr && tile->GetGroup() == GROUP_TILE::MOSTERSPAWN) {

				CGaper* gaper = new CGaper;
				gaper->SetScale(fPoint(50, 50));
				gaper->SetPos(tile->GetPos());
		        AddObject(gaper, GROUP_GAMEOBJ::MONSTER);				
		        gaper->SetDestinaionObj(isaacplayer);


			}

		}

		
	}
	else {
		assert(nullptr);
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
