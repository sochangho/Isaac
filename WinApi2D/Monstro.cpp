#include "framework.h"
#include "Monstro.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CBloodTears.h";
#include "CCollider.h"

void Monstro::ChangeAnimation(MonstroAnimatonState state, float duration)
{
    if (this->anistate != state) {

        this->anistate = state;
        switch (this->anistate) 
        {
        case MonstroAnimatonState::LEFE_MOVE: {

            GetAnimator()->Play(L"MOVE_LEFT");
        }
        break;
        case MonstroAnimatonState::LEFT_JUMP: {

            GetAnimator()->Play(L"JUMP_LEFT");
        }
        break;
        case MonstroAnimatonState::RIGHT_MOVE: {

            GetAnimator()->Play(L"MOVE_Right");
        }
        break;
        case MonstroAnimatonState::RIGHT_JUMP: {

            GetAnimator()->Play(L"JUMP_Right");
        }
        break;
        case MonstroAnimatonState::ATTACK1_LEFT: {

            GetAnimator()->Play(L"ATTACK1_LEFT");
        }
                                             break;
        case MonstroAnimatonState::ATTACK2_LEFT: {

            GetAnimator()->Play(L"ATTACK2_LEFT");
        }
                                             break;
        case MonstroAnimatonState::ATTACK3_LEFT: {

            GetAnimator()->Play(L"ATTACK3_LEFT");
        }
                                             break;
        case MonstroAnimatonState::ATTACK1_RIGHT: {

            GetAnimator()->Play(L"ATTACK1_RIGHT");
        }
                                             break;
        case MonstroAnimatonState::ATTACK2_RIGHT: {

            GetAnimator()->Play(L"ATTACK2_RIGHT");
        }
                                             break;
        case MonstroAnimatonState::ATTACK3_RIGHT: {

            GetAnimator()->Play(L"ATTACK3_RIGHT");
        }
                                             break;
        case MonstroAnimatonState::TEARS_LEFT: {

            GetAnimator()->Play(L"TEARS_LEFT");
        }
                                                break;
        case MonstroAnimatonState::TEARS_RIGHT: {

            GetAnimator()->Play(L"TEARS_RIGHT");
        }
                                                break;
        }
        




    }
    m_animduration = duration;
    m_anicur = 0;
}

void Monstro::UpdateAniState()
{
    
    if (MonstroState::TRACE == monstroState) {

        MonstroMove();
    }
    else if (MonstroState::ATTACK == monstroState) {

        Attack();
    }
    else if (MonstroState::TREAS_ATTACk == monstroState) {
        TearsAttack();
    }

}

void Monstro::MonstroMove()
{
    fPoint pos = GetPos();
    fPoint playerPos = m_playerObj->GetPos();

    if (!(anistate == MonstroAnimatonState::LEFE_MOVE || anistate == MonstroAnimatonState::RIGHT_MOVE
        || anistate == MonstroAnimatonState::LEFT_JUMP || anistate == MonstroAnimatonState::RIGHT_JUMP)) {

        GetCollider()->SetOffsetPos(fPoint(0, 70));
       
        m_dir = playerPos - pos;
        if (m_dir.x < 0) {
            //哭率
            ChangeAnimation(MonstroAnimatonState::LEFE_MOVE, 0.4f);
        }
        else {
            //坷弗率
            ChangeAnimation(MonstroAnimatonState::RIGHT_MOVE, 0.4f);
        }


    }



    if (anistate == MonstroAnimatonState::LEFE_MOVE || anistate == MonstroAnimatonState::RIGHT_MOVE) {

        if (m_anicur < m_animduration) {
            m_anicur += fDT;
        }
        else {

            
            GetCollider()->SetOffsetPos(fPoint(0, 20));

            if (m_dir.x < 0) {
                //哭率
                ChangeAnimation(MonstroAnimatonState::LEFT_JUMP, 3.f);
            }
            else {
                //坷弗率
                ChangeAnimation(MonstroAnimatonState::RIGHT_JUMP, 3.f);
            }



        }


    }
    else if (anistate == MonstroAnimatonState::LEFT_JUMP || anistate == MonstroAnimatonState::RIGHT_JUMP) {

        if (m_anicur < m_animduration) {
            m_anicur += fDT;


            pos.x += m_dir.normalize().x * 30 * fDT;
            pos.y += m_dir.normalize().y * 30 * fDT;

            SetPos(pos);
        }
        else {
            monstroState = MonstroState::NONE;
            GetCollider()->SetOffsetPos(fPoint(0, 70));
            if (m_dir.x < 0) {
                //哭率
                ChangeAnimation(MonstroAnimatonState::NONE_RIGHT, 1.f);
            }
            else {
                //坷弗率
                ChangeAnimation(MonstroAnimatonState::NONE_LEFT, 1.f);
            }

            
        }
    }
}

