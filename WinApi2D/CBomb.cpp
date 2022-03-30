#include "framework.h"
#include "CBomb.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CScaleAnimation.h"
#include "CBombEffect.h"
#include "CIsaacPlayer.h"
#include "CBombRange.h"
CBomb::CBomb()
{
    m_pImg = CResourceManager::getInst()
        ->LoadD2DImage(L"Bomb", L"texture\\Animation\\bombs.png");
    SetName(L"Bomb");

    SetScale(fPoint(40, 40));
    CreateAnimator();
    GetAnimator()->CreateAnimation(L"IDLE", m_pImg, fPoint(0.f, 0.f), fPoint(32.5f, 32.5f), fPoint(32.5f, 0.f), 2.f, 1);
    GetAnimator()->Play(L"IDLE");

    CreateCollider();
    GetCollider()->SetScale(fPoint(25, 25));


    scaleAnimation = new CScaleAnimation;
    scaleAnimation->ScaleInit(35.f, 45.f, 30.f, 29.f);
    scaleAnimation->ScaleInit(45.f, 35.f, 30.f, 30.f);
}

CBomb::~CBomb()
{
    CSoundManager::getInst()->Play(L"Bomb");
}

CBomb* CBomb::Clone()
{
    return new CBomb(*this);
}

void CBomb::update()
{


    Explosion();


    CDropItem::update();

    if (scaleAnimation != nullptr) {
        scaleAnimation->ScaleAnimationUpate(this);
    }
    GetAnimator()->update();
}

void CBomb::render()
{
    component_render();
}

void CBomb::Explosion()
{

    if (m_curTime < m_duration) {

        m_curTime += fDT;

    }
    else {

        m_curTime = 0.f;
        //터짐 이펙트 생성
        CBombEffect* effect = new CBombEffect;
        effect->SetPos(GetPos());
        CreateObj(effect, GROUP_GAMEOBJ::EFFECT);


        //Collider가지는 오브젝트 생성 및 안에 있는 콜리더 데미지  

        CBombRange* range = new CBombRange;
        range->SetPos(GetPos());
        CreateObj(range, GROUP_GAMEOBJ::ATTACKRANGE);
        //이 오브젝트 삭제
        DeleteObj(this);
    }


}



