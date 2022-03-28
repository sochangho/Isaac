#include "framework.h"
#include "CRock.h"
#include "CD2DImage.h"
#include "CBombRange.h"
#include "CDestoryRock.h"
CRock::CRock()
{
    m_pImg = CResourceManager::getInst()->LoadD2DImage(L"Rock", L"texture\\map\\rocks_basement.png");
    SetScale(fPoint(60, 60));
    CreateCollider();
    GetCollider()->SetScale(fPoint(50, 50));
}

CRock::~CRock()
{
}

CRock* CRock::Clone()
{
    return nullptr;
}

void CRock::update()
{
}

void CRock::render()
{
    if (nullptr == m_pImg)
    {
        return;
    }
    fPoint pos = GetPos();
    fPoint scale = GetScale();
    fPoint renderPos = CCameraManager::getInst()->GetRenderPos(pos);
    

    CRenderManager::getInst()->RenderFrame(
        m_pImg,
        renderPos.x - scale.x / 2,
        renderPos.y - scale.y / 2,
        renderPos.x + scale.x / 2,
        renderPos.y + scale.y / 2, startX, startY, endX, endY
    );
    component_render();

}

void CRock::SetFrame(int x, int y, int w, int h)
{
    startX = x;
    startY = y;
    endX = w;
    endY = h;
}

RockFrame CRock::GetFrame()
{
    RockFrame rockFrame;
    rockFrame.startX = startX;
    rockFrame.startY = startY;
    rockFrame.endX = endX;
    rockFrame.endY = endY;

    return rockFrame;
}

void CRock::OnCollisionEnter(CCollider* _pOther)
{
    CBombRange* range = dynamic_cast<CBombRange*>(_pOther->GetObj());
    
    if (range != nullptr) {

        DeleteObj(this);
        CDestoryRock* rock = new CDestoryRock;
        rock->SetPos(GetPos());
        CreateObj(rock, GROUP_GAMEOBJ::ROCK);
   }


}
