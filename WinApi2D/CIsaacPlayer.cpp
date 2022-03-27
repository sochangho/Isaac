#include "framework.h"
#include "CIsaacPlayer.h"
#include "CPlayerBody.h"
#include "CPlayerHead.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CBomb.h"
#include "CTears.h"
#include "CTile.h"
#include "CMonster.h"
#include "CAnimation.h"
#include "CBombRange.h"
#include "CScene.h"
CIsaacPlayer::CIsaacPlayer()
{
	
	
	m_pImg = CResourceManager::getInst()->
		LoadD2DImage(L"playerDefault", L"texture\\Animation\\character_001_isaac.png");
	SetName(L"PlayerHead");
	SetScale(fPoint(100, 100));
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Attacked", m_pImg, fPoint(64.f*2, 64.f*3), fPoint(64.f, 64.f), fPoint(64.f, 0.f), 0.5f, 1);
	GetAnimator()->FindAnimation(L"Attacked")->GetFrame(0).fptOffset = fPoint(0 , -20);
	GetAnimator()->Play(L"Attacked");
	m_stHead = IsaacStateHead::IDLE;
	m_stBody = IsaacStateBody::IDLE;
	m_isMove = false;
	m_isAttack = false;
	m_veclocity = 0.f;
	/// <summary>
	/// 플레이어 몸통 
	/// </summary>
	CPlayerBody* playerBody = new CPlayerBody;
	fPoint playerPos = GetPos();
	playerBody->SetPos(playerPos + fPoint(0, 15));

	/// <summary>
	/// 플레이어 머리
	/// </summary>
	CPlayerHead* playerHead = new CPlayerHead;
	playerHead->SetPos(playerPos - fPoint(0, 15));


	

	/// <summary>
	/// 자식 캐릭터로 
	/// </summary>
	AddChilde(playerBody , GROUP_GAMEOBJ::PLAYER);
	AddChilde(playerHead , GROUP_GAMEOBJ::PLAYER);

	CreateCollider();
	GetCollider()->SetScale(fPoint(20, 20));
	
	m_item = nullptr;
}

CIsaacPlayer::~CIsaacPlayer()
{
	if (m_item != nullptr) {
		delete m_item;
	}
}

CIsaacPlayer* CIsaacPlayer::Clone()
{
	return new CIsaacPlayer();
}

void CIsaacPlayer::update()
{
   
	
	Attack();

	if (!m_isColCheck && !m_isAttacked ) {
		Move();
	}

	if (m_isAttacked) {
		AttackedMove();
	}

	if (m_isInvincibility) {

		Invincibility();
	}



	if (KeyDown('E')) {

		CreateBomb();
	}

	fPoint pos = GetPos();
	if (!m_isAttacked ) {

		
		pos.x += m_dirVec2.normalize().x * m_veclocity * fDT;
		pos.y += m_dirVec2.normalize().y * m_veclocity * fDT;
		
	}
	PetUpdate();
	SetPos(pos);

	GetAnimator()->update();
	
	CCharacter::update();
}

void CIsaacPlayer::render()
{
	if (m_isAttacked == true) {
		CCharacter::render();
	}
}

void CIsaacPlayer::finalupdate()
{
	CCharacter::finalupdate();
}

void CIsaacPlayer::HeadState(IsaacStateHead head)
{
	

	if (m_stHead != head) {

	

		m_stHead = head;		
		CCharacter* childe = FindTypeChilde<CPlayerHead>();

		if (childe == nullptr) {
			return;
		}


		

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

        
		if (m_bodyDelay < 0.2) {
			m_bodyDelay += fDT;
			return;
		}

		m_bodyDelay = 0.f;




		CCharacter* childe = FindTypeChilde<CPlayerBody>();

		if (childe == nullptr) {
			return;
		}

		m_stBody = body;
		switch (m_stBody)
		{
		case CIsaacPlayer::IsaacStateBody::IDLE:
			childe->GetAnimator()->Play(L"IDLE");
			break;
		case CIsaacPlayer::IsaacStateBody::LEFT_MOVE:
			childe->GetAnimator()->Play(L"LEFT_MOVE");
			break;
		case CIsaacPlayer::IsaacStateBody::RIGHT_MOVE:
			childe->GetAnimator()->Play(L"RIGHT_MOVE");
			break;
		case CIsaacPlayer::IsaacStateBody::UP_MOVE:
			childe->GetAnimator()->Play(L"UP_MOVE");
			break;
		case CIsaacPlayer::IsaacStateBody::DOWN_MOVE:
			childe->GetAnimator()->Play(L"DOWN_MOVE");
			break;
		default:
			break;
		}
		

	}


}

