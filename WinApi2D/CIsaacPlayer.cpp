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
	playerBody->SetPos(playerPos + fPoint(1, 4));
	
	/// <summary>
	/// 플레이어 머리
	/// </summary>
	CPlayerHead* playerHead = new CPlayerHead;
	playerHead->SetPos(playerPos - fPoint(0, 5));
	
	

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

void CIsaacPlayer::render(HDC hdc)
{
	CCharacter::render(hdc);
}

void CIsaacPlayer::finalupdate()
{
	CCharacter::finalupdate();
}

void CIsaacPlayer::HeadState(IsaacStateHead head)
{
	

	if (m_stHead != head) {

		CCharacter* childe = FindTypeChilde<CPlayerHead>();

		if (childe == nullptr) {
			return;
		}


		m_stHead = head;

		switch (m_stHead)
		{
		case CIsaacPlayer::IsaacStateHead::IDLE:
			childe->GetAnimator()->Play(L"IDLE");
			break;
		case CIsaacPlayer::IsaacStateHead::LEFT_MOVE:
			childe->GetAnimator()->Play(L"LEFT_MOVE");
			break;
		case CIsaacPlayer::IsaacStateHead::RIGHT_MOVE:
			childe->GetAnimator()->Play(L"RIGHT_MOVE");
			break;
		case CIsaacPlayer::IsaacStateHead::UP_MOVE:
			childe->GetAnimator()->Play(L"UP_MOVE");
			break;
		case CIsaacPlayer::IsaacStateHead::DOWN_MOVE:
			childe->GetAnimator()->Play(L"DOWN_MOVE");
			break;
		case CIsaacPlayer::IsaacStateHead::LEFT_ATTACK:
			childe->GetAnimator()->Play(L"LEFT_ATTACK");
			break;
		case CIsaacPlayer::IsaacStateHead::RIGHT_ATTACK:
			childe->GetAnimator()->Play(L"RIGHT_ATTACK");
			break;
		case CIsaacPlayer::IsaacStateHead::UP_ATTACK:
			childe->GetAnimator()->Play(L"UP_ATTACK");
			break;
		case CIsaacPlayer::IsaacStateHead::DOWN_ATTACK:
			childe->GetAnimator()->Play(L"DOWN_ATTACK");
			break;
		default:
			break;
		}

	}


}

void CIsaacPlayer::BodyState(IsaacStateBody body)
{



	if (body != m_stBody) {

        
		CCharacter* childe = FindTypeChilde<CPlayerBody>();

		if (childe == nullptr) {
			return;
		}

		m_stBody = body;
		switch (m_stBody)
		{
		case CIsaacPlayer::IsaacStateBody::IDLE:
			childe->GetAnimator()->Play(L"BODY_IDLE");
			break;
		case CIsaacPlayer::IsaacStateBody::LEFT_MOVE:
			childe->GetAnimator()->Play(L"BODY_LEFT_MOVE");
			break;
		case CIsaacPlayer::IsaacStateBody::RIGHT_MOVE:
			childe->GetAnimator()->Play(L"BODY_RIGHT_MOVE");
			break;
		case CIsaacPlayer::IsaacStateBody::UP_MOVE:
			childe->GetAnimator()->Play(L"BODY_UP_MOVE");
			break;
		case CIsaacPlayer::IsaacStateBody::DOWN_MOVE:
			childe->GetAnimator()->Play(L"BODY_DOWN_MOVE");
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

