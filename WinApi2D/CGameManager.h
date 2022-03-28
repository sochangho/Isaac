#pragma once
class CGameObject;
class CIsaacPlayer;
class CIsaacPlayer2;
class CItem;
class CPlayerStateHart;
class CGameManager
{
	SINGLETON(CGameManager);
private:	
	
	int hp = 0;
	int bombCount = 0 ;
	int coin = 0;
	int hartcount = 0 ;

	bool savePlayer = false;

	fPoint playerPos;
	CIsaacPlayer* player;
	vector<CIsaacPlayer2*> player2Save;
	vector<CPlayerStateHart*> hartVec;
	CItem* item;
public:
	


	void init();
	void render();

	int GetHart();
	void SetHart(int hart);

	void SavePlayer();
	CIsaacPlayer* LoadPlayer();
	bool GetSaveCheck();

};

