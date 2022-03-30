#pragma once
#include "CGameObject.h"
#include "CTile.h"
#include "CCollider.h"
#include "CScene.h"
#include "CIsaacPlayer.h"



class CDropItem : public CGameObject
{
protected:
    

private:

	fVec2 m_dir;
	float m_adDuration = 0.2f;
	float m_adCurTime = 0.f;

	

	bool m_isPlayerCol = false;

	float m_velocity = 0.f;
public:
	CDropItem();
	~CDropItem();

	virtual CDropItem* Clone();
	virtual void update();
	virtual void render();


  

	virtual void OnCollision(CCollider* pOther);
	virtual void OnCollisionEnter(CCollider* pOther);
	virtual void OnCollisionExit(CCollider* pOther);
};

