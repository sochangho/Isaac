#include "framework.h"
#include "CScene_Start.h"

#include "CGameObject.h"
#include "CPlayer.h"
#include "CMonster.h"

#include "CSound.h"
#include "CIsaacPlayer.h"

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::update()
{
	CScene::update();

	/*if (KeyDown(VK_TAB))
	{
		ChangeScn(GROUP_SCENE::TOOL);
	}

	if (KeyDown(VK_LBUTTON))
	{
		fPoint fptLookAt = CCameraManager::getInst()->GetRealPos(MousePos());
		CCameraManager::getInst()->SetLookAt(fptLookAt);
	}

	if (KeyDown('Z'))
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
	// Ÿ�� �ε�
	//wstring path = CPathManager::getInst()->GetContentPath();
	//path += L"tile\\Start.tile";
	////LoadTile(path);

	//// Player �߰�
	//CGameObject* pPlayer = new CPlayer;
	//pPlayer->SetPos(fPoint(200, 200));
	//AddObject(pPlayer, GROUP_GAMEOBJ::PLAYER);

	//// Monster �߰�
	//CMonster* pMonster = new CMonster;
	//pMonster->SetPos(fPoint(1100, 350));
	//pMonster->SetCenterPos(pMonster->GetPos());
	//AddObject(pMonster, GROUP_GAMEOBJ::MONSTER);

	//CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::MONSTER);
	//CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::MISSILE_PLAYER, GROUP_GAMEOBJ::MONSTER);

	//// Camera Look ����
	//CCameraManager::getInst()->SetLookAt(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
	//CCameraManager::getInst()->FadeOut(5.f);
	//CCameraManager::getInst()->FadeIn(5.f);
	////CCameraManager::getInst()->SetTargetObj(pPlayer);

	CIsaacPlayer* player = new CIsaacPlayer;
	player->SetPos(fPoint(200, 200));
	AddObject(player, GROUP_GAMEOBJ::PLAYER);
	CCameraManager::getInst()->SetLookAt(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));


}

void CScene_Start::Exit()
{
	DeleteAll();

	CCollisionManager::getInst()->Reset();
}
