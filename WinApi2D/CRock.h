#pragma once
#include "CGameObject.h"
#include "CD2DImage.h"
#include "CCollider.h"
class CRock : public CGameObject
{
private:
	CD2DImage* m_pImg;

	int startX;
	int startY;
	int endX;
	int endY;

public:
	CRock();
	~CRock();

	virtual CRock* Clone();
	virtual void update();
	virtual void render();
	void SetFrame(int x, int y, int w, int h);
	RockFrame GetFrame();
	virtual void OnCollisionEnter(CCollider* _pOther);

};

