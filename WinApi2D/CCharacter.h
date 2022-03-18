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

	void AddChilde(CCharacter* character , GROUP_GAMEOBJ type);
	fPoint GetFinalPos();

	vector<CCharacter*>& GetChildes();
	CCharacter* GetParentObj();
	template<typename T>
	CCharacter* FindTypeChilde();



	virtual void OnCollision(CCollider* _pOther) {}
	virtual void OnCollisionEnter(CCollider* _pOther) {}
	virtual void OnCollisionExit(CCollider* _pOther) {}
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
