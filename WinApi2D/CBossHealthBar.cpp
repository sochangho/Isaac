#include "framework.h"
#include "CBossHealthBar.h"

CBossHealthBar::CBossHealthBar()
{
    m_pImg = CResourceManager::getInst()->LoadD2DImage(L"HealthBar", L"texture\\ui_bosshealthbar.png");
    
   
   

}

CBossHealthBar::~CBossHealthBar()
{
	if (m_monster != nullptr) {
		m_monster = nullptr;
	}
}

CBossHealthBar* CBossHealthBar::Clone()
{
    return nullptr;
}

void CBossHealthBar::update()
{
}

void CBossHealthBar::render()
{
	if (nullptr == m_pImg)
	{
		return;
	}
	fPoint pos = GetPos();
	fPoint scale = GetScale();


	CRenderManager::getInst()->RenderFrame(
		m_pImg,
		pos.x ,
		pos.y ,
		pos.x + scale.x,
		pos.y + scale.y, 0.f, 32.f, 150.f, 64.f

	);

	fPoint pointFill ;
	pointFill.x = pos.x + 60;
	pointFill.y = pos.y + 32;
	fPoint scaleFill;
	scaleFill.x = scale.x / 2 + 80;
	scaleFill.y = scale.y / 2 - 20;

	if (m_monster != nullptr) {
		scaleFill.x = scaleFill.x * m_monster->GetHpPercent();
	}
	CRenderManager::getInst()->RenderFillRectangle
	(pointFill.x , pointFill.y, pointFill.x + scaleFill.x, pointFill.y + scaleFill.y, RGB(255, 0, 0));


}

void CBossHealthBar::SetMonster(CMonster* monster)
{
	m_monster = monster;
}
