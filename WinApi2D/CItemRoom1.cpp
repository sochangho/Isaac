#include "framework.h"
#include "CItemRoom1.h"
#include "CBackGround.h"
#include "CMap.h"
#include "CCenterObject.h"
CItemRoom1::CItemRoom1()
{
}

CItemRoom1::~CItemRoom1()
{
}

void CItemRoom1::update()
{
}

void CItemRoom1::Enter()
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
	backGround->SetPos(fPoint(-100.f, 0));
	AddObject(backGround, GROUP_GAMEOBJ::BACKGROUND);

	CMap* map = new CMap;
	map->Load(L"Map_Start", L"texture\\map\\basement.png");
	AddObject(map, GROUP_GAMEOBJ::MAP);


	CCenterObject* center = new CCenterObject;
	center->SetPos(fPoint(map->GetScale().x / 2, map->GetScale().y / 2));
	AddObject(center, GROUP_GAMEOBJ::UI);


	GroupCheckSetting();

}

void CItemRoom1::Exit()
{
	DeleteAll();

	CCollisionManager::getInst()->Reset();
}
