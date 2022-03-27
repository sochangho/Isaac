#include "framework.h"
#include "CSceneManager.h"

#include "CScene_Start.h"
#include "CScene_Tool.h"
#include "CStartRoom.h"
#include "CItemRoom1.h"
#include "CItemRoom2.h"
#include "CNomalRoom1.h"
#include "CNomalRoom2.h"
CSceneManager::CSceneManager()
{
	// 씬 목록 초기화
	for (int i = 0; i < (int)GROUP_SCENE::SIZE; i++)
	{
		m_arrScene[i] = nullptr;
	}
	m_pCurScene = nullptr;
}

CSceneManager::~CSceneManager()
{
	// 씬 목록 삭제
	for (int i = 0; i < (int)GROUP_SCENE::SIZE; i++)
	{
		if (nullptr != m_arrScene[i])
		{
			delete m_arrScene[i];
		}
	}
}

void CSceneManager::ChangeScene(GROUP_SCENE scene)
{
	

	m_pCurScene->Exit();
	m_pCurScene = m_arrScene[(UINT)scene];
	

	m_pCurScene->Enter();


	if (!m_pCurScene->GetInit()) {

		m_pCurScene->SetInit(true);
		m_pCurScene->init();

	}
}

void CSceneManager::update()
{
	m_pCurScene->update();
	m_pCurScene->finalupdate();
}

void CSceneManager::render()
{
	m_pCurScene->render();
}

void CSceneManager::init()
{
	m_arrScene[(size_t)GROUP_SCENE::START] = new CScene_Start;
	m_arrScene[(size_t)GROUP_SCENE::START]->SetName(L"Start_Scene");

	m_arrScene[(size_t)GROUP_SCENE::TOOL] = new CScene_Tool;
	m_arrScene[(size_t)GROUP_SCENE::TOOL]->SetName(L"Tool_Scene");

	m_arrScene[(size_t)GROUP_SCENE::STARTROOM] = new CStartRoom;
	m_arrScene[(size_t)GROUP_SCENE::STARTROOM]->SetName(L"StartRoom");

	m_arrScene[(size_t)GROUP_SCENE::ITEMROOM] = new CItemRoom1;
	m_arrScene[(size_t)GROUP_SCENE::ITEMROOM]->SetName(L"ItemRoom1");

	m_arrScene[(size_t)GROUP_SCENE::ITEMROOM1] = new CItemRoom2;
	m_arrScene[(size_t)GROUP_SCENE::ITEMROOM1]->SetName(L"ItemRoom2");

	m_arrScene[(size_t)GROUP_SCENE::NOMALROOM1] = new CNomalRoom1;
	m_arrScene[(size_t)GROUP_SCENE::NOMALROOM1]->SetName(L"NomalRoom1");

	m_arrScene[(size_t)GROUP_SCENE::NOMALROOM2] = new CNomalRoom2;
	m_arrScene[(size_t)GROUP_SCENE::NOMALROOM2]->SetName(L"NomalRoom2");

	m_pCurScene = m_arrScene[(size_t)GROUP_SCENE::START];
	m_pCurScene->Enter();
}

CScene* CSceneManager::GetCurScene()
{
	return m_pCurScene;
}
