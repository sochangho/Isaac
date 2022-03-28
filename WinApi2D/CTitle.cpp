#include "framework.h"
#include "CTitle.h"
#include "CD2DImage.h"
CTitle::CTitle()
{
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"title", L"texture\\map\\titlemenu.png");
	
}

CTitle::~CTitle()
{
}

CTitle * CTitle::Clone()
{
	return new CTitle(*this);
}

void CTitle::update()
{
}

void CTitle::render()
{

	if (nullptr == m_pImg)
	{
		return;
	}
	fPoint pos = GetPos();
	fPoint scale = GetScale();
	fPoint renderPos = CCameraManager::getInst()->GetRenderPos(pos);


	CRenderManager::getInst()->RenderFrame(
		m_pImg,
		renderPos.x - scale.x,
		renderPos.y - scale.y,
		renderPos.x + scale.x,
		renderPos.y + scale.y, 0.f, 0.f, 480.f, 270.f

	);


	CRenderManager::getInst()->RenderFrame(
		m_pImg,
		renderPos.x - scale.x,
		renderPos.y - scale.y,
		renderPos.x + scale.x,
		renderPos.y + scale.y, 0.f, 270.f, 480.f, 540.f

	);


}
