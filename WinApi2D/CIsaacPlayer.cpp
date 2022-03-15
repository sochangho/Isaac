#include "framework.h"
#include "CIsaacPlayer.h"
#include "CPlayerBody.h"
#include "CPlayerHead.h"
#include "CCollider.h"
#include "CAnimator.h"
CIsaacPlayer::CIsaacPlayer()
{
	
	m_stHead = IsaacStateHead::IDLE;
	m_stBody = IsaacStateBody::IDLE;
	m_isMove = false;
	m_veclocity = 100.f;
	/// <summary>
	/// 플레이어 몸통 
	/// </summary>
	CPlayerBody* playerBody = new CPlayerBody;
	fPoint playerPos = GetPos();
	playerBody->SetPos(playerPos + fPoint(0, 10));
	playerBody->CreateCollider();
	playerBody->GetCollider()->SetScale(fPoint(17, 17));
	/// <summary>
	/// 플레이어 머리
	/// </summary>
	CPlayerHead* playerHead = new CPlayerHead;
	playerHead->SetPos(playerPos - fPoint(0, 10));
	playerHead->CreateCollider();
	playerHead->GetCollider()->SetScale(fPoint(30, 30));

	/// <summary>
	/// 자식 캐릭터로 
	/// </summary>
	AddChilde(playerBody);
	AddChilde(playerHead);


}

CIsaacPlayer::~CIsaacPlayer()
{
}

CIsaacPlayer* CIsaacPlayer::Clone()
{
	return new CIsaacPlayer(*this);
}

void CIsaacPlayer::update()
{
   
	if (Key('W')) {
		
		fPoint pos = GetPos();
		pos.y -= m_veclocity * fDT;
		SetPos(pos);
		HeadState(IsaacStateHead::UP_MOVE);
		BodyState(IsaacStateBody::UP_MOVE);
	}
	if (Key('A')) {

		fPoint pos = GetPos();
		pos.x -= m_veclocity * fDT;
		SetPos(pos);
		HeadState(IsaacStateHead::LEFT_MOVE);
		BodyState(IsaacStateBody::LEFT_MOVE);
	}
	if (Key('S')) {

		fPoint pos = GetPos();
		pos.y += m_veclocity * fDT;
		SetPos(pos);
		HeadState(IsaacStateHead::DOWN_MOVE);
		BodyState(IsaacStateBody::DOWN_MOVE);
	}
	if (Key('D')) {

		fPoint pos = GetPos();
		pos.x += m_veclocity * fDT;
		SetPos(pos);
		HeadState(IsaacStateHead::RIGHT_MOVE);
		BodyState(IsaacStateBody::RIGHT_MOVE);

	}
	
	if (Key(VK_UP)) {

		HeadState(IsaacStateHead::UP_ATTACK);
		// 물풍선  생성 
		CreateWaterballoon(fVec2(0, -1));
	}
	if (Key(VK_DOWN)) {

		HeadState(IsaacStateHead::DOWN_ATTACK);
		// 물풍선  생성 
		CreateWaterballoon(fVec2(0, 1));
	}
	if (Key(VK_LEFT)) {

		HeadState(IsaacStateHead::LEFT_ATTACK);
		// 물풍선  생성 
		CreateWaterballoon(fVec2(-1, 0));
	}
	if (Key(VK_RIGHT)) {

		HeadState(IsaacStateHead::RIGHT_ATTACK);
		CreateWaterballoon(fVec2(1, 0));
		// 물풍선  생성 
	}

	if (Key('E')) {

		//폭탄 생성 
	}


	if (Key('W') || Key('A') || Key('S') || Key('D')) {

		m_isMove = true;

	}
	else {

		m_isMove = false;

	}

	if (Key(VK_UP) || Key(VK_DOWN) || Key(VK_LEFT) || Key(VK_RIGHT)) {

		m_isAttack = true;
	}
	else {

		m_isAttack = false;
	}

	if (!m_isMove) {

		if (!m_isAttack) {

			HeadState(IsaacStateHead::IDLE);
		}
		BodyState(IsaacStateBody::IDLE);
	}


	CCharacter::update();
}

