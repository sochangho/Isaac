#include "framework.h"
#include "CGaperBodyMonster.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CBloodTears.h"
#include "CTile.h"
CGaperBodyMonster::CGaperBodyMonster()
{
    m_pImg = CResourceManager::getInst()->LoadD2DImage(L"GaperBody2", L"texture\\Animation\\monsterBody.png");
   
    SetScale(fPoint(50, 50));
    CreateAnimator();

    GetAnimator()->CreateAnimation(L"IDLE", m_pImg, fPoint(0.f, 0.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.5f, 1);


    GetAnimator()->CreateAnimation(L"LEFT", m_pImg, fPoint(32.f * 2, 32.f * 2), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.1f, 2, true);
    CAnimation* animation = GetAnimator()->FindAnimation(L"LEFT");
    animation->Create(m_pImg, fPoint(0.f, 32.f * 3), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.1f, 4);
    animation->Create(m_pImg, fPoint(0.f, 32.f * 4), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.1f, 4);

    GetAnimator()->CreateAnimation(L"RIGHT", m_pImg, fPoint(32.f * 2, 32.f * 2), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.1f, 2);
    animation = GetAnimator()->FindAnimation(L"RIGHT");
    animation->Create(m_pImg, fPoint(0.f, 32.f * 3), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.1f, 4);
    animation->Create(m_pImg, fPoint(0.f, 32.f * 4), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.1f, 4);



    GetAnimator()->CreateAnimation(L"UP", m_pImg, fPoint(0.f, 0.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.1f, 4, true);
    animation = GetAnimator()->FindAnimation(L"UP");
    animation->Create(m_pImg, fPoint(0.f, 32.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.1f, 4);
    animation->Create(m_pImg, fPoint(0.f, 32.f * 2), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.1f, 2);


    GetAnimator()->CreateAnimation(L"DOWN", m_pImg, fPoint(0.f, 0.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.1f, 4);
    animation = GetAnimator()->FindAnimation(L"DOWN");
    animation->Create(m_pImg, fPoint(0.f, 32.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.1f, 4);
    animation->Create(m_pImg, fPoint(0.f, 32.f * 2), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.1f, 2);
    GetAnimator()->Play(L"IDLE");

    CreateCollider();
    GetCollider()->SetScale(fPoint(20, 20));
	SetStop(false);



	random_device rd;
	mt19937_64 gen(rd());
	uniform_int_distribution<int> dis(1, 4);

	m_attackduration = dis(gen);
	

}

CGaperBodyMonster::~CGaperBodyMonster()
{
}

CGaperBodyMonster* CGaperBodyMonster::Clone()
{
    return new CGaperBodyMonster(*this);
}

void CGaperBodyMonster::update()
{


	bool change = false;



	if (!GetStop()) {
		change = GoRandom();
	}

	if (m_attackTime < m_attackduration) {
		m_attackTime += fDT;
	}
	else {

		CBloodTears* bloodTeas = new CBloodTears;
		bloodTeas->type = CDefaultTears::AttackType::PLAYER;

		fPoint pos = GetPos();

		random_device rd;
		mt19937_64 gen(rd());
		uniform_int_distribution<int> dis(0, 360);
		
		fVec2 fvDir;

		fvDir.normalize().x = (float)cos(dis(gen));
		fvDir.normalize().y = (float)sin(dis(gen));
		
		bloodTeas->SetPos(pos);
		bloodTeas->SetDir(fvDir);
		CreateObj(bloodTeas, GROUP_GAMEOBJ::TEARS);
		m_attackTime = 0.f;

	}



	CMonster::update();

	fVec2 dir = GetMonsterDir();

	ChangeAni(change);
	GetAnimator()->update();
}

void CGaperBodyMonster::render()
{
	component_render();
}

void CGaperBodyMonster::finalupdate()
{
	CMonster::finalupdate();
}

void CGaperBodyMonster::stateChange(GaperBodyState state)
{
	if (state != m_state) {
		m_state = state;
		switch (m_state)
		{
		case CGaperBodyMonster::GaperBodyState::IDLE: {
			GetAnimator()->Play(L"IDLE");
		}
			break;
		case CGaperBodyMonster::GaperBodyState::LEFT: {
			GetAnimator()->Play(L"LEFT");
		}
			break;
		case CGaperBodyMonster::GaperBodyState::RIGHT: {
			GetAnimator()->Play(L"RIGHT");
		}
			break;
		case CGaperBodyMonster::GaperBodyState::UP: {
			GetAnimator()->Play(L"UP");
		}
			break;
		case CGaperBodyMonster::GaperBodyState::DOWN: {
			GetAnimator()->Play(L"DOWN");
		}
			break;
		default:
			break;
		}

	}


}

void CGaperBodyMonster::ChangeAni(bool change)
{
	fVec2 dir = GetMonsterDir();

	if (change == true) {

		if (dir.x > 0) {

			stateChange(GaperBodyState::RIGHT);
		}
		else if (dir.x < 0) {

			stateChange(GaperBodyState::LEFT);
		}
		else if (dir.x == 0) {


			if (dir.y > 0) {

				stateChange(GaperBodyState::DOWN);
			}
			else if (dir.y < 0) {

				stateChange(GaperBodyState::UP);
			}
			else {

				stateChange(GaperBodyState::IDLE);

			}

		}

	}
}

void CGaperBodyMonster::OnCollisionEnter(CCollider* _pOther)
{
	CMonster::OnCollisionEnter(_pOther);

	CTile* tile = dynamic_cast<CTile*>(_pOther->GetObj());

	if (tile != nullptr && (tile->GetGroup() == GROUP_TILE::WALL|| tile->GetGroup() == GROUP_TILE::GROUND)) {

		ChangeDir(tile->GetPos());
		ChangeAni(true);

	}


}
