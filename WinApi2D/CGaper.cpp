#include "framework.h"
#include "CGaper.h"

CGaper::~CGaper()
{
}

CGaper* CGaper::Clone()
{
	return new CGaper(*this);
}

void CGaper::update()
{
}

void CGaper::render()
{
}

void CGaper::OnCollision(CCollider* _pOther)
{
}

void CGaper::OnCollisionEnter(CCollider* _pOther)
{
}

void CGaper::OnCollisionExit(CCollider* _pOther)
{
}
