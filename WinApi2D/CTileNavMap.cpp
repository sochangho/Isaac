#include "framework.h"
#include "CTileNavMap.h"
#include "CTile.h"
#include "CScene.h"
#include "CMonster.h"
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
	
	CreateCTileNavMap();
}

CTileNavMap::~CTileNavMap()
{
	for (int i = 0; i < m_tileNavVec.size(); i++) {

		m_tileNavVec[i] = nullptr;
	}

	m_tileNavVec.clear();


}

void CTileNavMap::CreateCTileNavMap()
{


	vector<CGameObject*>& tileVec = CSceneManager::getInst()->GetCurScene()->GetTiles();

	for (int i = 0; i < tileVec.size(); i++) {

		CTile* tile = dynamic_cast<CTile*>(tileVec[i]);
		if (tile->GetGroup() == GROUP_TILE::ROAD || tile->GetGroup() == GROUP_TILE::WALL) {


			UINT x = tile->GetX();
			UINT y = tile->GetY();
			TILE_INDEX tileindex;
			tileindex.x = x;
			tileindex.y = y;
			tileMap.insert(make_pair(tileindex.ID, tile->GetGroup()));
			

		}


	}


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

fPoint CTileNavMap::CTileNavRandomUpdate(CGameObject* Monster)
{
	vector<iPoint> i_vec;
	
	random_device rd;
	mt19937_64 gen(rd());

	fPoint  fmonsterPos = Monster->GetPos();
	iPoint  iPos;
	iPos.x = fmonsterPos.x / CTile::SIZE_TILE;
	iPos.y = fmonsterPos.y / CTile::SIZE_TILE;

	
	

	for (int i = -2; i < 3; i++) {
		for (int j = -2; j < 3; j++) {

			if (!((i == 0) && (j == 0)) && WallCheck(iPos.x + i, iPos.y + j)) {
				i_vec.push_back(iPoint(iPos.x + i, iPos.y + j));
			}
		}
	}

	
	

	fPoint resultPos;
	if (i_vec.size() == 0) {

		resultPos.x = iPos.x * CTile::SIZE_TILE;
		resultPos.y = iPos.y * CTile::SIZE_TILE;
		
	}
	else {

	
		uniform_int_distribution<int> dis(0, i_vec.size() - 1);
		resultPos.x = i_vec[dis(gen)].x * CTile::SIZE_TILE;
		resultPos.y = i_vec[dis(gen)].y * CTile::SIZE_TILE;

	}

	resultPos.x += CTile::SIZE_TILE / 2;
	resultPos.y += CTile::SIZE_TILE / 2;

	return resultPos;

}

void CTileNavMap::CTileNavAstarUpdate(CGameObject* objdestination, CGameObject* Monster)
{
	fPoint fdtPos = objdestination->GetPos();
	iPoint idtPos;
	idtPos.x = fdtPos.x / CTile::SIZE_TILE;
	idtPos.y = fdtPos.y / CTile::SIZE_TILE;
	
	//if (!WallCheck(idtPos.x, idtPos.y)) {

	//	for (int i = -1; i < 2; i++) {
	//		for (int j = -1; j < 2; j++) {

	//			if (
	//			
	//				!((i == 0) && (j == 0)) && WallCheck(idtPos.x + i, idtPos.y + j)) {					
	//				idtPos.x += i;
	//				idtPos.y += j;
	//			}

	//		}

	//	}


	//}


			
	list<ASNode> roadList;
	fPoint fstartPos = Monster->GetPos();
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

						pPathNode->point.x += CTile::SIZE_TILE/2;
						pPathNode->point.y += CTile::SIZE_TILE/2;

						path.push_front(pPathNode->point);
						pPathNode = pPathNode->connect;


					}

					CMonster* monster = dynamic_cast<CMonster*>(Monster);

					monster->SetDestination(path);
					break;
				}

				if (miniter == roadList.end()) {
					CMonster* monster = dynamic_cast<CMonster*>(Monster);
					monster->SetDestination(list<iPoint>());
					break;
				}



				for (int i = -1; i < 2; i++) {
					for (int j = -1; j < 2; j++) {

						if (
							!(i == 0 && j == 0) && WallCheck(miniter->point.x + i, miniter->point.y + j)
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



bool CTileNavMap::WallCheck(UINT x, UINT y)
{ 


	TILE_INDEX tileindex;
	tileindex.x = x;
	tileindex.y = y;

	map<ULONGLONG, GROUP_TILE>::iterator iter = tileMap.find(tileindex.ID);

	if (tileMap.end() == iter) {	
		return false;
	}

	if (iter->second == GROUP_TILE::WALL) {

		return false;
	}
	else {

		return true;
	}

}

void CTileNavMap::ChanageTileType(GROUP_TILE type, UINT x, UINT y)
{
	TILE_INDEX tileindex;
	tileindex.x = x;
	tileindex.y = y;
	map<ULONGLONG, GROUP_TILE>::iterator iter = tileMap.find(tileindex.ID);


	if (tileMap.end() == iter) {
		return;
	}


	iter->second = type;


}



