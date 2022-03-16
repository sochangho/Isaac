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
	virtual void render(HDC hdc);

	void AddChilde(CCharacter* character);
	fPoint GetFinalPos();

	vector<CCharacter*>& GetChildes();

	template<typename T>
	CCharacter* FindTypeChilde();
};

template<typename T>
inline CCharacter* CCharacter::FindTypeChilde()
{

	vector<CCharacter*>& childes = GetChildes();
	
	for (int i = 0; i < childes.size(); i++) {

		if (dynamic_cast<T*>(childes[i]) != nullptr) {
			return childes[i];
		}

	}

	return nullptr;
}
