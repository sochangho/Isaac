#include "framework.h"
#include "CGaper.h"
#include "CGaperBody.h"
#include "CGaperHead.h"
#include "CAnimator.h"
#include "CCollider.h"
CGaper::CGaper()
{
	random_device rd;
	mt19937_64 gen(rd());
	uniform_int_distribution<int> dis(120, 130);
	m_veclocity = dis(gen);

	CGaperBody* body = new CGaperBody;
	fPoint Pos = GetPos();
	body->SetPos(Pos + fPoint(0, 9.5));

	CGaperHead* head = new CGaperHead;
	head->SetPos(Pos - fPoint(0, 9));

	AddChilde(body, GROUP_GAMEOBJ::MONSTER);
	AddChilde(head, GROUP_GAMEOBJ::MONSTER);

	CreateCollider();
	GetCollider()->SetScale(fPoint(30, 50));

}

CGaper::~CGaper()
{
}

CGaper* CGaper::Clone()
{
	return new CGaper(*this);
}

void CGaper::update()
{
	bool change = false;



	if (!GetStop()) {
	 change	= GoDestition();
	}



	CMonster::update();
	
	fVec2 dir = GetMonsterDir();

	if (change == true) {

		if (dir.x > 0) {

			StateChange(GaperState::RIGHT);
		}
		else if (dir.x < 0) {

			StateChange(GaperState::LEFT);
		}
		else if (dir.x == 0) {


			if (dir.y > 0) {

				StateChange(GaperState::DOWN);
			}
			else if(dir.y<0) {

				StateChange(GaperState::UP);
			}
			else {

				StateChange(GaperState::IDLE);

			}

		}

	}


}

void CGaper::render()
{
	CMonster::render();
	
}

void CGaper::finalupdate()
{
	CMonster::finalupdate();
}



void CGaper::StateChange(GaperState state)
{

	if (state != m_state) {

		CCharacter* body = FindTypeChilde<CGaperBody>();
		m_state = state;

		switch (m_state)
		{
		case CGaper::GaperState::IDLE:
		{
			body->GetAnimator()->Play(L"IDLE");
		}
			break;
		case CGaper::GaperState::LEFT: {

			body->GetAnimator()->Play(L"LEFT");
		}
			break;
		case CGaper::GaperState::RIGHT: {
			body->GetAnimator()->Play(L"RIGHT");
		}
			break;
		case CGaper::GaperState::UP: {
			body->GetAnimator()->Play(L"UP");
		}
			break;
		case CGaper::GaperState::DOWN: {
			body->GetAnimator()->Play(L"DOWN");
		}
			break;
		default:
			break;
		}


	}

}
