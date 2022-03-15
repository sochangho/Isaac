#include "framework.h"
#include "CPlayerHead.h"
#include "CCharacter.h"
#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"
CPlayerHead::CPlayerHead()
{
    m_pImg = CResourceManager::getInst()->
        LoadD2DImage(L"PlayerImg", L"texture\\Animation\\IsaacBody.bmp");
    SetName(L"PlayerBody");
    CreateAnimator();
    GetAnimator()->CreateAnimation(L"IDLE", m_pImg, fPoint(0.f, 0.f), fPoint(34.8f, 32.7f), fPoint(34.8f, 0.f), 0.5f, 1);
    GetAnimator()->CreateAnimation(L"RIGHT_MOVE", m_pImg, fPoint(34.8f, 0.f), fPoint(34.8f, 32.7f), fPoint(34.8f, 0.f), 0.1f, 10);
    GetAnimator()->CreateAnimation(L"LEFT_MOVE", m_pImg, fPoint(34.8f*2.f, 0.f), fPoint(34.8f, 32.7f), fPoint(34.8f, 0.f), 0.1f, 10);
    GetAnimator()->CreateAnimation(L"UP_MOVE", m_pImg, fPoint(0.f, 32.7f*5.f), fPoint(34.8f, 32.7f), fPoint(34.8f, 0.f), 0.1f, 5);
    GetAnimator()->CreateAnimation(L"DOWN_MOVE", m_pImg, fPoint(0.f, 0.f), fPoint(34.8f, 32.7f), fPoint(34.8f, 0.f), 0.1f, 5);

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
}

void CPlayerHead::render()
{
    CCharacter::render();
}

void CPlayerHead::finalupdate()
{
    CCharacter::finalupdate();
}
