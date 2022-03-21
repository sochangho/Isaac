#include "framework.h"
#include "CMonster.h"
#include "CCollider.h"
#include "CD2DImage.h"
#include "CAnimator.h"
#include "CTile.h"
#include "CScene.h"
CMonster::CMonster()
{
}

CMonster::~CMonster()
{
}

void CMonster::update()
{
	if (!is_stop) {
		GoDestition();
	}
}

void CMonster::render()
{

	fPoint fptRenderPos = CCameraManager::getInst()->GetRenderPos(GetPos());
	CRenderManager::getInst()->RenderRectangle(
		fptRenderPos.x - GetScale().x / 2,
		fptRenderPos.y - GetScale().y / 2,
		fptRenderPos.x + GetScale().x / 2,
		fptRenderPos.y + GetScale().y / 2);


	COLORREF rgb = RGB(0, 0, 255);	
	for (auto iter = m_destinations.begin(); iter != m_destinations.end(); iter++) {

		fPoint pos;
		pos.x = iter->x;
		pos.y = iter->y;
		fPoint fptRenderPos = CCameraManager::getInst()->GetRenderPos(pos);
		CRenderManager::getInst()->RenderRectangle(
			fptRenderPos.x - CTile::SIZE_TILE / 2,
			fptRenderPos.y - CTile::SIZE_TILE / 2,
			fptRenderPos.x + CTile::SIZE_TILE / 2,
			fptRenderPos.y + CTile::SIZE_TILE / 2 , rgb);

	}

}

void CMonster::SetDestination(const list<iPoint>& des)
{
	is_stop = true;
	m_destinations.clear();
	m_destinations = des;		
	m_curIter = m_destinations.begin();
	is_stop = false;

}

void CMonster::GoDestition()
{
	fPoint monsterPos = GetPos();

	if (m_curIter != m_destinations.end()) {
		
		m_dirVec2.x = (float)m_curIter->x - monsterPos.x;
		m_dirVec2.y = (float)m_curIter->y - monsterPos.y;
	}
	else {

		//CSceneManager::getInst()->GetCurScene()->GettileNav()->CTileNavAstarUpdate();
		
	}


	if ( m_dirVec2.Length() >= 0.01f) {
	
		monsterPos.x += m_dirVec2.normalize().x * m_veclocity * fDT;
		monsterPos.y += m_dirVec2.normalize().y * m_veclocity * fDT;
		SetPos(monsterPos);		
	}
	else {



		if (m_curIter != m_destinations.end()) {

			m_curIter++;
			
		}


	}
	


}
