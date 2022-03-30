#include "framework.h"
#include "CTitle2.h"
#include "CAnimation.h"
#include "CAnimator.h"
CTitle2::CTitle2()
{
    m_pImg = CResourceManager::getInst()->LoadD2DImage(L"title2", L"texture\\map\\title2.png");
    CreateAnimator();
    GetAnimator()->CreateAnimation(L"Idle", m_pImg, fPoint(0.f, 0.f), fPoint(160.f, 160.f), fPoint(160.f, 0.f), 0.5f, 2);
    GetAnimator()->Play(L"Idle");
    GetAnimator()->FindAnimation(L"Idle")->SetRenderPosCheck(false);
}

CTitle2::~CTitle2()
{
}

CTitle2* CTitle2::Clone()
{
    return nullptr;
}

void CTitle2::update()
{

    GetAnimator()->update();
}

void CTitle2::render()
{
    component_render();
}
