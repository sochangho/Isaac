#pragma once
#include "CGameObject.h"
#include "CD2DImage.h"
#include "CCollider.h"

enum class DOOR_DIR{
	UP,DOWN,LEFT,RIGHT
};

enum class DOOR_STATE {

	Open , CLOSE , GO_OPEN , GO_CLOSE

};

class CDoor :public CGameObject
{
private:

	
	
	float m_doorT;
	CD2DImage* m_Img;
	DOOR_DIR m_doorDir;
	DOOR_STATE m_doorstate;

	GROUP_SCENE goScene;

public:

	CDoor();
	~CDoor();

	void Load(DOOR_DIR doorDir , GROUP_SCENE scene);

	virtual CDoor* Clone();
	virtual void update();
	virtual void render();

	void ChangeDoorState(DOOR_STATE state);

	virtual void OnCollisionEnter(CCollider* _pOther);

};