void Monstro::Attack()
{
    fPoint pos = GetPos();
    fPoint playerPos = m_playerObj->GetPos();
  
    if (!(anistate == MonstroAnimatonState::ATTACK1_RIGHT || anistate == MonstroAnimatonState::ATTACK2_RIGHT
        || anistate == MonstroAnimatonState::ATTACK3_RIGHT || anistate == MonstroAnimatonState::ATTACK1_LEFT
        || anistate == MonstroAnimatonState::ATTACK2_LEFT
        || anistate == MonstroAnimatonState::ATTACK3_LEFT)) {

        m_dir = playerPos - pos;
        if (m_dir.x > 0) {

            ChangeAnimation(MonstroAnimatonState::ATTACK1_RIGHT, 0.4f);

        }
        else {

            ChangeAnimation(MonstroAnimatonState::ATTACK1_LEFT, 0.4f);
        }

    }


    if (anistate == MonstroAnimatonState::ATTACK1_RIGHT || anistate == MonstroAnimatonState::ATTACK1_LEFT) {

        if (m_anicur < m_animduration) {
            m_anicur += fDT;
        }
        else {

            m_playerPos = m_playerObj->GetPos();
            if (m_dir.x > 0) {

                ChangeAnimation(MonstroAnimatonState::ATTACK2_RIGHT, 1.f);

            }
            else {

                ChangeAnimation(MonstroAnimatonState::ATTACK2_LEFT, 1.f);
            }
        }

    }


    if (anistate == MonstroAnimatonState::ATTACK2_RIGHT || anistate == MonstroAnimatonState::ATTACK2_LEFT) {

        if (m_anicur < m_animduration) {
            m_anicur += fDT;
            
            fPoint pos = GetPos();
            pos.y -= 1500.f * fDT;
            SetPos(pos);
        }
        else {
            fPoint pos = GetPos();
            pos.x = m_playerPos.x;
            SetPos(pos);
            if (m_dir.x > 0) {

                ChangeAnimation(MonstroAnimatonState::ATTACK3_RIGHT, 2.f);

            }
            else {

                ChangeAnimation(MonstroAnimatonState::ATTACK3_LEFT, 2.f);
            }
        }

    }


    if (anistate == MonstroAnimatonState::ATTACK3_RIGHT || anistate == MonstroAnimatonState::ATTACK3_LEFT) {

        fPoint pos = GetPos();
        if (abs(pos.y - m_playerPos.y) > 10.f ) {
            m_anicur += fDT;
            pos.y += 1000.f * fDT;
            SetPos(pos);

        }
        else {
            pos.y = m_playerPos.y - 40;
            SetPos(pos);

            monstroState = MonstroState::NONE;
            if (m_dir.x > 0) {

                ChangeAnimation(MonstroAnimatonState::NONE_RIGHT, 1.f);
                

            }
            else {

                ChangeAnimation(MonstroAnimatonState::NONE_LEFT, 1.f);
            }
        }

    }


}