void CIsaacPlayer::Attack()
{

	if (!m_isAttack) {

		if (Key(VK_UP)) {
			m_isAttack = true;
			HeadState(IsaacStateHead::UP_ATTACK);
			// 물풍선  생성 
			CreateWaterballoon(fVec2(0, -1));

		}
		else if (Key(VK_DOWN)) {
			m_isAttack = true;
			HeadState(IsaacStateHead::DOWN_ATTACK);
			// 물풍선  생성 
			CreateWaterballoon(fVec2(0, 1));

		}
		else  if (Key(VK_LEFT)) {
			m_isAttack = true;
			HeadState(IsaacStateHead::LEFT_ATTACK);
			// 물풍선  생성 
			CreateWaterballoon(fVec2(-1, 0));

		}
		else if (Key(VK_RIGHT)) {
			m_isAttack = true;
			HeadState(IsaacStateHead::RIGHT_ATTACK);
			CreateWaterballoon(fVec2(1, 0));

			// 물풍선  생성 
		}
	}
	else {


		if (m_attackTime < 0.4f) {

			m_attackTime += fDT;

		}
		else {

			m_isAttack = false;
			m_attackTime = 0.f;
		}


	}
	if (Key(VK_UP) || Key(VK_DOWN) || Key(VK_LEFT) || Key(VK_RIGHT))
	{

		m_isAttackKey = true;


	}
	else {

		m_isAttackKey = false;
	}
}

void CIsaacPlayer::Move()
{

	if (Key('W')) {

		m_dirVec2.y = -1;

		if (!m_isAttackKey) {
			HeadState(IsaacStateHead::UP_MOVE);
		}
		BodyState(IsaacStateBody::UP_MOVE);
	}
	else if (Key('S') ) {
		m_dirVec2.y = 1;

		if (!m_isAttackKey) {
			HeadState(IsaacStateHead::DOWN_MOVE);
		}
		BodyState(IsaacStateBody::DOWN_MOVE);
	}




	if (Key('A')) {

		m_dirVec2.x = -1;

		if (!m_isAttackKey) {
			if (Key('S')) {

				HeadState(IsaacStateHead::DOWN_MOVE);
			}
			else if (Key('W')) {

				HeadState(IsaacStateHead::UP_MOVE);
			}
			else {
				HeadState(IsaacStateHead::LEFT_MOVE);
			}
		}
		BodyState(IsaacStateBody::LEFT_MOVE);
	}
	else if (Key('D')) {


		m_dirVec2.x = 1;
		
		if (!m_isAttackKey) {
			if (Key('S')) {

				HeadState(IsaacStateHead::DOWN_MOVE);
			}
			else if (Key('W')) {

				HeadState(IsaacStateHead::UP_MOVE);
			}
			else {
				HeadState(IsaacStateHead::RIGHT_MOVE);
			}
		}
		BodyState(IsaacStateBody::RIGHT_MOVE);

	}


	if (Key('W') || Key('A') || Key('S') || Key('D')) {

		m_isMove = true;
		if (m_veclocity < 200.f) {
			
			m_veclocity += 200.f * fDT;
		}


	}
	else {

		m_isMove = false;

		if (m_veclocity > 0.f) {

			m_veclocity -= 100.f * fDT;
		}
		else {
			m_veclocity = 0.f;

		}




	}

	if (!m_isMove) {

		if (!m_isAttackKey) {

			HeadState(IsaacStateHead::IDLE);
		}
		BodyState(IsaacStateBody::IDLE);
	}




}

void CIsaacPlayer::OppositeMove()
{

	if (m_ColTime < m_ColDuration) {

		m_ColTime += fDT;
		m_veclocity += 300 * fDT;
	}
	else {

		m_ColTime = 0;
		m_isColCheck = false;
		
	}

}

void CIsaacPlayer::AttackedMove()
{

	if (m_attacedTime < m_AttackedDuration) {

		m_attacedTime += fDT;

		fPoint pos = GetPos();
		pos.x += m_dirVec2.normalize().x * m_veclocity * fDT;
		pos.y += m_dirVec2.normalize().y * m_veclocity * fDT;
		SetPos(pos);
		
	}
	else {

		m_attacedTime = 0;
		m_veclocity = 0;
		m_isAttacked = false;

	}

}

void CIsaacPlayer::Invincibility()
{
	if (m_invincibilityT < m_invincibilityD) {

		m_invincibilityT += fDT;

	}
	else {

		m_isInvincibility = false;
		m_invincibilityT = 0.f;
	}

}



void CIsaacPlayer::CreateWaterballoon(fVec2 dir)
{
	if (m_item == nullptr) {
		fPoint pos = GetPos();

		pos.x += 10 * dir.x;
		pos.y += 10 * dir.y;

		CTears* tears = new CTears;
		tears->SetPos(pos);
		tears->SetDir(dir);

		CreateObj(tears, GROUP_GAMEOBJ::TEARS);
		
	}
	else {


		m_item->ItemUse(dir);

	}
	vector<CCharacter*>& childes = GetChildes();
	for (auto iter = childes.begin(); iter != childes.end(); ) {


		if ((*iter)->isDead()) {

			iter = childes.erase(iter);
		}
		else {

			CIsaacPlayer2* player2 = dynamic_cast<CIsaacPlayer2*>(*iter);
			if (player2 != nullptr) {
				player2->ItemUse(dir);
			}

			iter++;
		}


	}

}


