#include "framework.h"
#include "CGameManager.h"
#include "CGameObject.h"
#include "CIsaacPlayer.h"
#include "CIsaacPlayer2.h"
#include "CScene.h"
#include "CPlayerStateHart.h"
#include "CBombImg.h"
CGameManager::CGameManager() {


}

CGameManager::~CGameManager() {

	if (player != nullptr) {

		player = nullptr;
	}


	for (int i = 0; i < player2Save.size(); i++) {

		player2Save[i] = nullptr;
	}

	player2Save.clear();


	for (int i = 0; i < hartVec.size(); i++) {

		delete hartVec[i];
	}

	hartVec.clear();

	delete bombImg;
}


void CGameManager::init()
{
	hp = 6;
	bombCount = 1;
	coin = 0;
	hartcount = hp/2;

	int size = 50;

	for (int i = 0; i < hartcount; i++) {

		float tum = size * i;
		hartVec.push_back(new CPlayerStateHart);
		hartVec[i]->SetPos(fPoint(50 + tum, 50));
		hartVec[i]->SetScale(fPoint(20 , 20));

	}

	bombImg = new CBombImg;
	bombImg->SetScale(fPoint(20, 20));
	bombImg->SetPos(fPoint(40, 108));

}

void CGameManager::render()
{
	


	int count = 0;
	int life = hp / 2;
	int lifeHarf = hp % 2;

		for (int i = 0; i < life; i++) {

			if (hartVec.size() > count) {

				hartVec[count]->SetState(HARTSTATE::DEFAULT);
				hartVec[count]->render();
				count++;
			}
		}


		

		if (lifeHarf == 1) {
				if (hartVec.size() > count) {

					hartVec[count]->SetState(HARTSTATE::HALF);
					hartVec[count]->render();
					count++;
				}
		}
			
		while(hartVec.size() > count){

				hartVec[count]->SetState(HARTSTATE::NONE);
				hartVec[count]->render();
				count++;
		}

			if (hartVec.size() > 0) {
				
				bombImg->render();				
				WCHAR strFPS[6];
				swprintf_s(strFPS, L"%5d", bombCount);
				CRenderManager::getInst()->RenderText(strFPS, 70, 150, 50, 50, 12, RGB(255, 255, 255));
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

		   playerPos = player->GetPos();
		   this->player = player->Clone();

		   if (player->GetItem() != nullptr) {
			   item = player->GetItem()->Create();
		   }
	   }

   }
  

   for (int i = 0; i < vec.size(); i++) {
	   CIsaacPlayer2* player2 = dynamic_cast<CIsaacPlayer2*>(vec[i]);
	   if (player2 != nullptr) {
		   player2Save.push_back(player2->Clone());
	   }
   }

   savePlayer = true;

}

CIsaacPlayer* CGameManager::LoadPlayer()
{
	CScene* scene = CSceneManager::getInst()->GetCurScene();
	CIsaacPlayer* player = new CIsaacPlayer;
	player->SetPos(playerPos);
	if (item != nullptr) {
		player->SetItem(item);
	}
	scene->AddObject(player, GROUP_GAMEOBJ::PLAYER);
	for (int i = 0; i < player2Save.size(); i++) {

		player->AddPet(player2Save[i]);

	}


	for (int i = 0; i < player2Save.size(); i++) {

		player2Save[i] = nullptr;

	}
	player2Save.clear();
	item = nullptr;
	savePlayer = false;

	return player;
}

bool CGameManager::GetSaveCheck()
{
	return savePlayer;
}

void CGameManager::Reset()
{
	hp = 0;
	bombCount = 0;
	coin = 0;
	hartcount = 0;

	bool savePlayer = false;

	if (player != nullptr) {

		player = nullptr;
	}


	for (int i = 0; i < player2Save.size(); i++) {

		player2Save[i] = nullptr;
	}

	player2Save.clear();


	for (int i = 0; i < hartVec.size(); i++) {

		delete hartVec[i];
	}

	hartVec.clear();

	delete bombImg;

	bombImg = nullptr;

}
