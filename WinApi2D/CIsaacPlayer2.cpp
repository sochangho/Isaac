#include "framework.h"
#include "CIsaacPlayer2.h"
#include "CIsaacPlayer.h"
#include "CScene.h"
CIsaacPet::CIsaacPet()
{

    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<int> dis(130, 180);

    m_velocity = dis(gen);
    uniform_int_distribution<int> distance(10 , 50);
    m_distance = distance(gen);


    


}

CIsaacPet::~CIsaacPet()
{
}

CIsaacPet* CIsaacPet::Clone()
{
    return new CIsaacPet(*this);
}

CIsaacPet* CIsaacPet::Create()
{
    return new CIsaacPet;
}

void CIsaacPet::update()
{
    //CCharacter::update();


    CIsaacPlayer* player = dynamic_cast<CIsaacPlayer*>(GetParentObj());

    if (GetParentObj() == nullptr) {

        return;
    }

    vector<CCharacter*>& childes = player->GetChildes();

    


 

   
    CIsaacPlayer::IsaacStateBody dobystate = player->GetBodyState();
   
    switch (dobystate)
    {
    case CIsaacPlayer::IsaacStateBody::IDLE: {
        state = PetState::IDLE;
    }
        break;
    case CIsaacPlayer::IsaacStateBody::LEFT_MOVE: {
        state = PetState::LEFT;
    }
        break;
    case CIsaacPlayer::IsaacStateBody::RIGHT_MOVE: {
        state = PetState::RIGHT;
    }
        break;
    case CIsaacPlayer::IsaacStateBody::UP_MOVE: {
        state = PetState::UP;
    }
        break;
    case CIsaacPlayer::IsaacStateBody::DOWN_MOVE: {
        state = PetState::DOWN;
    }
        break;
    default:
        break;
    }
 
}

void CIsaacPet::render()
{
}

CIsaacPet::PetState CIsaacPet::GetPlayer2State()
{
    return state;
}
