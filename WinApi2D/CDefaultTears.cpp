#include "framework.h"
#include "CDefaultTears.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CTile.h"
#include "CMonster.h"
#include "CIsaacPlayer.h"
#include "CRock.h"
CDefaultTears::CDefaultTears()
{
	CSoundManager::getInst()->Play(L"Tear1");
	
}

CDefaultTears::~CDefaultTears()
{
	CSoundManager::getInst()->Play(L"Tear2");
}

CDefaultTears* CDefaultTears::Clone()
{
    return new CDefaultTears(*this);
}

void CDefaultTears::update()
{

	fPoint pos = GetPos();

	if (m_lifeTime < m_gravitySecend) {
		m_lifeTime += fDT;
		pos.x += m_velocity * m_fvDir.x * fDT;
		pos.y += m_velocity * m_fvDir.y * fDT;
			
		
		
		SetPos(pos);
	}
	else if (m_lifeTime > m_gravitySecend && m_lifeTime < m_durationSecend) {
		m_lifeTime += fDT;
		pos.x += m_velocity * m_fvDir.x * fDT;
		pos.y += m_velocity * m_fvDir.y * fDT + m_gravity * fDT;

		m_gravity += 400 * fDT;

		SetPos(pos);
	}
	else {

		m_effect->SetPos(GetPos());
		CreateObj(m_effect, GROUP_GAMEOBJ::EFFECT);

		DeleteObj(this);
	}

	GetAnimator()->update();
}

void CDefaultTears::render()
{
	component_render();
}

void CDefaultTears::OnCollisionEnter(CCollider* pOther)
{
	CMonster* monster = dynamic_cast<CMonster*>(pOther->GetObj());
	if ((type == AttackType::MONSATER) && monster != nullptr) {

		m_effect->SetPos(GetPos());
		CreateObj(m_effect, GROUP_GAMEOBJ::EFFECT);

		DeleteObj(this);
	}

	CIsaacPlayer* player = dynamic_cast<CIsaacPlayer*>(pOther->GetObj());
	if ((type == AttackType::PLAYER) && player != nullptr) {

		m_effect->SetPos(GetPos());
		CreateObj(m_effect, GROUP_GAMEOBJ::EFFECT);

		DeleteObj(this);
	}


	CTile* tile = dynamic_cast<CTile*>(pOther->GetObj());
	CRock* rock = dynamic_cast<CRock*>(pOther->GetObj());
	if ((tile != nullptr && tile->GetGroup() == GROUP_TILE::GROUND) || rock != nullptr ) {

		m_effect->SetPos(GetPos());
		CreateObj(m_effect, GROUP_GAMEOBJ::EFFECT);

		DeleteObj(this);


	}
}

void CDefaultTears::SetDir(fVec2 fv2)
{
	m_fvDir = fv2;
}

void CDefaultTears::SetImg(CD2DImage* img)
{
	m_pImg = img;
}

void CDefaultTears::SetEffect(CEffect* effect)
{
	m_effect = effect;
}

void CDefaultTears::SetVelocity(float vel)
{
	m_velocity = vel;
	
}

void CDefaultTears::SetSecend(float dur, float gravity)
{
	m_durationSecend = dur;
	m_gravitySecend = gravity;
}

CD2DImage* CDefaultTears::GetImg()
{
	return m_pImg;
}

CEffect* CDefaultTears::GetEffect()
{
	return m_effect;
}
