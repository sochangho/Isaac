#include "framework.h"
#include "CPlayerRight.h"
#include "CTile.h"
#include "CIsaacPlayer.h"
#include "CCollider.h"
CPlayerRight::CPlayerRight()
{
    CreateCollider();
    GetCollider()->SetScale(fPoint(5, 30));
    GetCollider()->SetOffsetPos(fPoint(0, -15));
}

CPlayerRight::~CPlayerRight()
{
   
}

CPlayerRight* CPlayerRight::Clone()
{
    return new CPlayerRight(*this);
}

void CPlayerRight::update()
{
    CCharacter::update();
}

void CPlayerRight::render()
{
    CCharacter::render();
}

void CPlayerRight::finalupdate()
{
    CCharacter::finalupdate();
}

void CPlayerRight::OnCollision(CCollider* _pOther)
{
    CIsaacPlayer* issac = dynamic_cast<CIsaacPlayer*>(GetParentObj());
    CTile* tile = dynamic_cast<CTile*>(_pOther->GetObj());

    if (tile != nullptr && issac != nullptr && tile->GetGroup() == GROUP_TILE::WALL) {

        issac->m_dirVec2.x = -1;

    }

}

void CPlayerRight::OnCollisionEnter(CCollider* _pOther)
{
    CIsaacPlayer* issac = dynamic_cast<CIsaacPlayer*>(GetParentObj());
    CTile* tile = dynamic_cast<CTile*>(_pOther->GetObj());

    if (tile != nullptr && issac != nullptr && tile->GetGroup() == GROUP_TILE::WALL) {

        issac->m_isColCheck = true;
       
    }
}

void CPlayerRight::OnCollisionExit(CCollider* _pOther)
{
    CIsaacPlayer* issac = dynamic_cast<CIsaacPlayer*>(GetParentObj());
    CTile* tile = dynamic_cast<CTile*>(_pOther->GetObj());

    if (tile != nullptr && issac != nullptr && tile->GetGroup() == GROUP_TILE::WALL) {

        issac->m_isColCheck = false;
        issac->m_veclocity = 0;
    }
}
