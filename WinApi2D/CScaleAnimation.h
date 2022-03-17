#pragma once
#include "CGameObject.h"




class CScaleAnimation
{
private:
	

	struct ScaleAnimation {


		float m_scale;
		float m_velocity;

	};



	vector<ScaleAnimation*> m_vecScaleX;
	vector<ScaleAnimation*> m_vecScaleY;
	int m_curIndexX = 0;
	int m_curIndexY = 0;
	
public:
	CScaleAnimation();
	~CScaleAnimation();

	void ScaleInit(float scaleX, float scaleY, float m_velocX, float m_velocY);
	void ScaleAnimationUpate(CGameObject* obj);


};

