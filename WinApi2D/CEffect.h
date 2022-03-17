#pragma once
#include "CGameObject.h"
#include"CD2DImage.h"
class CEffect : public CGameObject
{
private:
	float m_duration;
	float m_curTime = 0.f;
	CD2DImage* m_pImg;
public:
	CEffect();
	virtual ~CEffect();


	virtual CEffect* Clone();

	virtual void update();
	virtual void render();

protected:
	CD2DImage* GetEffectImg();
	void SetEffectImg(CD2DImage* pImg);
	void SetDuration(float duration);
};

