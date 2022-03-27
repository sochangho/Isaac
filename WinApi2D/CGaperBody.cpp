#include "framework.h"
#include "CGaperBody.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CBloodTears.h";


CGaperBody::CGaperBody()
{

    m_pImg = CResourceManager::getInst()->
        LoadD2DImage(L"GaperBody", L"texture\\Animation\\monsterBody.png");
    SetName(L"GaperHead");
    SetScale(fPoint(50, 50));
    CreateAnimator();
    GetAnimator()->CreateAnimation(L"IDLE", m_pImg, fPoint(0.f, 0.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.5f, 1);
    
    
    GetAnimator()->CreateAnimation(L"LEFT", m_pImg, fPoint(32.f * 2, 32.f * 2), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.1f, 2 , true);
    CAnimation* animation = GetAnimator()->FindAnimation(L"LEFT");
    animation->Create(m_pImg, fPoint(0.f, 32.f * 3), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.1f, 4);
    animation->Create(m_pImg, fPoint(0.f, 32.f * 4), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.1f, 4);
    
    GetAnimator()->CreateAnimation(L"RIGHT", m_pImg, fPoint(32.f*2, 32.f * 2), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.1f, 2);
    animation = GetAnimator()->FindAnimation(L"RIGHT");
    animation->Create(m_pImg, fPoint(0.f, 32.f*3), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.1f, 4);
    animation->Create(m_pImg, fPoint(0.f, 32.f *4), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.1f, 4);
    
    
    
    GetAnimator()->CreateAnimation(L"UP", m_pImg, fPoint(0.f, 0.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.1f, 4 , true);   
    animation = GetAnimator()->FindAnimation(L"UP");
    animation->Create(m_pImg, fPoint(0.f, 32.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.1f, 4);
    animation->Create(m_pImg, fPoint(0.f, 32.f*2), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.1f, 2);
    
    
    GetAnimator()->CreateAnimation(L"DOWN", m_pImg, fPoint(0.f, 0.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.1f, 4);    
    animation = GetAnimator()->FindAnimation(L"DOWN");
    animation->Create(m_pImg, fPoint(0.f, 32.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.1f, 4);
    animation->Create(m_pImg, fPoint(0.f, 32.f * 2), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.1f, 2);
    GetAnimator()->Play(L"IDLE");
}

CGaperBody::~CGaperBody()
{
}

CGaperBody* CGaperBody::Clone()
{
    return nullptr;
}

void CGaperBody::update()
{
    CCharacter::update();
    GetAnimator()->update();
}

void CGaperBody::render()
{
    CCharacter::render();
}

void CGaperBody::finalupdate()
{
    CCharacter::finalupdate();
}
