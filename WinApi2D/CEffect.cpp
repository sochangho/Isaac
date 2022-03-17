#include "framework.h"
#include "CEffect.h"
#include "CAnimator.h"
CEffect::CEffect()
{
}


CEffect::~CEffect()
{
}

CEffect* CEffect::Clone()
{
    return new CEffect(*this);
}

void CEffect::update()
{
    if (m_curTime < m_duration) {

        m_curTime += fDT;

    }
    else {

        DeleteObj(this);
    }

   

}

void CEffect::render()
{
    component_render();
}

CD2DImage* CEffect::GetEffectImg()
{
    return m_pImg;
}

void CEffect::SetEffectImg(CD2DImage* pImg)
{
    m_pImg = pImg;
}

void CEffect::SetDuration(float duration)
{
    m_duration = duration;
}
