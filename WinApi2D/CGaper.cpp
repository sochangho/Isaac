#include "framework.h"
#include "CGaper.h"
#include "CGaperBody.h"
#include "CGaperHead.h"
#include "CAnimator.h"
CGaper::CGaper()
{

	CGaperBody* body = new CGaperBody;
	fPoint Pos = GetPos();
	body->SetPos(Pos + fPoint(0, 9.5));

	CGaperHead* head = new CGaperHead;
	head->SetPos(Pos - fPoint(0, 9));

	AddChilde(body, GROUP_GAMEOBJ::MONSTER);
	AddChilde(head, GROUP_GAMEOBJ::MONSTER);

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
	if (!GetStop()) {
		GoDestition();
	}
	CMonster::update();
	
	fVec2 dir = GetMonsterDir();
	if (dir.x > 0) {

		StateChange(GaperState::RIGHT);
	}
	else if(dir.x < 0) {

		StateChange(GaperState::LEFT);
	}
	else if (dir.x == 0) {


		if (dir.y > 0) {

			StateChange(GaperState::DOWN);
		}
		else{

			StateChange(GaperState::UP);
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

void CGaper::OnCollision(CCollider* _pOther)
{
}

void CGaper::OnCollisionEnter(CCollider* _pOther)
{
}

void CGaper::OnCollisionExit(CCollider* _pOther)
{
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