void CIsaacPlayer::CreateBomb()
{
	fPoint pos = GetPos();

	CBomb* bomb = new CBomb;
	pos.y -= 30;
	bomb->SetPos(pos);
	CreateObj(bomb, GROUP_GAMEOBJ::BOMB);
}

CItem* CIsaacPlayer::GetItem()
{
	return m_item;
}

float CIsaacPlayer::GetVelocity()
{
	return m_veclocity;
}

fVec2 CIsaacPlayer::GetPlayerDir()
{
	return m_dirVec2;
}

CIsaacPlayer::IsaacStateBody CIsaacPlayer::GetBodyState()
{
	return m_stBody;
}

void CIsaacPlayer::AddPet(CIsaacPlayer2* character)
{

	character->SetPos(GetPos());
	this->AddChilde(character, GROUP_GAMEOBJ::PLAYER2);

}

void CIsaacPlayer::PetUpdate()
{

	vector<CCharacter*>& childes = GetChildes();
	CCharacter* prevC = nullptr;
	
	for (auto iter = childes.begin(); iter != childes.end(); ) {

		if ((*iter)->isDead()) {
			iter = childes.erase(iter);
		}
		else {

			fPoint dPos;
			fPoint sPos;
			CIsaacPlayer2* player2 = dynamic_cast<CIsaacPlayer2*>(*iter);
			if (player2 != nullptr) {


				if (prevC == nullptr) {
					
					dPos = GetPos();
					sPos = (*iter)->GetPos();
				}
				else {

					dPos = prevC->GetPos();
					sPos = (*iter)->GetPos();
				}

				fPoint distance = dPos - sPos;
				if (distance.Length() > 30.f) {
					sPos.x += 170.f * distance.normalize().x * fDT;
					sPos.y += 170.f * distance.normalize().y * fDT;

					(*iter)->SetPos(sPos);
				}

				prevC = *iter;			
			}			
			iter++;
		}
	}



}

void CIsaacPlayer::SetItem(CItem* item)
{
	if (this->m_item != nullptr) {
		delete this->m_item;
	}

	this->m_item = item;    
	this->m_item->SetOwnObj(this);

}

void CIsaacPlayer::OnCollision(CCollider* _pOther)
{

	CTile* tile = dynamic_cast<CTile*>(_pOther->GetObj());

	if (tile != nullptr && (tile->GetGroup() == GROUP_TILE::WALL || tile->GetGroup() == GROUP_TILE::GROUND)) {

		m_isColCheck = true;

		if (tile->GetCollider()->GetFinalPos().x - GetCollider()->GetFinalPos().x > 0) {

			m_dirVec2.x = -1;

		}
		else {

			m_dirVec2.x = 1;
		}
		

		if (tile->GetCollider()->GetFinalPos().y - GetCollider()->GetFinalPos().y > 0) {

			m_dirVec2.y = -1;

		}
		else {

			m_dirVec2.y = 1;
		}



	}


	
}

void CIsaacPlayer::OnCollisionEnter(CCollider* _pOther)
{

	CTile* tile = dynamic_cast<CTile*>(_pOther->GetObj());
	CDefaultTears* tears = dynamic_cast<CDefaultTears*>(_pOther->GetObj());

	if (tile != nullptr && tile->GetGroup() == GROUP_TILE::WALL) {

		m_isColCheck = true;

	}

	CMonster* monster = dynamic_cast<CMonster*>(_pOther->GetObj());
	if ( monster != nullptr && !m_isInvincibility) {

		m_isInvincibility = true;
		m_isAttacked = true;
		m_veclocity = 100;
		fPoint pos = GetPos();
		fPoint monsterPos = monster->GetPos();
		m_dirVec2.x = pos.x - monsterPos.x;
		m_dirVec2.y = pos.y - monsterPos.y;


		//HP: 감소

	}

	if (tears != nullptr && tears->type == CDefaultTears::AttackType::PLAYER &&!m_isInvincibility) {

		m_isInvincibility = true;
		m_isAttacked = true;
		m_veclocity = 100;
		fPoint pos = GetPos();
		fPoint tPos = tears->GetPos();
		m_dirVec2.x = pos.x - tPos.x;
		m_dirVec2.y = pos.y - tPos.y;

	}



	CBombRange* bomb = dynamic_cast<CBombRange*>(_pOther->GetObj());

	if (bomb != nullptr && !m_isInvincibility) {

		m_isInvincibility = true;
		m_isAttacked = true;
		m_veclocity = 100;
		fPoint pos = GetPos();
		fPoint bombPos = bomb->GetPos();
		m_dirVec2.x = pos.x - bombPos.x;
		m_dirVec2.y = pos.y - bombPos.y;
	}



}

void CIsaacPlayer::OnCollisionExit(CCollider* _pOther)
{

	
	CTile* tile = dynamic_cast<CTile*>(_pOther->GetObj());

	if (tile != nullptr && (tile->GetGroup() == GROUP_TILE::WALL || tile->GetGroup() == GROUP_TILE::GROUND)) {

		m_isColCheck = false;
		m_veclocity = 0;
		
	}
	


}

