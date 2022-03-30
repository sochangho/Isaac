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
	path += L"tile\\ROOM22";
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
	map->Load(L"NomalRoom1", L"texture\\map\\basement2.png");
	AddObject(map, GROUP_GAMEOBJ::MAP);

	CDoor* doorDown = new CDoor;
	doorDown->SetPos(fPoint(DOORDOWN_X, DOORDOWN_Y));
	doorDown->Load(DOOR_DIR::DOWN, GROUP_SCENE::NOMALROOM1);
	AddObject(doorDown, GROUP_GAMEOBJ::DOOR);



	const vector<CGameObject*>& tiles = GetGroupObject(GROUP_GAMEOBJ::TILE);

	for (int i = 0; i < tiles.size(); i++) {
		CTile* tile = dynamic_cast<CTile*>(tiles[i]);

		if (tile != nullptr && tile->GetGroup() == GROUP_TILE::MOSTERSPAWN) {

			CGaperBodyMonster* gaperBody = new CGaperBodyMonster;
			gaperBody->SetScale(fPoint(50, 50));
			gaperBody->SetPos(tile->GetPos());
			AddObject(gaperBody, GROUP_GAMEOBJ::MONSTER);			
		}

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
