#include "framework.h"
#include "CPlayerLeft.h"
#include "CTile.h"
#include "CIsaacPlayer.h"
#include "CCollider.h"
CPlayerLeft::CPlayerLeft()
{
    CreateCollider();
    GetCollider()->SetScale(fPoint(5, 30));
    GetCollider()->SetOffsetPos(fPoint(0, -15));
   
}

CPlayerLeft::~CPlayerLeft()
{
}

CPlayerLeft* CPlayerLeft::Clone()
{
    return new CPlayerLeft(*this);
}

void CPlayerLeft::update()
{
    CCharacter::update();
}

void CPlayerLeft::render()
{
    CCharacter::render();
}

void CPlayerLeft::finalupdate()
{
    CCharacter::finalupdate();
}

void CPlayerLeft::OnCollision(CCollider* _pOther)
{
    CIsaacPlayer* issac = dynamic_cast<CIsaacPlayer*>(GetParentObj());
    CTile* tile = dynamic_cast<CTile*>(_pOther->GetObj());

    if (tile != nullptr && issac != nullptr && tile->GetGroup() == GROUP_TILE::WALL) {

        issac->m_dirVec2.x = 1;

    }

}

void CPlayerLeft::OnCollisionEnter(CCollider* _pOther)
{
    CIsaacPlayer* issac = dynamic_cast<CIsaacPlayer*>(GetParentObj());
    CTile* tile = dynamic_cast<CTile*>(_pOther->GetObj());

    if (tile != nullptr && issac != nullptr && tile->GetGroup() == GROUP_TILE::WALL) {

        issac->m_isColCheck = true;
        
    }


}

void CPlayerLeft::OnCollisionExit(CCollider* _pOther)
{
    CIsaacPlayer* issac = dynamic_cast<CIsaacPlayer*>(GetParentObj());
    CTile* tile = dynamic_cast<CTile*>(_pOther->GetObj());

    if (tile != nullptr && issac != nullptr && tile->GetGroup() == GROUP_TILE::WALL) {

        issac->m_isColCheck = false;
        issac->m_veclocity = 0;
    }
}
