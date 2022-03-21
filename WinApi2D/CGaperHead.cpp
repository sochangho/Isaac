#include "framework.h"
#include "CGaperHead.h"
#include "CAnimation.h"
#include "CAnimator.h"
CGaperHead::CGaperHead()
{
    m_pImg = CResourceManager::getInst()->
        LoadD2DImage(L"GaperHead", L"texture\\Animation\\monsterHead.png");
    SetName(L"GaperHead");
    SetScale(fPoint(50, 50));
    CreateAnimator();
    GetAnimator()->CreateAnimation(L"IDLE", m_pImg, fPoint(32.f, 0.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 3.f, 1);
    GetAnimator()->Play(L"IDLE");
}

CGaperHead::~CGaperHead()
{
   
}

CGaperHead* CGaperHead::Clone()
{
    return new CGaperHead(*this);
}

void CGaperHead::update()
{
    CCharacter::update();
    GetAnimator()->update();
}

void CGaperHead::render()
{
    CCharacter::render();
}

void CGaperHead::finalupdate()
{
    CCharacter::finalupdate();
}
