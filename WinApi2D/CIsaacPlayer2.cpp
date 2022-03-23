#include "framework.h"
#include "CIsaacPlayer2.h"
#include "CIsaacPlayer.h"
#include "CScene.h"
CIsaacPlayer2::CIsaacPlayer2()
{






}

CIsaacPlayer2::~CIsaacPlayer2()
{
}

CIsaacPlayer2* CIsaacPlayer2::Clone()
{
    return new CIsaacPlayer2(*this);
}

void CIsaacPlayer2::update()
{
   CCharacter::update();


    CIsaacPlayer* player = dynamic_cast<CIsaacPlayer*>(GetParentObj());

    if (GetParentObj() == nullptr) {

        return;
    }

    
    fVec2 playerDir = player->GetPlayerDir();


    if (playerDir.x > 0) {

        state = Player2State::RIGHT;
    }
    else if(playerDir.x < 0) {

        state = Player2State::LEFT;

    }
    else {

        if (playerDir.y > 0) {

            state = Player2State::DOWN;
        }
        else if(playerDir.y < 0) {

            state = Player2State::UP;

        }
        else {

            state = Player2State::IDLE;
        }
    }


 
}

void CIsaacPlayer2::render()
{
}

CIsaacPlayer2::Player2State CIsaacPlayer2::GetPlayer2State()
{
    return state;
}
