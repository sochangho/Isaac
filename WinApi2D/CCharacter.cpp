#include "framework.h"
#include "CCharacter.h"
#include "CGameObject.h"
#include "CAnimator.h"
#include "CScene.h"
CCharacter::CCharacter()
{
    m_parent = nullptr;
}

CCharacter::CCharacter(const CCharacter& other) : CGameObject(other)
{
   

    m_fptFinalPos = other.m_fptFinalPos;

    for (int i = 0; i < other.m_vecChilde.size(); i++) {


        m_vecChilde.push_back(other.m_vecChilde[i]->Clone());
       
        m_vecChilde[i]->m_parent = this;

    }
}

CCharacter::~CCharacter()
{
    for (int i = 0; i < m_vecChilde.size(); i++) {

        if (m_vecChilde[i]->m_parent != nullptr) {

            m_vecChilde[i]->m_parent = nullptr;
        }    
    }

    m_vecChilde.clear();
}

CCharacter* CCharacter::Clone()
{
    return new CCharacter(*this);
}

void CCharacter::update()
{
    
    if (m_parent != nullptr) {

        SetPos(m_parent->GetPos() - m_fptFinalPos);

    }
   

  
}

void CCharacter::finalupdate()
{
   
    CGameObject::finalupdate();
   
}

void CCharacter::render()
{
    component_render();
}

void CCharacter::AddChilde(CCharacter* character , GROUP_GAMEOBJ type)
{
    character->m_parent = this;
    character->m_fptFinalPos = character->m_parent->GetPos() - character->GetPos();

    CScene* curScene = CSceneManager::getInst()->GetCurScene();
    CreateObj(character, type);
    m_vecChilde.push_back(character);

}

fPoint CCharacter::GetFinalPos()
{
    return m_fptFinalPos;
}

vector<CCharacter*>& CCharacter::GetChildes()
{
    return m_vecChilde;
}

CCharacter* CCharacter::GetParentObj()
{
    return m_parent;
}

vector<CCharacter*>& CCharacter::AllChilde()
{
   return m_vecChilde;
}
