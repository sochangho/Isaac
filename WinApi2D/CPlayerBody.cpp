#include "framework.h"
#include "CPlayerBody.h"
#include "CCharacter.h"
#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CIsaacPlayer.h"
#include "CTile.h"
CPlayerBody::CPlayerBody()
{
    m_pImg = CResourceManager::getInst()->
        LoadD2DImage(L"PlayerBody", L"texture\\Animation\\isaacAniTex.png");
    
    SetName(L"PlayerBody");
    SetScale(fPoint(50 , 50));
    CreateAnimator();
    GetAnimator()->CreateAnimation(L"IDLE", m_pImg, fPoint(0.f, 31.6f), fPoint(28.37f, 31.6f), fPoint(28.37f, 0.f), 0.5f, 1);
    GetAnimator()->CreateAnimation(L"RIGHT_MOVE", m_pImg, fPoint(0.f , 31.6f * 2.f), fPoint(28.37f, 31.6f), fPoint(28.37f, 0.f), 0.1f, 10);
    GetAnimator()->CreateAnimation(L"LEFT_MOVE", m_pImg, fPoint(0.f , 31.6f * 3.f), fPoint(28.37f, 31.6f), fPoint(28.37f, 0.f), 0.1f, 10);
    GetAnimator()->CreateAnimation(L"UP_MOVE", m_pImg, fPoint(28.37f * 5.f , 31.6f), fPoint(28.37f, 31.6f), fPoint(28.37f, 0.f), 0.1f, 5);
    GetAnimator()->CreateAnimation(L"DOWN_MOVE", m_pImg, fPoint(0.f, 31.6f), fPoint(28.37f, 31.6f), fPoint(28.37f, 0.f), 0.1f, 5);

    GetAnimator()->Play(L"IDLE");

    CreateCollider();
    GetCollider()->SetScale(fPoint(20, 20));
    GetCollider()->SetOffsetPos(fPoint(0, -10));
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

void CPlayerBody::render()
{
    CCharacter::render();
  
}

void CPlayerBody::finalupdate()
{
    CCharacter::finalupdate();
}

void CPlayerBody::OnCollision(CCollider* _pOther)
{
    CIsaacPlayer* issac = dynamic_cast<CIsaacPlayer*>(GetParentObj());
    CTile* tile = dynamic_cast<CTile*>(_pOther->GetObj());

    if (tile != nullptr && issac != nullptr && tile->GetGroup() == GROUP_TILE::WALL) {

        issac->m_dirVec2.y = -1;

    }
}

void CPlayerBody::OnCollisionEnter(CCollider* _pOther)
{
    CIsaacPlayer* issac = dynamic_cast<CIsaacPlayer*>(GetParentObj());
    CTile* tile = dynamic_cast<CTile*>(_pOther->GetObj());

    if (tile != nullptr && issac != nullptr && tile->GetGroup() == GROUP_TILE::WALL) {

        issac->m_isColCheck = true;
       
    }
}

void CPlayerBody::OnCollisionExit(CCollider* _pOther)
{
    CIsaacPlayer* issac = dynamic_cast<CIsaacPlayer*>(GetParentObj());
    CTile* tile = dynamic_cast<CTile*>(_pOther->GetObj());

    if (tile != nullptr && issac != nullptr && tile->GetGroup() == GROUP_TILE::WALL) {

        issac->m_isColCheck = false;
        issac->m_veclocity = 0;
    }
}
