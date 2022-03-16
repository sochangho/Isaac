#include "framework.h"
#include "CPlayerBody.h"
#include "CCharacter.h"
#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"
CPlayerBody::CPlayerBody()
{
    m_pTex = CResourceManager::getInst()->
        LoadTextrue(L"PlayerBodyImg", L"texture\\Animation\\IsaacBody.bmp");
    SetName(L"PlayerHead");
    CreateAnimator();
    GetAnimator()->CreateAnimation(L"BODY_IDLE", m_pTex, fPoint(0.f, 0.f), fPoint(34.8f, 32.7f), fPoint(34.8f, 0.f), 0.5f, 1);
    GetAnimator()->CreateAnimation(L"BODY_RIGHT_MOVE", m_pTex, fPoint(0.f, 32.7f), fPoint(34.8f, 32.7f), fPoint(34.8f, 0.f), 0.1f, 10);
    GetAnimator()->CreateAnimation(L"BODY_LEFT_MOVE", m_pTex, fPoint(0.f , 32.7f*2.f), fPoint(34.8f, 32.7f), fPoint(34.8f, 0.f), 0.1f, 10);
    GetAnimator()->CreateAnimation(L"BODY_UP_MOVE", m_pTex, fPoint(34.8f * 5.f, 0.f), fPoint(34.8f, 32.7f), fPoint(34.8f, 0.f), 0.1f, 5);
    GetAnimator()->CreateAnimation(L"BODY_DOWN_MOVE", m_pTex, fPoint(0.f, 0.f), fPoint(34.8f, 32.7f), fPoint(34.8f, 0.f), 0.1f, 5);

    GetAnimator()->Play(L"BODY_IDLE");
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
    GetAnimator()->update();

}

void CPlayerBody::render(HDC hdc)
{
    CCharacter::render(hdc);
}

void CPlayerBody::finalupdate()
{
    CCharacter::finalupdate();
}
