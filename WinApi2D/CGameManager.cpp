#include "framework.h"
#include "CGameManager.h"
#include "CGameObject.h"
#include "CIsaacPlayer.h"
#include "CIsaacPlayer2.h"
#include "CScene.h"
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
