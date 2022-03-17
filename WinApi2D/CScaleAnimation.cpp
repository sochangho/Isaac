#include "framework.h"
#include "CScaleAnimation.h"
#include "CGameObject.h"
CScaleAnimation::CScaleAnimation()
{
}

CScaleAnimation::~CScaleAnimation()
{
    for (int i = 0; i < m_vecScaleX.size(); i++) {

        delete m_vecScaleX[i];
    }

    for (int i = 0; i < m_vecScaleY.size(); i++) {

        delete m_vecScaleY[i];
    }

    m_vecScaleX.clear();
    m_vecScaleY.clear();
}

void CScaleAnimation::ScaleInit(float scaleX , float scaleY, float m_velocX , float m_velocY)
{
	ScaleAnimation* scaleAniX = new ScaleAnimation;
	scaleAniX->m_scale = scaleX;
	scaleAniX->m_velocity = m_velocX;


    ScaleAnimation* scaleAniY = new ScaleAnimation;
    scaleAniY->m_scale = scaleY;
    scaleAniY->m_velocity = m_velocY;

	m_vecScaleX.push_back(scaleAniX);
    m_vecScaleY.push_back(scaleAniY);
}

void CScaleAnimation::ScaleAnimationUpate(CGameObject* obj)
{

    fPoint scale = obj->GetScale();

    if (m_vecScaleX.size() == 0 || m_curIndexX >= m_vecScaleX.size()) {
        assert(nullptr);
    }

    if (m_vecScaleY.size() == 0 || m_curIndexY >= m_vecScaleY.size()) {
        assert(nullptr);
    }

    if (m_vecScaleX[m_curIndexX]->m_scale > scale.x) {

        scale.x += m_vecScaleX[m_curIndexX]->m_velocity * fDT;

    }
    else {

        scale.x -= m_vecScaleX[m_curIndexX]->m_velocity * fDT;
    }

    if (m_vecScaleY[m_curIndexY]->m_scale > scale.y) {

        scale.y += m_vecScaleY[m_curIndexY]->m_velocity * fDT;

    }
    else {

        scale.y -= m_vecScaleY[m_curIndexY]->m_velocity * fDT;
    }

    obj->SetScale(scale);

    if (abs(m_vecScaleX[m_curIndexX]->m_scale - scale.x) <= 0.1f && abs(m_vecScaleX[m_curIndexX]->m_scale - scale.x) > 0.f) {

        if (m_curIndexX < m_vecScaleX.size() - 1) {
            m_curIndexX++;
        }
        else {

            m_curIndexX = 0;
        }
    }

    if (abs(m_vecScaleY[m_curIndexY]->m_scale - scale.y) <= 0.1f && abs(m_vecScaleY[m_curIndexY]->m_scale - scale.y) > 0.f) {

        if (m_curIndexY < m_vecScaleY.size() - 1) {
            m_curIndexY++;
        }
        else {

            m_curIndexY = 0;
        }
    }





}
