#pragma once
#include "CTileNavMap.h"

// 전방 선언 : 해당 클래스의 포인터 변수를 사용할 수 있게 해줌.
// 1. 헤더파일이 여러번 호출되어 #pragma에 의해 선언부를 확인 불가한 문제 해결
// 2. 컴파일 속도를 줄임
class CGameObject;

class CScene
{
private:
	vector<CGameObject*> m_arrObj[(int)GROUP_GAMEOBJ::SIZE];

	CTileNavMap* tileNav;
	wstring m_strName;
	bool clear = false;
	bool m_init = false;
public:
	CScene();
	virtual ~CScene();

	virtual void update();
	virtual void finalupdate();
	virtual void render();

	void render_tile();

	virtual void Enter() = 0;	// 해당 씬에 진입시 호출
	virtual void init() {};
	virtual void Exit() = 0;	// 해당 씬을 탈출시 호출

	void SetName(const wstring& strName);

	wstring GetName();

	const vector<CGameObject*>& GetGroupObject(GROUP_GAMEOBJ group);
	vector<CGameObject*>& GetUIGroup();		// UI는 렌더링 순서를 변경해야 하기 때문에 원본을 참조 / 주의 필요!
	vector<CGameObject*>& GetTiles();
	vector<CGameObject*>& GetPlayer();
	vector<CGameObject*>& GetPlayer2();

	bool GetInit();
	void SetInit(bool init);

	bool GetCrear();
	void SetCrear(bool clear);


	void AddObject(CGameObject* pObj, GROUP_GAMEOBJ group);
	void DeleteGroup(GROUP_GAMEOBJ group);
	void DeleteAll();
	void PlayerDelete();
	void StageChangeDelete();
	void GroupCheckSetting();
	void LoadTile(const wstring& strPath);
	void CurSceneMonsterAllStop(bool stop);


	CTileNavMap* GettileNav();
	void SetTileNav(CTileNavMap* nav);

	
};

