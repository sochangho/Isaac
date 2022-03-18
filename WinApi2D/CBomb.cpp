#include "framework.h"
#include "CBomb.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CScaleAnimation.h"
#include "CBombEffect.h"
#include "CIsaacPlayer.h"
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
}

CBomb* CBomb::Clone()
{
    return new CBomb(*this);
}

void CBomb::update()
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
        //
        //
        
        
        //이 오브젝트 삭제
        DeleteObj(this);
    }

    if (m_isPlayerCol) {

        if (m_adCurTime < m_adDuration) {

            m_adCurTime += fDT;
            m_velocity += 300.f * fDT;
        }
        else {

            m_velocity -= 200.f * fDT;
           
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

    if (scaleAnimation != nullptr) {
        scaleAnimation->ScaleAnimationUpate(this);
    }
    GetAnimator()->update();
}

void CBomb::render()
{
    component_render();
}


void CBomb::OnCollision(CCollider* pOther)
{
   
    CTile* tile = dynamic_cast<CTile*>(pOther->GetObj());

    if (tile != nullptr  && tile->GetGroup() == GROUP_TILE::WALL) {

        fPoint thisPos = GetPos();
        fPoint tilePos = pOther->GetObj()->GetPos();

        m_dir.x = thisPos.x - tilePos.x;
        m_dir.y = thisPos.y - tilePos.y;
    }

}

void CBomb::OnCollisionEnter(CCollider* pOther)
{

   
    if (pOther->GetObj()->GetName() == L"PlayerBody" ) {

        fPoint thisPos = GetPos();
        fPoint playerPos =pOther->GetObj()->GetPos();

        CPlayerBody* isaacBody = dynamic_cast<CPlayerBody*>(pOther->GetObj());
        CIsaacPlayer* isaac = dynamic_cast<CIsaacPlayer*>(isaacBody->GetParentObj());        
        m_velocity = isaac->GetVelocity();
        m_dir.x = thisPos.x - playerPos.x;
        m_dir.y = thisPos.y - playerPos.y;
        m_adCurTime = 0.f;
        m_isPlayerCol = true;

    }
}

void CBomb::OnCollisionExit(CCollider* pOther)
{

}


