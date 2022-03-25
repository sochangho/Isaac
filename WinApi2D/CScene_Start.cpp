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
#include "CCollider.h"

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
	//if (KeyDown('Z'))
	//{
	//	CSoundManager::getInst()->AddSound(L"bgm", L"sound\\drumloop.wav", true);
	//	CSoundManager::getInst()->Play(L"bgm");
	//}

	//if (KeyDown('X'))
	//{
	//	CSoundManager::getInst()->Stop(L"bgm");
	//}
}

void CScene_Start::Enter()
{
	
}

void CScene_Start::Exit()
{
	DeleteAll();

	CCollisionManager::getInst()->Reset();
}
