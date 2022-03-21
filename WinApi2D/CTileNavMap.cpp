#include "framework.h"
#include "CTileNavMap.h"
#include "CTile.h"
#include "CScene.h"

int CTileNavMap::getH(const iPoint& start, const iPoint& end)
{
	int xSize = abs(start.x - end.x);		// 가로로 가야 하는 횟수
	int ySize = abs(start.y - end.y);		// 세로로 가야 하는 횟수

	int straight;		// 직선으로 가야 하는 횟수
	int diagonal;		// 대각선으로 가야 하는 횟수

	if (xSize > ySize)
		diagonal = ySize;
	else
		diagonal = xSize;

	int large;
	if (xSize > ySize)
		large = xSize;
	else
		large = ySize;

	straight = large - diagonal;

	return 10 * straight + 14 * diagonal;
}

int CTileNavMap::getG(int i, int j, const ASNode& node)
{
	return i * j == 0 ? node.g + 10 : node.g + 14;
}

CTileNavMap::CTileNavMap()
{
	m_Objdestination = nullptr;
	CreateCTileNavMap();
}

CTileNavMap::~CTileNavMap()
{
	for (int i = 0; i < m_tileNavVec.size(); i++) {

		m_tileNavVec[i] = nullptr;
	}

	m_tileNavVec.clear();

	if (m_Objdestination != nullptr) {

		m_Objdestination = nullptr;
	}


	for (int i = 0; i < m_startingPointVec.size(); i++) {
		m_startingPointVec[i] = nullptr;
	}


}

void CTileNavMap::CreateCTileNavMap()
{


	vector<CGameObject*>& tileVec = CSceneManager::getInst()->GetCurScene()->GetTiles();

	for (int i = 0; i < tileVec.size(); i++) {

		CTile* tile = dynamic_cast<CTile*>(tileVec[i]);
		if (tile->GetGroup() == GROUP_TILE::ROAD || tile->GetGroup() == GROUP_TILE::WALL) {

			m_tileNavVec.push_back(tile);

		}


	}

	m_startX =  m_tileNavVec[0]->GetX();
	m_startY = m_tileNavVec[0]->GetY();
	m_EndX = m_tileNavVec[m_tileNavVec.size() - 1]->GetX();
	m_EndY = m_tileNavVec[m_tileNavVec.size() - 1]->GetY();

	xSize = m_EndX - m_startX + 1;
	ySize = m_EndY - m_startY + 1;
}



UINT CTileNavMap::GetStartX()
{
    return m_startX;
}

UINT CTileNavMap::GetStartY()
{
    return m_startY;
}

UINT CTileNavMap::GetEndX()
{
    return m_EndX;
}

UINT CTileNavMap::GetEndY()
{
    return m_EndY;
}

void CTileNavMap::CTileNavAstarUpdate()
{
	fPoint fdtPos = m_Objdestination->GetPos();
	iPoint idtPos;
	idtPos.x = fdtPos.x / CTile::SIZE_TILE;
	idtPos.y = fdtPos.y / CTile::SIZE_TILE;

	for (int mi = 0; mi < m_startingPointVec.size(); mi++) {

		list<ASNode> roadList;
		fPoint fstartPos = m_startingPointVec[mi]->GetPos();
		iPoint istartPos;

		istartPos.x = fstartPos.x / CTile::SIZE_TILE;
		istartPos.y = fstartPos.y / CTile::SIZE_TILE;

		ASNode startNode(true, nullptr, istartPos, 0, getH(istartPos, idtPos));
		roadList.push_back(startNode);

		while (true) {

			list<ASNode>::iterator miniter = roadList.end();
			int minF = INF;
			for (list<ASNode>::iterator iter = roadList.begin(); iter != roadList.end(); iter++) {

				if ((iter->active == true) && (iter->f < minF)) {

					miniter = iter;
					minF = iter->f;
				}

			}

			if (miniter != roadList.end() && miniter->point == idtPos) {

				ASNode endNode = *miniter;
				ASNode* pPathNode = &endNode;
				list<iPoint> path;
				while (pPathNode != nullptr) {

					pPathNode->point.x *= CTile::SIZE_TILE;
					pPathNode->point.y *= CTile::SIZE_TILE;
					path.push_front(pPathNode->point);
					pPathNode = pPathNode->connect;


				}

				m_startingPointVec[mi]->SetDestionations(path);
				break;
			}

			if (miniter == roadList.end()) {

				m_startingPointVec[mi]->SetDestionations(list<iPoint>());
				break;
			}



			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {

					if (miniter->point.x + i > GetStartX() && miniter->point.y + j > GetStartY()
						&& miniter->point.x + i < GetEndX() && miniter->point.y + j < GetEndY()
						&& !(i == 0 && j == 0) 
						) {

						iPoint newPoint(miniter->point.x + i, miniter->point.y + j);

						int newG = getG(i, j, *miniter);
						int newH = getH(newPoint, idtPos);
						int newF = newG + newH;

						bool find = false;

						for (list<ASNode>::iterator iter = roadList.begin(); iter != roadList.end(); iter++) {

							if (iter->point == newPoint) {

								if (iter->f > newF) {

									iter->g = newG;
									iter->h = newH;
									iter->f = newF;
									iter->connect = &(*miniter);
								}


								find = true;
								break;
							}
						}

						if (!find) {


							ASNode newNode(true, &(*miniter), newPoint, newG, newH);
							roadList.push_back(newNode);

						}
					}
				}

			}

			miniter->active = false;

		}

	}

}

void CTileNavMap::SetStartingPoint(CGameObject* obj)
{
	m_startingPointVec.push_back(obj);
}

void CTileNavMap::SetDestinaion(CGameObject* obj)
{
	m_Objdestination = obj;
}
