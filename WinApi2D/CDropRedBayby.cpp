#include "framework.h"
#include "CDropRedBayby.h"
#include "CCollider.h"
#include "CIsaacPlayer.h"
#include "CRedBaby.h"
CDropRedBayby::CDropRedBayby()
{
    m_Img = CResourceManager::getInst()
        ->LoadD2DImage(L"RedBaby", L"texture\\Animation\\collectibles_096_littlechad.png");
    SetName(L"RedBaby");
    SetScale(fPoint(50, 50));
    CreateCollider();
    GetCollider()->SetScale(fPoint(30, 30));


}

CDropRedBayby::~CDropRedBayby()
{
}

CDropRedBayby* CDropRedBayby::Clone()
{
    return new CDropRedBayby(*this);
}

void CDropRedBayby::update()
{
}

void CDropRedBayby::render()
{
    if (nullptr == m_Img)
    {
        return;
    }
    fPoint pos = GetPos();
    fPoint scale = GetScale();
    pos = CCameraManager::getInst()->GetRenderPos(pos);

    CRenderManager::getInst()->RenderImage(
        m_Img,
        pos.x - scale.x/2,
        pos.y - scale.y/2,
        pos.x + scale.x/2,
        pos.y + scale.y/2
    );
    component_render();
}

void CDropRedBayby::OnCollision(CCollider* pOther)
{
}

void CDropRedBayby::OnCollisionEnter(CCollider* pOther)
{
    CIsaacPlayer* player = dynamic_cast<CIsaacPlayer*>(pOther->GetObj());
    


    if (player != nullptr) {       
        CRedBaby* redbaby = new CRedBaby;
        player->AddPet(redbaby);
        DeleteObj(this);
    }

    
    

}

void CDropRedBayby::OnCollisionExit(CCollider* pOther)
{
}
