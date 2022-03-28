#include "framework.h"
#include "CPlayerStateHart.h"

CPlayerStateHart::CPlayerStateHart()
{
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"hart", L"texture\\map\\ui_hearts.png");
	SetScale(fPoint(50, 50));
}

CPlayerStateHart::~CPlayerStateHart()
{
}

void CPlayerStateHart::SetState(HARTSTATE state)
{
	this->state = state;
}

CPlayerStateHart * CPlayerStateHart::Clone()
{
	return new CPlayerStateHart(*this) ;
}

void CPlayerStateHart::update()
{
}

void CPlayerStateHart::render()
{

	if (nullptr == m_pImg)
	{
		return;
	}
	fPoint pos = GetPos();
	fPoint scale = GetScale();
	
	float startX;
	float startY;
	float endX;
	float endY;


	if (state == HARTSTATE::DEFAULT) {

		startX = 0.f;
		startY = 0.f;
		endX = 16.f;
		endY = 15.f;

	}
	else if(state == HARTSTATE::HALF){

		startX = 16.f;
		startY = 0.f;
		endX = 38.f;
		endY = 15.f;


	}
	else if (state == HARTSTATE::NONE) {
		startX = 38.f;
		startY = 0.f;
		endX = 54.f;
		endY = 15.f;

	}


	CRenderManager::getInst()->RenderFrame(
		m_pImg,
		pos.x - scale.x,
		pos.y - scale.y,
	    pos.x + scale.x,
		pos.y + scale.y, startX, startY, endX, endY);



}
