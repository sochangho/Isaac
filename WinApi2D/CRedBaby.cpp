#include "framework.h"
#include "CRedBaby.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CBloodTears.h"
CRedBaby::CRedBaby()
{
    m_pImg = CResourceManager::getInst()->LoadD2DImage(L"playerRedBaby", L"texture\\Animation\\redBaby.png");


    SetName(L"RedBaby");
    SetScale(fPoint(40, 40));
    CreateAnimator();
    GetAnimator()->CreateAnimation(L"IDLE", m_pImg, fPoint(0.f ,0.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.5f, 1);
    GetAnimator()->CreateAnimation(L"RIGHT", m_pImg, fPoint(32.f * 2 , 0.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.5f, 2);
    GetAnimator()->CreateAnimation(L"UP", m_pImg, fPoint(32.f*4, 0.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.5f, 2);
    GetAnimator()->CreateAnimation(L"LEFT", m_pImg, fPoint(32.f*6, 0.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.5f, 2);
    GetAnimator()->CreateAnimation(L"DOWN", m_pImg, fPoint(0.f, 0.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.5f, 2);

    GetAnimator()->Play(L"IDLE");
    
   
   
}

CRedBaby::~CRedBaby()
{
}

CRedBaby* CRedBaby::Clone()
{
    
    return new CRedBaby();
}

void CRedBaby::update()
{
  

    CIsaacPlayer2::update();
    ChangeAnimation(GetPlayer2State());
   GetAnimator()->update();

}

void CRedBaby::render()
{
    component_render();
}

void CRedBaby::ItemUse(fVec2 dir)
{
    fPoint pos = GetPos();

    pos.x += 10 * dir.x;
    pos.y += 10 * dir.y;

    CBloodTears* tears = new CBloodTears;
    tears->SetPos(pos);
    tears->SetDir(dir);

    CreateObj(tears, GROUP_GAMEOBJ::TEARS);
}

void CRedBaby::ChangeAnimation(CIsaacPlayer2::Player2State state)
{
    if (cur_state == state) {
        return;
    }

    cur_state = state;

    switch (cur_state)
    {
   


    case CIsaacPlayer2::Player2State::IDLE: {
        GetAnimator()->Play(L"IDLE");
    }
        break;
    case CIsaacPlayer2::Player2State::UP: {
        GetAnimator()->Play(L"UP");
    }
        break;
    case CIsaacPlayer2::Player2State::DOWN: {
        GetAnimator()->Play(L"DOWN");
    }
        break;
    case CIsaacPlayer2::Player2State::LEFT: {
        GetAnimator()->Play(L"LEFT");
    }
        break;
    case CIsaacPlayer2::Player2State::RIGHT: {
        GetAnimator()->Play(L"RIGHT");
    }
        break;
    default:
        break;
    }



}
