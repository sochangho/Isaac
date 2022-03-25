
#include "framework.h"
#include "CDropLilloki.h"
#include "CCollider.h"
#include "CIsaacPlayer.h"
#include "CLilloki.h"
CDropLilloki::CDropLilloki()
{
    m_Img = CResourceManager::getInst()
        ->LoadD2DImage(L"lilLoki", L"texture\\Animation\\lilloki.png");
    SetName(L"RedBaby");
    SetScale(fPoint(50, 40));
    CreateCollider();
    GetCollider()->SetScale(fPoint(30, 30));
}

CDropLilloki::~CDropLilloki()
{
}

CDropLilloki* CDropLilloki::Clone()
{
    return nullptr;
}

void CDropLilloki::update()
{
}

void CDropLilloki::render()
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
        pos.x - scale.x / 2,
        pos.y - scale.y / 2,
        pos.x + scale.x / 2,
        pos.y + scale.y / 2
    );
    component_render();
}

void CDropLilloki::OnCollision(CCollider* pOther)
{
}

void CDropLilloki::OnCollisionEnter(CCollider* pOther)
{
    CIsaacPlayer* player = dynamic_cast<CIsaacPlayer*>(pOther->GetObj());

    if (player != nullptr) {

        player->SetItem(new CLilloki);
        DeleteObj(this);
    }


}

void CDropLilloki::OnCollisionExit(CCollider* pOther)
{
}
