#include "framework.h"
#include "CTears.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CTearsEffect.h"
#include "CTile.h"
CTears::CTears()
{
  SetImg(CResourceManager::getInst()->
		LoadD2DImage(L"Tears", L"texture\\Animation\\tearsEffect.png"));
	SetName(L"Attack");
	SetScale(fPoint(90, 90));
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"IDLE", GetImg(), fPoint(0.f, 0.f), fPoint(64.f, 64.f), fPoint(64.f, 0.f), 0.5f, 1);
	GetAnimator()->Play(L"IDLE");
	CreateCollider();
	GetCollider()->SetScale(fPoint(20, 20));
	SetEffect(new CTearsEffect);
}

CTears::~CTears()
{
}

CTears* CTears::Clone()
{
	return new CTears(*this);
}