void CIsaacPlayer::render()
{
	CCharacter::render();
}

void CIsaacPlayer::finalupdate()
{
	CCharacter::finalupdate();
}

void CIsaacPlayer::HeadState(IsaacStateHead head)
{
	vector<CCharacter*>& childes =  GetChildes();
	int index = -1;
	for (int i = 0; i < childes.size(); i++) {

		if (dynamic_cast<CPlayerHead*>(childes[i]) != nullptr) {
			index = i;
		}

	}

	if (index == -1) {
		return;
	}


	if (m_stHead != head) {
		m_stHead = head;

		switch (m_stHead)
		{
		case CIsaacPlayer::IsaacStateHead::IDLE:
			childes[index]->GetAnimator()->Play(L"IDLE");
			break;
		case CIsaacPlayer::IsaacStateHead::LEFT_MOVE:
			childes[index]->GetAnimator()->Play(L"LEFT_MOVE");
			break;
		case CIsaacPlayer::IsaacStateHead::RIGHT_MOVE:
			childes[index]->GetAnimator()->Play(L"RIGHT_MOVE");
			break;
		case CIsaacPlayer::IsaacStateHead::UP_MOVE:
			childes[index]->GetAnimator()->Play(L"UP_MOVE");
			break;
		case CIsaacPlayer::IsaacStateHead::DOWN_MOVE:
			childes[index]->GetAnimator()->Play(L"DOWN_MOVE");
			break;
		case CIsaacPlayer::IsaacStateHead::LEFT_ATTACK:
			childes[index]->GetAnimator()->Play(L"LEFT_ATTACK");
			break;
		case CIsaacPlayer::IsaacStateHead::RIGHT_ATTACK:
			childes[index]->GetAnimator()->Play(L"RIGHT_ATTACK");
			break;
		case CIsaacPlayer::IsaacStateHead::UP_ATTACK:
			childes[index]->GetAnimator()->Play(L"UP_ATTACK");
			break;
		case CIsaacPlayer::IsaacStateHead::DOWN_ATTACK:
			childes[index]->GetAnimator()->Play(L"DOWN_ATTACK");
			break;
		default:
			break;
		}

	}


}

void CIsaacPlayer::BodyState(IsaacStateBody body)
{
	vector<CCharacter*>& childes = GetChildes();
	int index = -1;
	for (int i = 0; i < childes.size(); i++) {

		if (dynamic_cast<CPlayerBody*>(childes[i]) != nullptr) {
			index = i;
		}

	}

	if (index == -1) {
		return;
	}

	if (body != m_stBody) {

		m_stBody = body;
		switch (m_stBody)
		{
		case CIsaacPlayer::IsaacStateBody::IDLE:
			childes[index]->GetAnimator()->Play(L"IDLE");
			break;
		case CIsaacPlayer::IsaacStateBody::LEFT_MOVE:
			childes[index]->GetAnimator()->Play(L"LEFT_MOVE");
			break;
		case CIsaacPlayer::IsaacStateBody::RIGHT_MOVE:
			childes[index]->GetAnimator()->Play(L"RIGHT_MOVE");
			break;
		case CIsaacPlayer::IsaacStateBody::UP_MOVE:
			childes[index]->GetAnimator()->Play(L"UP_MOVE");
			break;
		case CIsaacPlayer::IsaacStateBody::DOWN_MOVE:
			childes[index]->GetAnimator()->Play(L"DOWN_MOVE");
			break;
		default:
			break;
		}
		

	}


}

void CIsaacPlayer::CreateWaterballoon(fVec2 dir)
{
}


void CIsaacPlayer::CreateBomb()
{
}

