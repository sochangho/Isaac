#include "framework.h"
#include "CMonster.h"
#include "CCollider.h"
#include "CD2DImage.h"
#include "CAnimator.h"
#include "CTile.h"
#include "CScene.h"
#include "CTileNavMap.h"
#include "CTears.h"
#include "CBloodEffect.h"
CMonster::CMonster()
{
	m_destitionobj = nullptr;


	SetName(L"Monster");

}

CMonster::~CMonster()
{
}

void CMonster::update()
{
	if (is_attacked) {
		Attacked();
	}
	CCharacter::update();
}

void CMonster::render()
{

	
	COLORREF rgb = RGB(0, 0, 255);	
	for (auto iter = m_destinations.begin(); iter != m_destinations.end(); iter++) {

		fPoint pos;
		pos.x = iter->x;
		pos.y = iter->y;
		fPoint fptRenderPos = CCameraManager::getInst()->GetRenderPos(pos);
		CRenderManager::getInst()->RenderRectangle(
			fptRenderPos.x - CTile::SIZE_TILE / 2,
			fptRenderPos.y - CTile::SIZE_TILE / 2,
			fptRenderPos.x + CTile::SIZE_TILE / 2,
			fptRenderPos.y + CTile::SIZE_TILE / 2 , rgb);

	}
	CCharacter::render();

}

void CMonster::finalupdate()
{
	CCharacter::finalupdate();
}

void CMonster::SetDestinaionObj(CGameObject* obj)
{
	m_destitionobj = obj;
	is_stop = false;
}

void CMonster::SetDestination(const list<iPoint>& des)
{
	is_stop = true;
	m_destinations.clear();
	m_destinations = des;		
	m_curIter = m_destinations.begin();
	is_stop = false;

}

void CMonster::SetStop(bool stop)
{
	is_stop = stop;
}

bool CMonster::GoDestition()
{
	CScene* curScene = CSceneManager::getInst()->GetCurScene();
	

	if (m_destitionobj == nullptr ) {

		return false;
	}

	if (curScene->GettileNav() == nullptr) {
		CSceneManager::getInst()->GetCurScene()->SetTileNav(new CTileNavMap);
	}

	if (!is_init) {

		curScene->GettileNav()->CTileNavAstarUpdate(m_destitionobj, this);
		is_init = true;
	}


	fPoint monsterPos = GetPos();

	if ( m_curIter != m_destinations.end()) {
		

		m_dirVec2.x = (float)m_curIter->x - monsterPos.x;
		m_dirVec2.y = (float)m_curIter->y - monsterPos.y;
	}
	else {

		CSceneManager::getInst()->GetCurScene()->GettileNav()->CTileNavAstarUpdate(m_destitionobj,this);
		
	}


	if ( m_dirVec2.Length() >= 0.1f) {
	
		monsterPos.x += m_dirVec2.normalize().x * m_veclocity * fDT;
		monsterPos.y += m_dirVec2.normalize().y * m_veclocity * fDT;
		SetPos(monsterPos);		
	}
	else {



		if (m_curIter != m_destinations.end()) {

			iPoint curPos;
			curPos.x = m_curIter->x;
			curPos.y = m_curIter->y;
			
			m_curIter++;

			if (m_curIter != m_destinations.end()) {

				m_Anidir.x = m_curIter->x - curPos.x;
				m_Anidir.y = m_curIter->y - curPos.y;
			}
			else {

				m_Anidir.x = 0;
				m_Anidir.y = 0;
			}

			return true;
		}


	}	
	return false;
}

bool CMonster::GoRandom()
{
	CScene* curScene = CSceneManager::getInst()->GetCurScene();
	fPoint monsterPos = GetPos();

	if (curScene->GettileNav() == nullptr) {
		CSceneManager::getInst()->GetCurScene()->SetTileNav(new CTileNavMap);
	}

	if (!is_init) {

	    randomDestonaion = curScene->GettileNav()->CTileNavRandomUpdate(this);
		is_init = true;
	}


	m_dirVec2.x = randomDestonaion.x - monsterPos.x;
	m_dirVec2.y = randomDestonaion.y - monsterPos.y;


	if (m_dirVec2.Length() > 0.1f) {


		monsterPos.x += m_dirVec2.normalize().x * m_veclocity * fDT;
		monsterPos.y += m_dirVec2.normalize().y * m_veclocity * fDT;
		SetPos(monsterPos);

	}
	else {


		randomDestonaion = curScene->GettileNav()->CTileNavRandomUpdate(this);

		m_Anidir.x = randomDestonaion.x - monsterPos.x;
		m_Anidir.y = randomDestonaion.y - monsterPos.y;

		return true;
	}


	return false;
}

fVec2 CMonster::GetMonsterDir()
{
	return m_Anidir;
}

bool CMonster::GetStop()
{
	return is_stop;
}

void CMonster::Attacked()
{
	if (m_attackedTime < m_attackedDuration) {

		m_attackedTime += fDT;
		fPoint pos = GetPos();
		pos.x += m_dirVec2.normalize().x * m_attackedV * fDT;
		pos.y += m_dirVec2.normalize().y * m_attackedV * fDT;
		SetPos(pos);

	}
	else {

		m_attackedTime = 0.f;
		is_stop = false;
		is_attacked = false;
	}


}

void CMonster::OnCollision(CCollider* _pOther)
{
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
        
	CTears* tears = dynamic_cast<CTears*>(_pOther->GetObj());


	if (tears != nullptr && !is_attacked) {

		is_stop = true;
		is_attacked = true;
		fPoint pos = GetPos();
		fPoint tearsPos = tears->GetPos();
		m_dirVec2.x = pos.x - tearsPos.x;
		m_dirVec2.y = pos.y - tearsPos.y;

		m_hp -= tears->m_dmg;

		if (m_hp <= 0.f) {


         //effect»ý¼º

		CBloodEffect* blood = new CBloodEffect;
		blood->SetPos(GetPos());
		CreateObj(blood, GROUP_GAMEOBJ::EFFECT);
		DeleteObj(this);

		vector<CCharacter*>& childes = AllChilde();

		for (int i = 0; i < childes.size(); i++) {

			DeleteObj(childes[i]);
		}


	  }
       
	}


}

void CMonster::OnCollisionExit(CCollider* _pOther)
{
}
