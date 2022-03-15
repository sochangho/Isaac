#pragma once
#include "CGameObject.h"
class CCharacter : public CGameObject
{
private:

	CCharacter* m_parent;
	vector<CCharacter*> m_vecChilde;
	fPoint m_fptFinalPos;
public:
	CCharacter();
	CCharacter(const CCharacter& other);
	virtual ~CCharacter();

	virtual CCharacter* Clone();
	virtual void update();
	virtual void finalupdate();
	virtual void render();

	void AddChilde(CCharacter* character);
	fPoint GetFinalPos();

	vector<CCharacter*>& GetChildes();
};

