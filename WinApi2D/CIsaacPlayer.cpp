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
#include "CRock.h"
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

	GetAnimator()->CreateAnimation(L"DIE", m_pImg, fPoint(0.f, 64.f * 2), fPoint(64.f, 64.f), fPoint(64.f, 0.f), 0.2f, 1);
	GetAnimator()->FindAnimation(L"DIE")->Create(m_pImg, fPoint(64.f * 2, 64.f * 3), fPoint(64.f, 64.f), fPoint(64.f, 0.f), 0.2f, 1);
	GetAnimator()->FindAnimation(L"DIE")->Create(m_pImg, fPoint(64.f * 4, 64.f * 2), fPoint(64.f, 64.f), fPoint(64.f, 0.f), 0.2f, 1);
	for (int i = 0; i < 3; i++) {
		GetAnimator()->FindAnimation(L"DIE")->GetFrame(i).fptOffset = fPoint(0, -20);
	}
	GetAnimator()->CreateAnimation(L"DIE2", m_pImg, fPoint(64.f * 3, 64.f * 2), fPoint(64.f, 64.f), fPoint(64.f, 0.f), 0.2f, 1);
	GetAnimator()->FindAnimation(L"DIE2")->GetFrame(0).fptOffset = fPoint(0, -20);
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


	if (dropItem != nullptr) {
		dropItem = nullptr;
	}
}

CIsaacPlayer* CIsaacPlayer::Clone()
{
	return new CIsaacPlayer();
}

