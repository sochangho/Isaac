#include "framework.h"
#include "CPlayerBody.h"
#include "CCharacter.h"
#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"
CPlayerBody::CPlayerBody()
{
    m_pImg = CResourceManager::getInst()->
        LoadD2DImage(L"PlayerImg", L"texture\\Animation\\IsaacHead.bmp");
    SetName(L"PlayerHead");
    CreateAnimator();
    GetAnimator()->CreateAnimation(L"IDLE", m_pImg, fPoint(0.f, 0.f), fPoint(40.f, 34.f), fPoint(40.f, 0.f), 0.5f, 1);
    GetAnimator()->CreateAnimation(L"RIGHT_MOVE", m_pImg, fPoint(40.f * 2.f, 0.f), fPoint(40.f, 34.f), fPoint(40.f, 0.f), 0.5f, 1);
    GetAnimator()->CreateAnimation(L"LEFT_MOVE", m_pImg, fPoint(40.f * 6.f, 0.f), fPoint(40.f, 34.f), fPoint(40.f, 0.f), 0.5f, 1);
    GetAnimator()->CreateAnimation(L"UP_MOVE", m_pImg, fPoint(40.f * 4.f, 0.f), fPoint(40.f, 34.f), fPoint(40.f, 0.f), 0.5f, 2);
    GetAnimator()->CreateAnimation(L"DOWN_MOVE", m_pImg, fPoint(0.f, 0.f), fPoint(40.f, 34.f), fPoint(40.f, 0.f), 0.5f, 1);



    GetAnimator()->CreateAnimation(L"RIGHT_ATTACK", m_pImg, fPoint(40.f * 2.f, 0.f), fPoint(40.f, 34.f), fPoint(40.f, 0.f), 0.5f, 2);
    GetAnimator()->CreateAnimation(L"LEFT_ATTACK", m_pImg, fPoint(40.f * 6.f, 0.f), fPoint(40.f, 34.f), fPoint(40.f, 0.f), 0.5f, 2);
    GetAnimator()->CreateAnimation(L"UP_ATTACK", m_pImg, fPoint(40.f * 4.f, 0.f), fPoint(40.f, 34.f), fPoint(40.f, 0.f), 0.5f, 2);
    GetAnimator()->CreateAnimation(L"DOWN_ATTACK", m_pImg, fPoint(0.f, 0.f), fPoint(40.f, 34.f), fPoint(40.f, 0.f), 0.5f, 2);
}

CPlayerBody::~CPlayerBody()
{
}

CPlayerBody* CPlayerBody::Clone()
{
    return new CPlayerBody(*this);
}

void CPlayerBody::update()
{
    CCharacter::update();

}

void CPlayerBody::render()
{
    CCharacter::render();
}

void CPlayerBody::finalupdate()
{
    CCharacter::finalupdate();
}
