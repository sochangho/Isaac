#include "framework.h"
#include "CBloodTears.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CTearsEffect.h"
#include "CTile.h"
CBloodTears::CBloodTears()
{

	SetImg(CResourceManager::getInst()->
		LoadD2DImage(L"BloodTears", L"texture\\Animation\\blodTearsEffect.png"));
	SetName(L"Attack");
	SetScale(fPoint(100, 100));
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"IDLE", GetImg(), fPoint(0.f, 0.f), fPoint(64.f, 64.f), fPoint(64.f, 0.f), 0.5f, 1);
	GetAnimator()->Play(L"IDLE");
	CreateCollider();
	GetCollider()->SetScale(fPoint(20, 20));
	SetEffect(new CTearsEffect);
}

CBloodTears::~CBloodTears()
{
}

CBloodTears* CBloodTears::Clone()
{
	return new CBloodTears(*this);
}
