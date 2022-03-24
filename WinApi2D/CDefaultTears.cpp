#include "framework.h"
#include "CDefaultTears.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CTile.h"
CDefaultTears::CDefaultTears()
{
}

CDefaultTears::~CDefaultTears()
{
}

CDefaultTears* CDefaultTears::Clone()
{
    return new CDefaultTears(*this);
}

void CDefaultTears::update()
{

	fPoint pos = GetPos();

	if (m_lifeTime < 2.f) {
		m_lifeTime += fDT;
		pos.x += m_velocity * m_fvDir.x * fDT;
		pos.y += m_velocity * m_fvDir.y * fDT;
		SetPos(pos);
	}
	else {

	}

	GetAnimator()->update();
}

void CDefaultTears::render()
{
	component_render();
}

void CDefaultTears::OnCollisionEnter(CCollider* pOther)
{

	if (pOther->GetObj()->GetName() == L"Monster") {



		m_effect->SetPos(GetPos());
		CreateObj(m_effect, GROUP_GAMEOBJ::EFFECT);

		DeleteObj(this);




	}

	CTile* tile = dynamic_cast<CTile*>(pOther->GetObj());


	if (tile != nullptr && tile->GetGroup() == GROUP_TILE::WALL) {

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

CD2DImage* CDefaultTears::GetImg()
{
	return m_pImg;
}

CEffect* CDefaultTears::GetEffect()
{
	return m_effect;
}
