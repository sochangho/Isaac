#pragma once
#include "CGameObject.h"
#include "CD2DImage.h"

enum class HARTSTATE {
	DEFAULT,
	HALF,
	NONE,
};


class CPlayerStateHart : public CGameObject
{
private:
	CD2DImage* m_pImg;

	HARTSTATE state = HARTSTATE::DEFAULT;

public:

	CPlayerStateHart();
	~CPlayerStateHart();

	void SetState(HARTSTATE state);
	virtual CPlayerStateHart* Clone();
	virtual void update();
	virtual void render();


};

