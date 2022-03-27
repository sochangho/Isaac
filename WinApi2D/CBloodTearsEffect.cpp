#include "framework.h"
#include "CBloodTearsEffect.h"
#include "CEffect.h"
#include "CAnimator.h"
#include "CAnimation.h"
CBloodTearsEffect::CBloodTearsEffect()
{
    SetEffectImg(CResourceManager::getInst()->
        LoadD2DImage(L"TearsBloodEffect", L"texture\\Animation\\blodTearsEffect.png"));
    SetName(L"Effect");
    SetScale(fPoint(90, 90));
    CreateAnimator();
    GetAnimator()->CreateAnimation(L"IDLE", GetEffectImg(), fPoint(0.f, 0.f), fPoint(64.f, 64.f), fPoint(64.f, 0.f), 0.05f, 4);
    CAnimation* animation = GetAnimator()->FindAnimation(L"IDLE");
    animation->Create(GetEffectImg(), fPoint(0.f, 64.f), fPoint(64.f, 64.f), fPoint(64.f, 0.f), 0.05f, 4);
    animation->Create(GetEffectImg(), fPoint(0.f, 64.f * 2), fPoint(64.f, 64.f), fPoint(64.f, 0.f), 0.05f, 4);
    animation->Create(GetEffectImg(), fPoint(0.f, 64.f * 3), fPoint(64.f, 64.f), fPoint(64.f, 0.f), 0.05f, 4);
    SetDuration(0.8f);
    GetAnimator()->Play(L"IDLE");
}

CBloodTearsEffect::~CBloodTearsEffect()
{
}

CBloodTearsEffect* CBloodTearsEffect::Clone()
{
    return new CBloodTearsEffect;
}

void CBloodTearsEffect::update()
{
    CEffect::update();
    GetAnimator()->update();
}

void CBloodTearsEffect::render()
{
    CEffect::render();
}
