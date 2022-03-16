#pragma once
#include "CTexture.h"
#include "CCharacter.h"
class CPlayerBody : public CCharacter
{private:
	CTexture* m_pTex;
public:
	CPlayerBody();
	~CPlayerBody();

	virtual CPlayerBody* Clone();
	virtual void update();
	virtual void render(HDC hdc);
	virtual void finalupdate();
	

};

