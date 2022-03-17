#include "framework.h"
#include "CEffect.h"
#include "CAnimator.h"
#include "CBombEffect.h"
#include "CAnimation.h"
CBombEffect::CBombEffect()
{

    SetEffectImg(CResourceManager::getInst()->
        LoadD2DImage(L"bombEffect", L"texture\\Animation\\bombEffect.png"));
    SetName(L"Effect");
    SetScale(fPoint(200, 200));
    CreateAnimator();
    GetAnimator()->CreateAnimation(L"IDLE", GetEffectImg(), fPoint(0.f, 0.f), fPoint(96.f, 96.f), fPoint(96.f, 0.f), 0.05f, 4);
    CAnimation* animation = GetAnimator()->FindAnimation(L"IDLE");
    animation->Create(GetEffectImg(), fPoint(0.f, 96.f), fPoint(96.f, 96.f), fPoint(96.f, 0.f), 0.05f, 4);
    animation->Create(GetEffectImg(), fPoint(0.f, 96.f * 2), fPoint(96.f, 96.f), fPoint(96.f, 0.f), 0.05f, 4);
    
    SetDuration(0.6f);
    GetAnimator()->Play(L"IDLE");
}

CBombEffect::~CBombEffect()
{
}

CBombEffect* CBombEffect::Clone()
{
    return new CBombEffect(*this);
}

void CBombEffect::update()
{
    CEffect::update();
    GetAnimator()->update();
}

void CBombEffect::render()
{
    CEffect::render();
}
