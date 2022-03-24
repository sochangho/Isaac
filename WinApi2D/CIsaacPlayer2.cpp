#include "framework.h"
#include "CIsaacPlayer2.h"
#include "CIsaacPlayer.h"
#include "CScene.h"
CIsaacPlayer2::CIsaacPlayer2()
{

    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<int> dis(130, 180);

    m_velocity = dis(gen);
    uniform_int_distribution<int> distance(10 , 50);
    m_distance = distance(gen);


    


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
    //CCharacter::update();


    CIsaacPlayer* player = dynamic_cast<CIsaacPlayer*>(GetParentObj());

    if (GetParentObj() == nullptr) {

        return;
    }

    vector<CCharacter*>& childes = player->GetChildes();

    


    fPoint pos = GetPos();
    fVec2 dir = player->GetPos() - GetPos();
   
    if (dir.Length() > m_distance) {
        pos.x += m_velocity * dir.normalize().x * fDT;
        pos.y += m_velocity * dir.normalize().y * fDT;
        SetPos(pos);
    }

   
    CIsaacPlayer::IsaacStateBody dobystate = player->GetBodyState();
   
    switch (dobystate)
    {
    case CIsaacPlayer::IsaacStateBody::IDLE: {
        state = Player2State::IDLE;
    }
        break;
    case CIsaacPlayer::IsaacStateBody::LEFT_MOVE: {
        state = Player2State::LEFT;
    }
        break;
    case CIsaacPlayer::IsaacStateBody::RIGHT_MOVE: {
        state = Player2State::RIGHT;
    }
        break;
    case CIsaacPlayer::IsaacStateBody::UP_MOVE: {
        state = Player2State::UP;
    }
        break;
    case CIsaacPlayer::IsaacStateBody::DOWN_MOVE: {
        state = Player2State::DOWN;
    }
        break;
    default:
        break;
    }
 
}

void CIsaacPlayer2::render()
{
}

CIsaacPlayer2::Player2State CIsaacPlayer2::GetPlayer2State()
{
    return state;
}
