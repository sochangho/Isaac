#include "framework.h"
#include "CDropItem.h"
#include "CTile.h"
#include "CIsaacPlayer.h"
#include "CCollider.h"
CDropItem::CDropItem()
{
}

CDropItem::~CDropItem()
{
}

CDropItem* CDropItem::Clone()
{
    return new CDropItem(*this);
}

void CDropItem::update()
{

    if (m_isPlayerCol) {

        if (m_adCurTime < m_adDuration) {

            m_adCurTime += fDT;
            m_velocity += 50.f * fDT;
        }
        else {

            m_velocity -= 50.f * fDT;

            if (m_velocity < 0.f) {

                m_velocity = 0.f;
                m_adCurTime = 0.f;
                m_isPlayerCol = false;

            }

        }

    }



    fPoint pos = GetPos();
    pos.x += m_dir.normalize().x * m_velocity * fDT;
    pos.y += m_dir.normalize().y * m_velocity * fDT;
    SetPos(pos);

}

void CDropItem::render()
{
}

void CDropItem::OnCollision(CCollider* pOther)
{

    CTile* tile = dynamic_cast<CTile*>(pOther->GetObj());

    if (tile != nullptr && tile->GetGroup() == GROUP_TILE::WALL) {

        fPoint thisPos = GetPos();
        fPoint tilePos = pOther->GetObj()->GetPos();

        m_dir.x = thisPos.x - tilePos.x;
        m_dir.y = thisPos.y - tilePos.y;
    }
}

void CDropItem::OnCollisionEnter(CCollider* pOther)
{

    CIsaacPlayer* isaac = dynamic_cast<CIsaacPlayer*>(pOther->GetObj());

    if (isaac != nullptr) {

        fPoint thisPos = GetPos();
        fPoint playerPos = pOther->GetObj()->GetPos();

        m_velocity = isaac->GetVelocity();
        m_dir.x = thisPos.x - playerPos.x;
        m_dir.y = thisPos.y - playerPos.y;
        m_adCurTime = 0.f;
        m_isPlayerCol = true;

    }
}

void CDropItem::OnCollisionExit(CCollider* pOther)
{
}