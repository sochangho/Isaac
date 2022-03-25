#pragma once
class CGameObject;
class CIsaacPlayer;
class CIsaacPlayer2;
class CItem;
class CGameManager
{
	SINGLETON(CGameManager);
private:	
	
	int hp = 6;
	int bombCount = 1;
	int coin = 0.f;

	bool savePlayer = false;

	fPoint playerPos;
	CIsaacPlayer* player;
	vector<CIsaacPlayer2*> player2Save;
	CItem* item;
public:
	
	void SavePlayer();
	CIsaacPlayer* LoadPlayer();
	bool GetSaveCheck();

};

