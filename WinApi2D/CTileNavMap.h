#pragma once
#include "CTile.h"
#include "CGameObject.h"
#define INF 100000
class CTileNavMap
{
private:

	

	struct ASNode
	{

		bool active; //활성화 여부
		ASNode* connect; // 이전 정점의 포인터 변수 
		iPoint point; // 현재좌표 
		int f, g, h;  // g 지금 까지 온거리 h예상거리 // f = g+h

		ASNode() {
			active = false;
			connect = nullptr;
			f = INF;
			g = INF;
			h = INF;
		}

		ASNode(const bool& active, ASNode* connect, const iPoint& point, const int& g, const int& h) {

			this->active = active;
			this->connect = connect;
			this->point = point;
			this->g = g;
			this->h = h;
			this->f = g + h;
		}
		~ASNode() {}
	};






	vector<CTile*> m_tileNavVec;

	UINT xSize = 0;
	UINT ySize = 0;


	UINT  m_startX;
	UINT  m_startY;
	UINT  m_EndX;
	UINT  m_EndY;

	CGameObject* m_Objdestination;
	vector<CGameObject*> m_startingPointVec;


	int getH(const iPoint& start, const iPoint& end);
	int getG(int i, int j, const ASNode& node);
	void MonsterRoadUpdate();
public:
	CTileNavMap();
	~CTileNavMap();

	void CreateCTileNavMap();
	UINT GetStartX();
	UINT GetStartY();
	UINT GetEndX();
	UINT GetEndY();
	void CTileNavAstarUpdate();
	void SetStartingPoint(CGameObject* obj);
	void SetDestinaion(CGameObject* obj);
	bool WallCheck(UINT x, UINT y);
};

