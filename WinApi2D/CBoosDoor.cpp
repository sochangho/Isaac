#include "framework.h"
#include "CDoor.h"
#include "CBoosDoor.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CIsaacPlayer.h"
#include "CScene.h"


CBoosDoor::CBoosDoor() {


    m_Img = nullptr;
    SetScale(fPoint(100, 100));
    CreateCollider();
    GetCollider()->SetScale(fPoint(80, 80));

}
CBoosDoor::~CBoosDoor() {




}

void CBoosDoor::LoadDoor(DOOR_DIR doorDir, GROUP_SCENE scene) {
    goScene = scene;
    m_doorDir = doorDir;
    switch (m_doorDir)
    {
    case DOOR_DIR::UP: {
        m_Img = CResourceManager::getInst()->LoadD2DImage(L"BossDoorUp", L"texture\\Animation\\BossDoorUp.png");
    }
                     break;
    case DOOR_DIR::DOWN: {
        m_Img = CResourceManager::getInst()->LoadD2DImage(L"BossDoorDown", L"texture\\Animation\\BossDoorDown.png");
    }
                       break;
    case DOOR_DIR::LEFT: {
        m_Img = CResourceManager::getInst()->LoadD2DImage(L"BossDoorLeft", L"texture\\Animation\\NomalDoorLeft.png");
    }
                       break;
    case DOOR_DIR::RIGHT: {
        m_Img = CResourceManager::getInst()->LoadD2DImage(L"BossDoorRight", L"texture\\Animation\\NomalDoorRight.png");
    }
                        break;
    default:
        break;
    }

}