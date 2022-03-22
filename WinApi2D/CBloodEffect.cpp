#include "framework.h"
#include "CBloodEffect.h"
#include "CAnimator.h"
#include "CBombEffect.h"
#include "CAnimation.h"
CBloodEffect::CBloodEffect()
{
    SetEffectImg(CResourceManager::getInst()->
        LoadD2DImage(L"BloodEffect", L"texture\\Animation\\bloodEffect.png"));
    SetName(L"Effect");
    SetScale(fPoint(100, 100));
    CreateAnimator();
    GetAnimator()->CreateAnimation(L"IDLE", GetEffectImg(), fPoint(0.f, 0.f), fPoint(64.f, 64.f), fPoint(64.f, 0.f), 0.1f, 4);
    CAnimation* animation = GetAnimator()->FindAnimation(L"IDLE");
    animation->Create(GetEffectImg(), fPoint(0.f, 64.f), fPoint(64.f, 64.f), fPoint(64.f, 0.f), 0.1f, 4);
    animation->Create(GetEffectImg(), fPoint(0.f, 64.f * 2), fPoint(64.f, 64.f), fPoint(64.f, 0.f), 0.1f, 4);
    animation->Create(GetEffectImg(), fPoint(0.f, 64.f * 3), fPoint(64.f, 64.f), fPoint(64.f, 0.f), 0.1f, 4);
    SetDuration(1.6f);
    GetAnimator()->Play(L"IDLE");
}

CBloodEffect::~CBloodEffect()
{
}

CBloodEffect* CBloodEffect::clone()
{
    return new CBloodEffect(*this);
}

void CBloodEffect::update()
{
    CEffect::update();
    GetAnimator()->update();
}

void CBloodEffect::render()
{
    CEffect::render();
}
