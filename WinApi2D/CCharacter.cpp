#include "framework.h"
#include "CCharacter.h"
#include "CGameObject.h"
#include "CAnimator.h"
CCharacter::CCharacter()
{
    m_parent = nullptr;
}

CCharacter::CCharacter(const CCharacter& other) : CGameObject(other)
{
    for (int i = 0; i < other.m_vecChilde.size(); i++) {

        m_vecChilde.push_back(other.m_vecChilde[i]->Clone());
    }
}

CCharacter::~CCharacter()
{
    for (int i = 0; i < m_vecChilde.size(); i++) {

        if (m_vecChilde[i]->m_parent != nullptr) {

            m_vecChilde[i]->m_parent = nullptr;
        }

        delete m_vecChilde[i];
    }

    m_vecChilde.clear();
}

CCharacter* CCharacter::Clone()
{
    return new CCharacter(*this);
}

void CCharacter::update()
{
   
   
    for (int i = 0; i < m_vecChilde.size(); i++) {

        m_vecChilde[i]->update();
    }
    
}

void CCharacter::finalupdate()
{
   
    if (m_parent != nullptr) {

       SetPos(m_parent->GetPos() - m_fptFinalPos);

    }
    CGameObject::finalupdate();
   
    for (int i = 0; i < m_vecChilde.size(); i++) {

        m_vecChilde[i]->finalupdate();
    }
}

void CCharacter::render(HDC hdc)
{
   

    component_render(hdc);

    for (int i = 0; i < m_vecChilde.size(); i++) {

        m_vecChilde[i]->render(hdc);
    }

}

void CCharacter::AddChilde(CCharacter* character)
{
    character->m_parent = this;
    character->m_fptFinalPos = character->m_parent->GetPos() - character->GetPos();
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