void Monstro::TearsAttack()
{
    fPoint pos = GetPos();
    fPoint playerPos = m_playerObj->GetPos();
    float theta;
    float min;
    float max;
    if (!(anistate == MonstroAnimatonState::TEARS_LEFT || anistate == MonstroAnimatonState::TEARS_RIGHT)) {
        GetCollider()->SetOffsetPos(fPoint(0, 70));

        m_dir = playerPos - pos;
  

        if (m_dir.x > 0) {

            ChangeAnimation(MonstroAnimatonState::TEARS_RIGHT, 1.8f);

        }
        else {

            ChangeAnimation(MonstroAnimatonState::TEARS_LEFT,  1.8f);
        }

    }

    if (anistate == MonstroAnimatonState::TEARS_RIGHT || anistate == MonstroAnimatonState::TEARS_LEFT) {

      
        if (m_anicur < m_animduration) {
            m_anicur += fDT;
          
            if (m_anicur > 0.75f && !is_tearsAttack) {

                is_tearsAttack = true;
                is_animationStop = true;
                
                for (int i = 0; i < 10; i++) {


                    m_dir = playerPos - pos;
                    fPoint rightVec = fPoint(1, 0);
                    theta = m_dir.normalize().x * rightVec.x + m_dir.normalize().y * rightVec.y;
                    theta = acos(theta) * 180.f / 3.141592f;

                    
                    CreateRandomTearsAttack(m_dir , theta);

                }


            }
           
        }
        else {
          
            is_tearsAttack = false;
            is_animationStop = false;
            monstroState = MonstroState::NONE;
            if (m_dir.x > 0) {

                ChangeAnimation(MonstroAnimatonState::NONE_RIGHT, 1.8f);


            }
            else {

                ChangeAnimation(MonstroAnimatonState::NONE_LEFT, 1.8f);
            }
        }

    }





}

void Monstro::CreateRandomTearsAttack(fPoint dir , float theta)
{
    
    CBloodTears* bloodTeas = new CBloodTears;
    bloodTeas->type = CDefaultTears::AttackType::PLAYER;
    fPoint pos = GetPos();
    
   

 
      random_device rd;
      mt19937_64 gen(rd());
      uniform_int_distribution<int> angle(0, 20);
      uniform_int_distribution<int> vel(100, 400);

      

      fVec2 fvDir = dir;

      fvDir.x += (float)cos(angle(gen));
      fvDir.y += (float)sin(angle(gen));

     
      bloodTeas->SetPos(pos);
      bloodTeas->SetDir(fvDir.normalize());
      CreateObj(bloodTeas, GROUP_GAMEOBJ::TEARS);
      bloodTeas->SetVelocity(vel(gen));
      bloodTeas->SetSecend(1.2f, 0.8f);

}

