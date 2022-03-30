#include "framework.h"
#include "CRock.h"
#include "CD2DImage.h"
#include "CBombRange.h"
#include "CDestoryRock.h"
#include "CTile.h"
#include "CTileNavMap.h"
#include "CScene.h"
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

        CScene* sceneCur = CSceneManager::getInst()->GetCurScene();
        CTileNavMap* tilemap = sceneCur->GettileNav();

       

        fPoint pos = GetPos();
        fPoint scale = GetScale();
        fPoint p1;
        fPoint p2;

       

        p1.x = (pos.x - scale.x/2)/CTile::SIZE_TILE ;
        p1.y = (pos.y - scale.y/2)/CTile::SIZE_TILE ;

        p2.x = (pos.x + scale.x/2)/CTile::SIZE_TILE ;
        p2.y = (pos.y + scale.y/2)/CTile::SIZE_TILE ;

        int lengthX = p2.x - p1.x;
        int lengthY = p2.y - p1.y;

       
       
        vector<iPoint> points;
        for (int i = p1.x; i <= p1.x + lengthX; i++) {
            for (int j = p1.y; j <= p1.y + lengthY; j++) { 
                points.push_back(iPoint(i, j));
                if (sceneCur->GettileNav() != nullptr) {
                    sceneCur->GettileNav()->AddRoadTile(i, j);
                }
            }
        }
        
       

       
    }

   

}
