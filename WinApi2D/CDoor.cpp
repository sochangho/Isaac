#include "framework.h"
#include "CDoor.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CIsaacPlayer.h"
#include "CScene.h"
CDoor::CDoor()
{
    m_Img = nullptr;
    SetScale(fPoint(100, 100));
    CreateCollider();
    GetCollider()->SetScale(fPoint(80, 80));
}


CDoor::~CDoor()
{
   
}

void CDoor::Load(DOOR_DIR doorDir , GROUP_SCENE scene)
{
    LoadDoor(doorDir, scene);

    CreateAnimator();
    GetAnimator()->CreateAnimation(L"OPEN", m_Img, fPoint(0.f, 0.f), fPoint(64.f, 48.f), fPoint(64.f, 0.f), 0.1f, 1);
    GetAnimator()->CreateAnimation(L"GoClose", m_Img, fPoint(0.f, 0.f), fPoint(64.f, 48.f), fPoint(64.f, 0.f), 0.1f, 2);
    GetAnimator()->FindAnimation(L"GoClose")->Create(m_Img, fPoint(0.f, 48.f), fPoint(64.f, 48.f), fPoint(64.f, 0.f), 0.1f, 2);
    GetAnimator()->CreateAnimation(L"GoOpen", m_Img, fPoint(0.f, 48.f * 2), fPoint(64.f, 48.f), fPoint(64.f, 0.f), 0.1f, 2);
    GetAnimator()->FindAnimation(L"GoOpen")->Create(m_Img, fPoint(0.f, 48.f * 3), fPoint(64.f, 48.f), fPoint(64.f, 0.f), 0.1f, 2);

    GetAnimator()->CreateAnimation(L"CLOSE", m_Img, fPoint(64.f, 48.f), fPoint(64.f, 48.f), fPoint(64.f, 0.f), 0.1f, 1);

    m_doorstate = DOOR_STATE::Open;
    GetAnimator()->Play(L"OPEN");


}
void CDoor::LoadDoor(DOOR_DIR doorDir, GROUP_SCENE scene) {


    goScene = scene;
    m_doorDir = doorDir;
    switch (m_doorDir)
    {
    case DOOR_DIR::UP: {
        m_Img = CResourceManager::getInst()->LoadD2DImage(L"DoorUp", L"texture\\Animation\\NomalDoorUp.png");
    }
                     break;
    case DOOR_DIR::DOWN: {
        m_Img = CResourceManager::getInst()->LoadD2DImage(L"DoorDown", L"texture\\Animation\\NomalDoorDown.png");
    }
                       break;
    case DOOR_DIR::LEFT: {
        m_Img = CResourceManager::getInst()->LoadD2DImage(L"DoorLeft", L"texture\\Animation\\NomalDoorLeft.png");
    }
                       break;
    case DOOR_DIR::RIGHT: {
        m_Img = CResourceManager::getInst()->LoadD2DImage(L"DoorRight", L"texture\\Animation\\NomalDoorRight.png");
    }
                        break;
    default:
        break;
    }

}

CDoor* CDoor::Clone()
{
    
    return new CDoor(*this);
}

void CDoor::update()
{
    bool sceneClear = CSceneManager::getInst()->GetCurScene()->GetCrear();

    if (!sceneClear) {

        if (m_doorstate == DOOR_STATE::Open) {
            CSoundManager::getInst()->Play(L"Door_Open");
            ChangeDoorState(DOOR_STATE::GO_CLOSE);
        }
        else if (m_doorstate == DOOR_STATE::GO_CLOSE) {

            if (m_doorT < 0.38f) {

                m_doorT += fDT;
            }
            else {
                m_doorT = 0;
                ChangeDoorState(DOOR_STATE::CLOSE);
                CSoundManager::getInst()->Play(L"Door_Close");
            }

        }
    }
    else {


        if (m_doorstate == DOOR_STATE::CLOSE) {
            
            ChangeDoorState(DOOR_STATE::GO_OPEN);
        }
        else if (m_doorstate == DOOR_STATE::GO_OPEN) {

            if (m_doorT < 0.38f) {

                m_doorT += fDT;
            }
            else {
                m_doorT = 0;
                ChangeDoorState(DOOR_STATE::Open);
                CSoundManager::getInst()->Play(L"Door_Open");
            }

        }


    }



    if (GetAnimator() == nullptr) {

        return;
    }


    GetAnimator()->update();
}

void CDoor::render()
{
    if (nullptr == m_Img)
    {
        return;
    }
   
    component_render();



}

void CDoor::ChangeDoorState(DOOR_STATE state)
{
    if (m_doorstate != state) {

        m_doorstate = state;
        switch (m_doorstate)
        {
        case DOOR_STATE::Open: {
            GetAnimator()->Play(L"OPEN");
        }
            break;
        case DOOR_STATE::CLOSE: {
            GetAnimator()->Play(L"CLOSE");
        }
            break;
        case DOOR_STATE::GO_OPEN: {
            GetAnimator()->Play(L"GoOpen");
        }
            break;
        case DOOR_STATE::GO_CLOSE: {
            GetAnimator()->Play(L"GoClose");
        }
            break;
        default:
            break;
        }



    }
}

void CDoor::OnCollisionEnter(CCollider* _pOther)
{
    if (m_doorstate == DOOR_STATE::Open) {

      vector<CGameObject*> players = CSceneManager::getInst()->GetCurScene()->GetPlayer();
      vector<CGameObject*> player2s = CSceneManager::getInst()->GetCurScene()->GetPlayer2();
      
      fPoint changePos;

      switch (m_doorDir)
      {
      case DOOR_DIR::UP: {

          changePos = fPoint(DOORDOWN_X, DOORDOWN_Y - 100);

      }
      break;
      case DOOR_DIR::DOWN: {

          changePos = fPoint(DOORUP_X , DOORUP_Y + 100);

      }

      break;
      case DOOR_DIR::LEFT: {

          changePos = fPoint(DOORRIGHT_X - 100 , DOORRIGHT_Y  );

      }
      break;
      case DOOR_DIR::RIGHT: {

          changePos = fPoint(DOORLEFT_X + 100 , DOORLFET_Y);

      }
      break;
      default:
          break;
      }


      

      for (int i = 0; i < players.size(); i++) {

          CIsaacPlayer* player = dynamic_cast<CIsaacPlayer*>(players[i]);

          if (player != nullptr) {

              player->SetPos(changePos);
              break;
          }

      }

      
      ChangeScn(goScene);

      
    }


}
