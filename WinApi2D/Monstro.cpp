#include "framework.h"
#include "Monstro.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CBloodTears.h";
#include "CCollider.h"

Monstro::Monstro()
{
    m_pImg = CResourceManager::getInst()->LoadD2DImage(L"Mostro", L"texture\\Animation\\boss_004_monstro.png");
    CreateAnimator();

  

    GetAnimator()->CreateAnimation(L"TEARS_LEFT", m_pImg, fPoint(0.f, 0.f), fPoint(80.f, 112.f), fPoint(80.f, 0.f), 0.2f, 4);
    GetAnimator()->CreateAnimation(L"TEARS_RIGHT", m_pImg, fPoint(0.f, 0.f), fPoint(80.f, 112.f), fPoint(80.f, 0.f), 0.2f, 4, true);


    GetAnimator()->CreateAnimation(L"UP", m_pImg, fPoint(80.f * 4, 0.f), fPoint(80.f, 112.f), fPoint(80.f, 0.f), 0.2f, 1);
    GetAnimator()->CreateAnimation(L"DOWN", m_pImg, fPoint(0.f, 112.f), fPoint(80.f, 112.f), fPoint(80.f, 0.f), 0.2f, 1);

   

    GetAnimator()->CreateAnimation(L"MOVE_LEFT", m_pImg, fPoint(0.f, 112.f ), fPoint(80.f, 112.f), fPoint(80.f, 0.f), 0.1f, 2);
    GetAnimator()->CreateAnimation(L"JUMP_LEFT", m_pImg, fPoint(80.f * 2, 112.f), fPoint(80.f, 112.f), fPoint(80.f, 0.f), 0.1f, 1);
    
    
   
    



    
    GetAnimator()->Play(L"MOVE_LEFT");

    SetScale(fPoint(150, 200));
    CreateCollider();
    GetCollider()->SetScale(fPoint(120, 100));
    GetCollider()->SetOffsetPos(fPoint(0, 70));

}

Monstro::~Monstro()
{
}

Monstro* Monstro::Clone()
{
    return new Monstro(*this);
}

void Monstro::update()
{
    CMonster::update();
    GetAnimator()->update();
}

void Monstro::render()
{
    component_render();
}

void Monstro::finalupdate()
{
    CMonster::finalupdate();
}
