#include "framework.h"
#include "CDestoryRock.h"

CDestoryRock::CDestoryRock()
{
     m_pImg = CResourceManager::getInst()->LoadD2DImage(L"Rock", L"texture\\map\\rocks_basement.png");
     SetScale(fPoint(50, 50));
}

CDestoryRock::~CDestoryRock()
{
}

CDestoryRock* CDestoryRock::Clone()
{
    return nullptr;
}

void CDestoryRock::update()
{
}

void CDestoryRock::render()
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
        renderPos.x - scale.x / 2,
        renderPos.y - scale.y / 2,
        renderPos.x + scale.x / 2,
        renderPos.y + scale.y / 2, 32.f*3, 0.f, 32.f*4, 32.f
    );
}
