#pragma once
#include "CScene.h"

class CD2DImage;
class CButtonUI;
class CTileButton;



class CScene_Tool : public CScene
{
private:
	CD2DImage* m_pMap;

	HWND m_hWnd;
	UINT m_iIdx;
	GROUP_TILE m_gTile;
	GROUP_OBJECT m_gObject;
	float m_velocity;

	UINT m_iTileX;
	UINT m_iTileY;

	RockFrame rockFrame;

public:
	CScene_Tool();
	~CScene_Tool();

	virtual void update();
	virtual void render();

	virtual void Enter();
	virtual void Exit();

	void SetIdx(UINT idx);
	void SetTileIdx();		// ���콺�� ��ȣ�ۿ��ؼ� Ÿ���� �ٲ�.
	void SetGroup(GROUP_TILE group);
	void SetTileGroup();
	void SetObjectGroup();

	void CreateTile(UINT xSize, UINT ySize);
	void SaveTile(const wstring& strPath);
	void LoadTile(const wstring& strPath);
	
	void SaveTileData();
	void LoadTileData();
	void LoadMap();

	void ClickObjectGroup(CButtonUI* button);
	void ClickTileGroup(CButtonUI* button);
	void ClickTile(CTileButton* button);

	RockFrame GetRockFrame();
	void SetRockFrame(UINT x , UINT y , UINT w, UINT  H);
	
private:
	void CreateTilePanel();

	void PrintMap();
	void PrintTileLine();
	void PrintTileGroup();


};

