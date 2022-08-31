#pragma once
class CGameObject;
class CIsaacPlayer;
class CIsaacPet;
class CItem;
class CPlayerStateHart;
class CBombImg;
class CPaper;

class CGameManager
{
	SINGLETON(CGameManager);
private:	
	
	int                       hp = 0;
	int                       bombCount = 0 ;
	int                       coin = 0;
	int                       hartcount = 0 ;

	bool                      m_savePlayer = false;
	bool                      m_diePlayer = false;
	fPoint                    m_playerPos;
	CIsaacPlayer*             m_player;
	vector<CIsaacPet*>    m_player2Save;
	vector<CPlayerStateHart*> m_hartVec;
	CBombImg*                 m_bombImg;
	CPaper*                   m_paper;
	CItem*                    m_item;
public:
	


	void init();
	void render();

	int GetHart();
	int GetBombCount();

	void SetHart(int hart);
	void SetBombCount(int count);



	void SavePlayer();
	CIsaacPlayer* LoadPlayer();
	bool GetSaveCheck();
	bool GetDieCheck();
	
	void SetDiecheck(bool check);

	void Reset();

};

