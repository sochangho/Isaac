#include "framework.h"
#include "CPlayerHead.h"
#include "CCharacter.h"
#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CIsaacPlayer.h"
#include "CTile.h"
CPlayerHead::CPlayerHead()
{
  
    m_pImg = CResourceManager::getInst()->
        LoadD2DImage(L"PlayerHead", L"texture\\Animation\\isaacAniTex.png");
    SetName(L"PlayerHead");
    SetScale(fPoint(50, 50));
    CreateAnimator();
    GetAnimator()->CreateAnimation(L"IDLE", m_pImg, fPoint(0.f, 0.f), fPoint(30.88f, 31.6f), fPoint(30.88f, 0.f), 0.5f, 1);
    GetAnimator()->CreateAnimation(L"RIGHT_MOVE", m_pImg, fPoint(30.88f * 2.f, 0.f), fPoint(30.88f, 31.6f), fPoint(30.88f, 0.f), 0.5f, 1);
    GetAnimator()->CreateAnimation(L"LEFT_MOVE", m_pImg, fPoint(30.88f * 6.f, 0.f), fPoint(30.88f, 31.6f), fPoint(30.88f, 0.f), 0.5f, 1);
    GetAnimator()->CreateAnimation(L"UP_MOVE", m_pImg, fPoint(30.88f * 4.f, 0.f), fPoint(30.88f, 31.6f), fPoint(30.88f, 0.f), 0.5f, 2);
    GetAnimator()->CreateAnimation(L"DOWN_MOVE", m_pImg, fPoint(0.f, 0.f), fPoint(30.88f, 31.6f), fPoint(30.88f, 0.f), 0.5f, 1);



    GetAnimator()->CreateAnimation(L"RIGHT_ATTACK", m_pImg, fPoint(30.88f * 2.f, 0.f), fPoint(30.88f, 31.6f), fPoint(30.88f, 0.f), 0.5f, 2);
    GetAnimator()->CreateAnimation(L"LEFT_ATTACK", m_pImg, fPoint(30.88f * 6.f, 0.f), fPoint(30.88f, 31.6f), fPoint(30.88f, 0.f), 0.5f, 2);
    GetAnimator()->CreateAnimation(L"UP_ATTACK", m_pImg, fPoint(30.88f * 4.f, 0.f), fPoint(30.88f, 31.6f), fPoint(30.88f, 0.f), 0.5f, 2);
    GetAnimator()->CreateAnimation(L"DOWN_ATTACK", m_pImg, fPoint(0.f, 0.f), fPoint(30.88f, 31.6f), fPoint(30.88f, 0.f), 0.5f, 2);

   

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

void CPlayerHead::render()
{
    CIsaacPlayer* player = dynamic_cast<CIsaacPlayer*>(GetParentObj());

    if (player->m_isAttacked == false) {
        CCharacter::render();
    }
}

void CPlayerHead::finalupdate()
{
    CCharacter::finalupdate();
}

void CPlayerHead::OnCollision(CCollider* _pOther)
{
    
}

void CPlayerHead::OnCollisionEnter(CCollider* _pOther)
{
   
}

void CPlayerHead::OnCollisionExit(CCollider* _pOther)
{
    
}
