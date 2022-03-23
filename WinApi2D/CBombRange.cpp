#include "framework.h"

#include "CBombRange.h"
#include "CCollider.h"
CBombRange::CBombRange()
{
    m_duration = 0.1f;
    m_cur = 0.f;
    CreateCollider();
    GetCollider()->SetScale(fPoint(100, 100));
}

CBombRange::~CBombRange()
{
}

CBombRange* CBombRange::Clone()
{
    return new CBombRange(*this);
}

void CBombRange::update()
{
    if(m_cur < m_duration){
    
        m_cur += fDT;
    
    }
    else {

        DeleteObj(this);

    }

    
}

void CBombRange::render()
{
    CGameObject::render();
}

void CBombRange::finalupdate()
{
    CGameObject::finalupdate();
}
