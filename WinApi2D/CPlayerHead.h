#pragma once
#include "CTexture.h"
#include "CCharacter.h"
class CPlayerHead : public CCharacter
{
private:
	CTexture* m_pTex; 
public:
	CPlayerHead();
	~CPlayerHead();

	virtual CPlayerHead* Clone();
	virtual void update();
	virtual void render(HDC hdc);
	virtual void finalupdate();


};

