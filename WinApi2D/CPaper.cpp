#include "framework.h"
#include "CPaper.h"

CPaper::CPaper()
{
    m_pImg = CResourceManager::getInst()->LoadD2DImage(L"paper", L"texture\\Animation\\deathportraits.png");
    
}

CPaper::~CPaper()
{
}

CPaper* CPaper::Clone()
{
    return nullptr;
}

void CPaper::update()
{
}

void CPaper::render()
{

    if (nullptr == m_pImg)
    {
        return;
    }
    fPoint pos = GetPos();
    fPoint scale = GetScale();


    CRenderManager::getInst()->RenderFrame(
        m_pImg,
        pos.x - scale.x/2,
        pos.y - scale.y/2,
        pos.x + scale.x/2,
        pos.y + scale.y/2 , 208.f , 0.f , 416.f , 256.f);


}
