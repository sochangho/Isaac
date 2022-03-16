#include "framework.h"
#include "CPlayerHead.h"
#include "CCharacter.h"
#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"
CPlayerHead::CPlayerHead()
{
  
    m_pTex = CResourceManager::getInst()->
        LoadTextrue(L"PlayerHeadImg", L"texture\\Animation\\IsaacHead.bmp");
    SetName(L"PlayerHead");
    CreateAnimator();
    GetAnimator()->CreateAnimation(L"IDLE", m_pTex, fPoint(0.f, 0.f), fPoint(40.f, 34.f), fPoint(40.f, 0.f), 0.5f, 1);
    GetAnimator()->CreateAnimation(L"RIGHT_MOVE", m_pTex, fPoint(40.f * 2.f, 0.f), fPoint(40.f, 34.f), fPoint(40.f, 0.f), 0.5f, 1);
    GetAnimator()->CreateAnimation(L"LEFT_MOVE", m_pTex, fPoint(40.f * 6.f, 0.f), fPoint(40.f, 34.f), fPoint(40.f, 0.f), 0.5f, 1);
    GetAnimator()->CreateAnimation(L"UP_MOVE", m_pTex, fPoint(40.f * 4.f, 0.f), fPoint(40.f, 34.f), fPoint(40.f, 0.f), 0.5f, 2);
    GetAnimator()->CreateAnimation(L"DOWN_MOVE", m_pTex, fPoint(0.f, 0.f), fPoint(40.f, 34.f), fPoint(40.f, 0.f), 0.5f, 1);



    GetAnimator()->CreateAnimation(L"RIGHT_ATTACK", m_pTex, fPoint(40.f * 2.f, 0.f), fPoint(40.f, 34.f), fPoint(40.f, 0.f), 0.5f, 2);
    GetAnimator()->CreateAnimation(L"LEFT_ATTACK", m_pTex, fPoint(40.f * 6.f, 0.f), fPoint(40.f, 34.f), fPoint(40.f, 0.f), 0.5f, 2);
    GetAnimator()->CreateAnimation(L"UP_ATTACK", m_pTex, fPoint(40.f * 4.f, 0.f), fPoint(40.f, 34.f), fPoint(40.f, 0.f), 0.5f, 2);
    GetAnimator()->CreateAnimation(L"DOWN_ATTACK", m_pTex, fPoint(0.f, 0.f), fPoint(40.f, 34.f), fPoint(40.f, 0.f), 0.5f, 2);

    GetAnimator()->Play(L"IDLE");
}

CPlayerHead::~CPlayerHead()
{
}

CPlayerHead* CPlayerHead::Clone()
{
    return new CPlayerHead(*this);
}

void CPlayerHead::update()
{
    CCharacter::update();
    GetAnimator()->update();
}

void CPlayerHead::render(HDC hdc)
{
    CCharacter::render(hdc);
}

void CPlayerHead::finalupdate()
{
    CCharacter::finalupdate();
}
