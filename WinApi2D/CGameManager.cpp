#include "framework.h"
#include "CGameManager.h"
#include "CGameObject.h"
#include "CIsaacPlayer.h"
#include "CIsaacPlayer2.h"
#include "CScene.h"
#include "CPlayerStateHart.h"
#include "CBombImg.h"
#include "CPaper.h"
CGameManager::CGameManager() {


}

CGameManager::~CGameManager() {

	if (m_player != nullptr) {

		m_player = nullptr;
	}


	for (int i = 0; i < m_player2Save.size(); i++) {

		m_player2Save[i] = nullptr;
	}

	m_player2Save.clear();


	for (int i = 0; i < m_hartVec.size(); i++) {

		delete m_hartVec[i];
	}

	m_hartVec.clear();

	delete m_bombImg;
}


void CGameManager::init()
{
	hp = 6;
	bombCount = 20;
	coin = 0;
	hartcount = hp/2;

	int size = 50;

	for (int i = 0; i < hartcount; i++) {

		float tum = size * i;
		m_hartVec.push_back(new CPlayerStateHart);
		m_hartVec[i]->SetPos(fPoint(50 + tum, 50));
		m_hartVec[i]->SetScale(fPoint(20 , 20));

	}

	m_bombImg = new CBombImg;
	m_bombImg->SetScale(fPoint(20, 20));
	m_bombImg->SetPos(fPoint(40, 108));

	m_paper = new CPaper;
	m_paper->SetScale(fPoint(500, 500));
	m_paper->SetPos(fPoint(WINSIZEX/2, WINSIZEY/2));

	CSoundManager::getInst()->AddSound(L"Door_Open", L"sound\\Effect\\doorheavyclose.wav");//
	CSoundManager::getInst()->AddSound(L"Door_Close", L"sound\\Effect\\doorheavyopen.wav");//
	CSoundManager::getInst()->AddSound(L"Attacked", L"sound\\Effect\\hurtgrunt.wav");//
	CSoundManager::getInst()->AddSound(L"Die", L"sound\\Effect\\isaacdiesnew.wav"); //
	CSoundManager::getInst()->AddSound(L"Monster", L"sound\\Effect\\monsterroar1.wav");
	CSoundManager::getInst()->AddSound(L"Item", L"sound\\Effect\\powerup1.wav");//
	CSoundManager::getInst()->AddSound(L"Bomb", L"sound\\Effect\\rockcrumble0.wav"); //
	CSoundManager::getInst()->AddSound(L"Tear1", L"sound\\Effect\\tearfire4.wav"); //
	CSoundManager::getInst()->AddSound(L"Tear2", L"sound\\Effect\\tearfire5.wav"); //
	//CSoundManager::getInst()->AddSound(L"basement", L"sound\\burningbasementloop.ogg" ,false, true); //

	 //
	

}

void CGameManager::render()
{
	


	int count = 0;
	int life = hp / 2;
	int lifeHarf = hp % 2;

		for (int i = 0; i < life; i++) {

			if (m_hartVec.size() > count) {

				m_hartVec[count]->SetState(HARTSTATE::DEFAULT);
				m_hartVec[count]->render();
				count++;
			}
		}


		

		if (lifeHarf == 1) {
				if (m_hartVec.size() > count) {

					m_hartVec[count]->SetState(HARTSTATE::HALF);
					m_hartVec[count]->render();
					count++;
				}
		}
			
		while(m_hartVec.size() > count){

				m_hartVec[count]->SetState(HARTSTATE::NONE);
				m_hartVec[count]->render();
				count++;
		}

		if (m_hartVec.size() > 0) {
				
				m_bombImg->render();				
				WCHAR strFPS[6];
				swprintf_s(strFPS, L"%5d", bombCount);
				CRenderManager::getInst()->RenderText(strFPS, 70, 150, 50, 50, 12, RGB(255, 255, 255));
				
		}

		if (m_diePlayer) {

		
				COLORREF color = RGB(0, 0, 0);
				CRenderManager::getInst()->RenderFillRectangle(0.f, 0.f, WINSIZEX, WINSIZEY, color, 0.8);
				if (m_paper != nullptr) {

					m_paper->render();
				}
		}


		
		
}

int CGameManager::GetHart()
{
	return hp;
}

int CGameManager::GetBombCount()
{
	return bombCount;
}

void CGameManager::SetHart(int hart)
{
	hp = hart;
}

void CGameManager::SetBombCount(int count)
{
	bombCount = count;
}

void CGameManager::SavePlayer()
{
	CScene* scene = CSceneManager::getInst()->GetCurScene();
   vector<CGameObject*>& vec = scene->GetPlayer2();
   vector<CGameObject*>& playerVec = scene->GetPlayer();
   for (int i = 0; i < playerVec.size(); i++) {
	   CIsaacPlayer* player = dynamic_cast<CIsaacPlayer*>(playerVec[i]);
	   if (player != nullptr) {

		   m_playerPos = player->GetPos();
		   this->m_player = player->Clone();

		   if (player->GetItem() != nullptr) {
			   m_item = player->GetItem()->Create();
		   }
	   }

   }
  

   for (int i = 0; i < vec.size(); i++) {
	   CIsaacPlayer2* player2 = dynamic_cast<CIsaacPlayer2*>(vec[i]);
	   if (player2 != nullptr) {
		   m_player2Save.push_back(player2->Clone());
	   }
   }

   m_savePlayer = true;

}

CIsaacPlayer* CGameManager::LoadPlayer()
{
	CScene* scene = CSceneManager::getInst()->GetCurScene();
	CIsaacPlayer* player = new CIsaacPlayer;
	player->SetPos(m_playerPos);
	if (m_item != nullptr) {
		player->SetItem(m_item);
	}
	scene->AddObject(player, GROUP_GAMEOBJ::PLAYER);
	for (int i = 0; i < m_player2Save.size(); i++) {

		player->AddPet(m_player2Save[i]);

	}


	for (int i = 0; i < m_player2Save.size(); i++) {

		m_player2Save[i] = nullptr;

	}
	m_player2Save.clear();
	m_item = nullptr;
	m_savePlayer = false;

	return player;
}

bool CGameManager::GetSaveCheck()
{
	return m_savePlayer;
}

bool CGameManager::GetDieCheck()
{
	return m_diePlayer;
}

void CGameManager::SetDiecheck(bool check)
{
	m_diePlayer = check;
}

void CGameManager::Reset()
{
	hp = 0;
	bombCount = 0;
	coin = 0;
	hartcount = 0;

	m_savePlayer = false;
	m_diePlayer = false;
	if (m_player != nullptr) {

		m_player = nullptr;
	}


	for (int i = 0; i < m_player2Save.size(); i++) {

		m_player2Save[i] = nullptr;
	}

	m_player2Save.clear();


	for (int i = 0; i < m_hartVec.size(); i++) {

		delete m_hartVec[i];
	}

	m_hartVec.clear();

	delete m_bombImg;
	delete m_paper;


}
