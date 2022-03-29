#pragma once

class CScene;

class CSceneManager
{
	SINGLETON(CSceneManager);
	
	friend class CEventManager;

private:
	CScene* m_arrScene[(int)GROUP_SCENE::SIZE];		// ÀüÃ¼ ¾À ¸ñ·Ï
	CScene* m_pCurScene;							// ÇöÀç ¾À




	void ChangeScene(GROUP_SCENE scene);			// ¾À ÀüÈ¯
	

public:
	void update();
	void render();
	void init();

	CScene* GetCurScene();							//ÇöÀç ¾À ¹ÝÈ¯
	void GameEnd(GROUP_SCENE scene);
};

