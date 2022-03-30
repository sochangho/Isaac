#include "framework.h"
#include "CTitle3.h"

#include "CAnimation.h"
#include "CAnimator.h"
CTitle3::CTitle3()
{

    m_pImg = CResourceManager::getInst()->LoadD2DImage(L"title3", L"texture\\map\\title3.png");
    CreateAnimator();
    GetAnimator()->CreateAnimation(L"Idle", m_pImg, fPoint(0.f, 0.f), fPoint(68.57f, 77.14f), fPoint(68.57f, 0.f), 0.4f, 1);
    GetAnimator()->FindAnimation(L"Idle")->Create(m_pImg, fPoint(0.f, 77.14f), fPoint(68.57f, 77.14f), fPoint(68.57f, 0.f), 0.4f, 1);
    GetAnimator()->FindAnimation(L"Idle")->SetRenderPosCheck(false);
    GetAnimator()->Play(L"Idle");
}

CTitle3::~CTitle3()
{
}

CTitle3* CTitle3::Clone()
{
    return nullptr;
}

void CTitle3::update()
{
    GetAnimator()->update();
}

void CTitle3::render()
{
    component_render();
    
}