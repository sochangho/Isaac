#include "framework.h"
#include "CBombImg.h"
#include "CD2DImage.h"
CBombImg::CBombImg()
{
    m_pImg = CResourceManager::getInst()
        ->LoadD2DImage(L"Bomb", L"texture\\Animation\\bombs.png");
}

CBombImg::~CBombImg()
{
}

void CBombImg::update()
{
}

CBombImg* CBombImg::Clone()
{
    return new CBombImg(*this);
}

void CBombImg::render()
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
		pos.y + scale.y, 0.f, 0.f, 32.5f, 32.5f);
}