void CIsaacPlayer::update()
{

	if (CGameManager::getInst()->GetHart() == 0) {

		if (!m_isDie) {
			CSoundManager::getInst()->Play(L"Die");
			m_isDie = true;
		}
	}

	if (!m_isDie) {
		Attack();

		if (!m_isColCheck && !m_isAttacked) {
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
		if (!m_isAttacked) {


			pos.x += m_dirVec2.normalize().x * m_veclocity * fDT;
			pos.y += m_dirVec2.normalize().y * m_veclocity * fDT;

		}
		PetUpdate();
		SetPos(pos);

	}
	else {

		GetAnimator()->Play(L"DIE");
		
		if (m_dieAniTime < m_dieAniDuration) {
			m_dieAniTime += fDT;
		}
		else {

			
			GetAnimator()->Play(L"DIE2");
			
			if (m_dieAfterTime < m_dieAfterDelay) {

				m_dieAfterTime += fDT;

			}
			else {
				
				//ui 생성
				if (!CGameManager::getInst()->GetDieCheck()) {
					
					CGameManager::getInst()->SetDiecheck(true);		
				}

				if (CGameManager::getInst()->GetDieCheck()) {

					if (KeyDown(VK_SPACE)) {

						CSoundManager::getInst()->Stop(L"basement");
						GameEndScn(GROUP_SCENE::START);

					}

				}
			}

		}

	}
	

	GetAnimator()->update();
	
	CCharacter::update();
}

void CIsaacPlayer::render()
{
	if (m_isAttacked == true || m_isDie == true) {
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
		case CIsaacPlayer::IsaacStateHead::ITEM:
			childe->GetAnimator()->Play(L"ITEM");
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
		case CIsaacPlayer::IsaacStateBody::ITEM:
			childe->GetAnimator()->Play(L"ITEM");
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

		if (!m_isItem) {
			if (!m_isAttackKey) {
				HeadState(IsaacStateHead::UP_MOVE);
			}
			BodyState(IsaacStateBody::UP_MOVE);
		}
	}
	else if (Key('S') ) {
		m_dirVec2.y = 1;

		if (!m_isItem) {
			if (!m_isAttackKey) {
				HeadState(IsaacStateHead::DOWN_MOVE);
			}
			BodyState(IsaacStateBody::DOWN_MOVE);
		}
	}




	if (Key('A')) {

		m_dirVec2.x = -1;

		if (!m_isItem) {
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
	}
	else if (Key('D')) {


		m_dirVec2.x = 1;
		
		if (!m_isItem) {
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
	}

	if(m_isItem)
	{

		HeadState(IsaacStateHead::ITEM);
		BodyState(IsaacStateBody::ITEM);

		if (m_itemAniTime < m_itemAniDuration) {

			m_itemAniTime += fDT;

			dropItem->SetPos(fPoint(GetPos().x, GetPos().y - 50));

		}
		else {

			m_itemAniTime = 0.f;
			m_isItem = false;
			HeadState(IsaacStateHead::IDLE);
			BodyState(IsaacStateBody::IDLE);
			ItemAnimationAfterAdd();
			DeleteObj(dropItem);
			

		}

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

	if (!m_isMove && !m_isItem) {

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

			CIsaacPet* player2 = dynamic_cast<CIsaacPet*>(*iter);
			if (player2 != nullptr) {
				player2->ItemUse(dir);
			}

			iter++;
		}


	}

}


void CIsaacPlayer::CreateBomb()
{
	if (CGameManager::getInst()->GetBombCount() > 0) {


		fPoint pos = GetPos();

		CBomb* bomb = new CBomb;
		pos.y -= 30;
		bomb->SetPos(pos);
		CreateObj(bomb, GROUP_GAMEOBJ::BOMB);

		CGameManager::getInst()->SetBombCount(CGameManager::getInst()->GetBombCount() - 1);
	}
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

bool CIsaacPlayer::GetIsItem()
{
	return m_isItem;
}

void CIsaacPlayer::AddPet(CIsaacPet* character)
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
			CIsaacPet* player2 = dynamic_cast<CIsaacPet*>(*iter);
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

void CIsaacPlayer::SetIsItem(bool isitem)
{
	m_isItem = isitem;
}

void CIsaacPlayer::ItemAnimationAfterAdd()
{
	if (m_tempItem != nullptr) {

		SetItem(m_tempItem);
		m_tempItem = nullptr;
	}
	
	if (m_tempPlayer2 != nullptr) {

		AddPet(m_tempPlayer2);
		m_tempPlayer2 = nullptr;
	}


}

void CIsaacPlayer::AddItemEqu(CGameObject* dropItem ,CItem* item, CIsaacPet* player2)
{
	m_isItem = true;
	this->dropItem = dropItem;	
	m_tempItem = item;
	m_tempPlayer2 = player2;
	CreateObj(this->dropItem, GROUP_GAMEOBJ::DROPITEM);
	CSoundManager::getInst()->Play(L"Item");
	
}

void CIsaacPlayer::OnCollision(CCollider* _pOther)
{

	CTile* tile = dynamic_cast<CTile*>(_pOther->GetObj());
	CRock* rock = dynamic_cast<CRock*>(_pOther->GetObj());


	if (tile != nullptr && tile->GetGroup() == GROUP_TILE::GROUND || rock != nullptr) {
		m_isColCheck = true;
		fPoint ObjPos = _pOther->GetObj()->GetPos();
		fPoint thisPos = GetPos();
		fVec2 dir = thisPos - ObjPos;
		m_dirVec2.x = dir.normalize().x;
		m_dirVec2.y = dir.normalize().y;
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

		if (CGameManager::getInst()->GetHart() > 0) {

			CGameManager::getInst()->SetHart(CGameManager::getInst()->GetHart() - 1);
			CSoundManager::getInst()->Play(L"Attacked");

		}



	}

	if (tears != nullptr && tears->type == CDefaultTears::AttackType::PLAYER &&!m_isInvincibility) {

		m_isInvincibility = true;
		m_isAttacked = true;
		m_veclocity = 100;
		fPoint pos = GetPos();
		fPoint tPos = tears->GetPos();
		m_dirVec2.x = pos.x - tPos.x;
		m_dirVec2.y = pos.y - tPos.y;



		if (CGameManager::getInst()->GetHart() > 0) {

			CGameManager::getInst()->SetHart(CGameManager::getInst()->GetHart() - 1);
			CSoundManager::getInst()->Play(L"Attacked");

		}



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

		if (CGameManager::getInst()->GetHart() > 0) {

			CGameManager::getInst()->SetHart(CGameManager::getInst()->GetHart() - 1);
			CSoundManager::getInst()->Play(L"Attacked");

		}
	}



}

void CIsaacPlayer::OnCollisionExit(CCollider* _pOther)
{

	
	CTile* tile = dynamic_cast<CTile*>(_pOther->GetObj());
	CRock* rock = dynamic_cast<CRock*>(_pOther->GetObj());
	if ((tile != nullptr &&  tile->GetGroup() == GROUP_TILE::GROUND) || rock != nullptr) {

		m_isColCheck = false;
		m_veclocity = 10;
		
	}
	


}

