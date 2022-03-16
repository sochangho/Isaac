#include "framework.h"
#include "CTears.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
CTears::CTears()
{
	m_pImg = CResourceManager::getInst()->
		LoadD2DImage(L"Tears", L"texture\\Animation\\tearsEffect.png");
	SetName(L"Attack");
	SetScale(fPoint(100, 100));
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"IDLE", m_pImg, fPoint(0.f, 0.f), fPoint(64.f, 64.f), fPoint(64.f, 0.f), 0.5f, 1);
	GetAnimator()->Play(L"IDLE");
	CreateCollider();
	GetCollider()->SetScale(fPoint(20, 20));
}

CTears::~CTears()
{
}

CTears* CTears::Clone()
{
	return new CTears(*this);
}

void CTears::update()
{
	fPoint pos = GetPos();

	if (m_lifeTime < 2.f) {
		m_lifeTime += fDT;
		pos.x += m_velocity * m_fvDir.x * fDT;
		pos.y += m_velocity * m_fvDir.y * fDT;
		SetPos(pos);
	}
	else {
		m_lifeTime = 0.f;
		DeleteObj(this);
		//捞棋飘 积己
	}

	GetAnimator()->update();
}

void CTears::render()
{
	component_render();
}

void CTears::OnCollisionEnter(CCollider* pOther)
{
	if (pOther->GetObj()->GetName() == L"Monster") {
		
		DeleteObj(this);

		//捞棋飘 积己 

	}
	if (pOther->GetObj()->GetName() == L"Wall") {

		DeleteObj(this);
		//捞棋飘 积己
	}

}

void CTears::SetDir(fVec2 fv2)
{
	m_fvDir = fv2;
}