Monstro::Monstro()
{
    m_pImg = CResourceManager::getInst()->LoadD2DImage(L"Mostro", L"texture\\Animation\\boss_004_monstro.png");
    CreateAnimator();

  

   

    GetAnimator()->CreateAnimation(L"MOVE_LEFT", m_pImg, fPoint(0.f, 112.f ), fPoint(80.f, 112.f), fPoint(80.f, 0.f), 0.2f, 2);
    GetAnimator()->CreateAnimation(L"JUMP_LEFT", m_pImg, fPoint(80.f * 2, 112.f), fPoint(80.f, 112.f), fPoint(80.f, 0.f), 0.1f, 1);  
    GetAnimator()->CreateAnimation(L"MOVE_Right", m_pImg, fPoint(0.f, 112.f), fPoint(80.f, 112.f), fPoint(80.f, 0.f), 0.2f, 2 , true);
    GetAnimator()->CreateAnimation(L"JUMP_Right", m_pImg, fPoint(80.f * 2, 112.f), fPoint(80.f, 112.f), fPoint(80.f, 0.f), 0.1f, 1 , true);

    GetAnimator()->FindAnimation(L"JUMP_LEFT")->GetFrame(0).fptOffset = fPoint(0, -30);
    GetAnimator()->FindAnimation(L"JUMP_Right")->GetFrame(0).fptOffset = fPoint(0, -30);

    
    GetAnimator()->CreateAnimation(L"ATTACK1_LEFT", m_pImg, fPoint(0.f, 0.f), fPoint(80.f, 112.f), fPoint(80.f, 0.f), 0.2f, 4);
    GetAnimator()->CreateAnimation(L"ATTACK1_RIGHT", m_pImg, fPoint(0.f, 0.f), fPoint(80.f, 112.f), fPoint(80.f, 0.f), 0.2f, 4,true);

    GetAnimator()->CreateAnimation(L"ATTACK2_LEFT", m_pImg, fPoint(80.f*4, 0.f), fPoint(80.f, 112.f), fPoint(80.f, 0.f), 0.1f, 1);
    GetAnimator()->CreateAnimation(L"ATTACK2_RIGHT", m_pImg, fPoint(80.f*4, 0.f), fPoint(80.f, 112.f), fPoint(80.f, 0.f), 0.1f, 1, true);

    GetAnimator()->CreateAnimation(L"ATTACK3_LEFT", m_pImg, fPoint(0.f, 112.f), fPoint(80.f, 112.f), fPoint(80.f, 0.f), 0.1f, 1);
    GetAnimator()->CreateAnimation(L"ATTACK3_RIGHT", m_pImg, fPoint(0.f, 112.f), fPoint(80.f, 112.f), fPoint(80.f, 0.f), 0.1f, 1, true);

    
    GetAnimator()->CreateAnimation(L"NONE_LEFT", m_pImg, fPoint(80.f * 3, 112.f), fPoint(80.f, 112.f), fPoint(80.f, 0.f), 0.1f, 1);
    GetAnimator()->CreateAnimation(L"NONE_RIGHT", m_pImg, fPoint(80.f * 3, 112.f), fPoint(80.f, 112.f), fPoint(80.f, 0.f), 0.1f, 1, true);


    GetAnimator()->CreateAnimation(L"TEARS_LEFT", m_pImg, fPoint(0.f, 0.f), fPoint(80.f, 112.f), fPoint(80.f, 0.f), 0.2f, 4);
   
    GetAnimator()->CreateAnimation(L"TEARS_RIGHT", m_pImg, fPoint(0.f, 0.f), fPoint(80.f, 112.f), fPoint(80.f, 0.f), 0.2f, 4, true);
    
    
   
  
    SetScale(fPoint(150, 200));
    CreateCollider();
    GetCollider()->SetScale(fPoint(120, 100));
    GetCollider()->SetOffsetPos(fPoint(0, 70));

    m_maxHp = 500;
    m_hp = m_maxHp;

   const vector<CGameObject*>& playerobjects = CSceneManager::getInst()->GetCurScene()->GetGroupObject(GROUP_GAMEOBJ::PLAYER);

   for (int i = 0; i < playerobjects.size(); i++) {
       CIsaacPlayer* player = dynamic_cast<CIsaacPlayer*>(playerobjects[i]);
       if (player != nullptr) {

           m_playerObj = player;
           break;
       }
   }



}

Monstro::~Monstro()
{
    m_playerObj = nullptr;    
   

}

Monstro* Monstro::Clone()
{
    return new Monstro(*this);
}

void Monstro::update()
{
    CMonster::update();

  

    if (monstroState == MonstroState::NONE) {

        random_device rd;
        mt19937_64 gen(rd());
        uniform_int_distribution<int> dis(0, 2);

      if (dis(gen) == 0) {

            monstroState = MonstroState::TREAS_ATTACk;
      }
      else if (dis(gen) == 1) {

          monstroState = MonstroState::ATTACK;
      }
      else if (dis(gen) == 2) {

          monstroState = MonstroState::TRACE;
      }
      

    }
   

    UpdateAniState();

    if (!is_animationStop) {

        GetAnimator()->update();
    }
}

void Monstro::render()
{
    component_render();
   
}

void Monstro::finalupdate()
{
    CMonster::finalupdate();
}
