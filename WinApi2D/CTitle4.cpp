#include "framework.h"
#include "CTitle4.h"
#include "CAnimation.h"
#include "CAnimator.h"
CTitle4::CTitle4()
{

    m_pImg = CResourceManager::getInst()->LoadD2DImage(L"title4", L"texture\\map\\title4.png");
    CreateAnimator();
    GetAnimator()->CreateAnimation(L"Idle", m_pImg, fPoint(0.f, 0.f), fPoint(60.f, 67.5f), fPoint(60.f, 0.f), 0.5f, 1);
    GetAnimator()->FindAnimation(L"Idle")->Create(m_pImg, fPoint(0.f, 67.5f), fPoint(60.f, 67.5f), fPoint(60.f, 0.f), 0.5f, 1);
    GetAnimator()->FindAnimation(L"Idle")->SetRenderPosCheck(false);
    GetAnimator()->Play(L"Idle");
}

CTitle4::~CTitle4()
{
}

CTitle4* CTitle4::Clone()
{
    return nullptr;
}

void CTitle4::update()
{
    GetAnimator()->update();
}

void CTitle4::render()
{
    component_render();

}