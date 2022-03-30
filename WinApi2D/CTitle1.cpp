#include "framework.h"
#include "CTitle1.h"

CTitle1::CTitle1()
{
    m_pImg = CResourceManager::getInst()->LoadD2DImage(L"title1", L"texture\\map\\title1.png");
}

CTitle1::~CTitle1()
{
}

CTitle1* CTitle1::Clone()
{
    return nullptr;
}

void CTitle1::update()
{
}

void CTitle1::render()
{

	if (nullptr == m_pImg)
	{
		return;
	}
	fPoint pos = GetPos();
	fPoint scale = GetScale();


	CRenderManager::getInst()->RenderFrame(
		m_pImg,
		pos.x - scale.x,
		pos.y - scale.y,
		pos.x + scale.x,
		pos.y + scale.y, 0.f, 0.f, 262.f, 99.f

	);


}
