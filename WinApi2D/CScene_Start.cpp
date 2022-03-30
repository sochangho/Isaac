#include "framework.h"
#include "CScene_Start.h"

#include "CGameObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CMap.h"
#include "CBackGround.h"

#include "CSound.h"
#include "CD2DImage.h"


#include "CIsaacPlayer.h"
#include "CTestObject.h"
#include "CTitle.h"
#include "CTitle1.h"
#include "CTitle2.h"
#include "CTitle3.h"
#include "CTitle4.h"
CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::update()
{
	CScene::update();

	if (KeyDown(VK_TAB))
	{
		ChangeScn(GROUP_SCENE::TOOL);
	}
	if (KeyDown(VK_SPACE))
	{
		ChangeScn(GROUP_SCENE::STARTROOM);
	}
	if (KeyDown('A')) {

		ChangeScn(GROUP_SCENE::ITEMROOM);
	}
	/*if (KeyDown('Z'))
	{
		CSoundManager::getInst()->AddSound(L"bgm", L"sound\\drumloop.wav", true);
		CSoundManager::getInst()->Play(L"bgm");
	}

	if (KeyDown('X'))
	{
		CSoundManager::getInst()->Stop(L"bgm");
	}*/
}

void CScene_Start::Enter()
{
	
	CTitle* title = new CTitle;
	title->SetPos(fPoint(WINSIZEX / 2, WINSIZEY / 2));
	title->SetScale(fPoint(WINSIZEX / 2, WINSIZEY / 2));
	AddObject(title, GROUP_GAMEOBJ::UI);

	CTitle1* title1 = new CTitle1;
	title1->SetPos(fPoint(WINSIZEX / 2, 180));
	title1->SetScale(fPoint(260,  100 ));
	AddObject(title1, GROUP_GAMEOBJ::UI);

	CTitle2* title2 = new CTitle2;
	title2->SetPos(fPoint(WINSIZEX / 2, WINSIZEY / 2 + 100));
	title2->SetScale(fPoint(320, 300));
	AddObject(title2, GROUP_GAMEOBJ::UI);
	CTitle3* title3 = new CTitle3;
	title3->SetPos(fPoint(WINSIZEX / 2 + 400, WINSIZEY / 2 + 100));
	title3->SetScale(fPoint(220, 200));
	AddObject(title3, GROUP_GAMEOBJ::UI);
	CTitle4* title4 = new CTitle4;
	title4->SetPos(fPoint(WINSIZEX / 2 - 400, WINSIZEY / 2 + 100));
	title4->SetScale(fPoint(220, 200));
	AddObject(title4, GROUP_GAMEOBJ::UI);
	


	CCameraManager::getInst()->SetLookAt(fPoint(WINSIZEX / 2, WINSIZEY / 2));
	CSoundManager::getInst()->AddSound(L"Title", L"sound\\titlescreen.ogg", false , true);
	CSoundManager::getInst()->Play(L"Title");
}

void CScene_Start::Exit()
{
	DeleteAll();
	CSoundManager::getInst()->Stop(L"Title");
	CCollisionManager::getInst()->Reset();
}
