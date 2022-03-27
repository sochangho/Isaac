#include "framework.h"
#include "CScene_Tool.h"
#include "CTile.h"
#include "resource.h"
#include "CScene.h"
#include "CD2DImage.h"
#include "commdlg.h"
#include "CUI.h"
#include "CPanelUI.h"
#include "CButtonUI.h"
#include "CTileButton.h"
#include "CRock.h"
#include "CGaper.h"
#include "CGaperBodyMonster.h"

INT_PTR CALLBACK TileWinProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

CScene_Tool::CScene_Tool()
{
	m_pMap = nullptr;

	m_hWnd = 0;
	m_iIdx = 0;
	m_gTile = GROUP_TILE::NONE;
	m_velocity = 500;
	m_iTileX = 0;
	m_iTileY = 0;
}

CScene_Tool::~CScene_Tool()
{
}

void CScene_Tool::update()
{
	CScene::update();

	if (KeyDown(VK_TAB))
	{
		ChangeScn(GROUP_SCENE::START);
	}

	if (Key('A'))
	{
		CCameraManager::getInst()->Scroll(fVec2(-1, 0),  m_velocity);
	}
	if (Key('D'))
	{
		CCameraManager::getInst()->Scroll(fVec2(1, 0), m_velocity);
	}
	if (Key('W'))
	{
		CCameraManager::getInst()->Scroll(fVec2(0, -1), m_velocity);
	}
	if (Key('S'))
	{
		CCameraManager::getInst()->Scroll(fVec2(0, 1), m_velocity);
	}

	//SetTileIdx();
    
	if (m_gObject == GROUP_OBJECT::NONE) {
		SetTileGroup();
	}

	if (m_gTile == GROUP_TILE::NONE) {
		SetObjectGroup();
	}
}

void CScene_Tool::render()
{
	const vector<CGameObject*>& vecTile = GetGroupObject(GROUP_GAMEOBJ::TILE);
	for (UINT i = 0; i < vecTile.size(); i++)
	{
		vecTile[i]->render();
	}

	PrintMap();
	PrintTileLine();
	PrintTileGroup();

	const vector<CGameObject*>& vecUI = GetGroupObject(GROUP_GAMEOBJ::UI);
	for (UINT i = 0; i < vecUI.size(); i++)
	{
		vecUI[i]->render();
	}

	const vector<CGameObject*>& vecRock = GetGroupObject(GROUP_GAMEOBJ::ROCK);
	for (int i = 0; i < vecRock.size(); i++) {

		vecRock[i]->render();
	}


}

void CScene_Tool::Enter()
{
	m_hWnd = CreateDialog(hInst, MAKEINTRESOURCE(IDD_TILEBOX), hWnd, TileWinProc);
	ShowWindow(m_hWnd, SW_SHOW);

	CreateTile(20, 20);
	CreateTilePanel();

	CCameraManager::getInst()->SetLookAt(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
}

void CScene_Tool::Exit()
{
	EndDialog(m_hWnd, IDOK);
	DeleteAll();
}

void CScene_Tool::SetIdx(UINT idx)
{
	m_iIdx = idx;
}

void CScene_Tool::SetTileIdx()
{
	if (Key(VK_LBUTTON) || Key(VK_RBUTTON))
	{
		fPoint fptMousePos = MousePos();
		fptMousePos = CCameraManager::getInst()->GetRealPos(fptMousePos);

		int iTileX = m_iTileX;
		int iTileY = m_iTileY;

		int iCol = (int)fptMousePos.x / CTile::SIZE_TILE;
		int iRow = (int)fptMousePos.y / CTile::SIZE_TILE;

		if (fptMousePos.x < 0.f || iTileX <= iCol ||
			fptMousePos.y < 0.f || iTileY <= iRow)
		{
			return;		// 타일이 없는 위치 무시
		}

		UINT iIdx = iRow * iTileX + iCol;
		const vector<CGameObject*>& vecTile = GetGroupObject(GROUP_GAMEOBJ::TILE);
		if (Key(VK_LBUTTON))
			((CTile*)vecTile[iIdx])->SetImgIdx(m_iIdx);
		else if (Key(VK_RBUTTON))
			((CTile*)vecTile[iIdx])->SetImgIdx(0);
	}
}

void CScene_Tool::SetGroup(GROUP_TILE group)
{
	m_gTile = group;
}

void CScene_Tool::SetTileGroup()
{
	



		if (Key(VK_LBUTTON) || Key(VK_RBUTTON))
		{
			fPoint fptMousePos = MousePos();
			fptMousePos = CCameraManager::getInst()->GetRealPos(fptMousePos);

			int iTileX = m_iTileX;
			int iTileY = m_iTileY;

			int iCol = (int)fptMousePos.x / CTile::SIZE_TILE;
			int iRow = (int)fptMousePos.y / CTile::SIZE_TILE;

			if (fptMousePos.x < 0.f || iTileX <= iCol ||
				fptMousePos.y < 0.f || iTileY <= iRow)
			{
				return;		// 타일이 없는 위치 무시
			}

			UINT iIdx = iRow * iTileX + iCol;
			const vector<CGameObject*>& vecTile = GetGroupObject(GROUP_GAMEOBJ::TILE);
			if (Key(VK_LBUTTON))
				((CTile*)vecTile[iIdx])->SetGroup(m_gTile);
			else if (Key(VK_RBUTTON))
				((CTile*)vecTile[iIdx])->SetGroup(GROUP_TILE::NONE);
		}
	
}

void CScene_Tool::SetObjectGroup()
{
	if (KeyDown(VK_LBUTTON) || KeyDown(VK_RBUTTON))
	{
		fPoint fptMousePos = MousePos();
		fptMousePos = CCameraManager::getInst()->GetRealPos(fptMousePos);

		 const vector<CGameObject*>& ui = GetGroupObject(GROUP_GAMEOBJ::UI);

		 if (!(ui[0]->GetPos().x < fptMousePos.x && ui[0]->GetPos().x + ui[0]->GetScale().x > fptMousePos.x
			 && ui[0]->GetPos().y < fptMousePos.y && ui[0]->GetPos().y + ui[0]->GetScale().y > fptMousePos.y
			 )) {

			 if (m_gObject == GROUP_OBJECT::ROCK) {

				 CRock* rock = new CRock;
				 rock->SetFrame(rockFrame.startX, rockFrame.startY, rockFrame.endX, rockFrame.endY);
				 rock->SetPos(fptMousePos);

				 CreateObj(rock, GROUP_GAMEOBJ::ROCK);
			 }
			 else if (m_gObject == GROUP_OBJECT::HART) {



			 }
		 }

	
	}



}

void CScene_Tool::CreateTile(UINT xSize, UINT ySize)
{
	DeleteGroup(GROUP_GAMEOBJ::TILE);

	m_iTileX = xSize;
	m_iTileY = ySize;

	CD2DImage* pImg = CResourceManager::getInst()->LoadD2DImage(L"Tile", L"texture\\tile\\tilemap.bmp");

	for (UINT y = 0; y < ySize; y++)
	{
		for (UINT x = 0; x < xSize; x++)
		{
			CTile* pTile = new CTile();
			pTile->SetPos(fPoint((float)(x * CTile::SIZE_TILE), (float)(y * CTile::SIZE_TILE)));
			pTile->SetX(x);
			pTile->SetY(y);
			pTile->SetD2DImage(pImg);
			AddObject(pTile, GROUP_GAMEOBJ::TILE);
		}
	}
}

void CScene_Tool::SaveTile(const wstring& strPath)
{
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strPath.c_str(), L"wb");		// w : write, b : binary
	assert(pFile);

	UINT xCount = m_iTileX;
	UINT yCount = m_iTileY;
	UINT tileCount = 0;

	const vector<CGameObject*>& vecTile = GetGroupObject(GROUP_GAMEOBJ::TILE);

	for (UINT i = 0; i < vecTile.size(); i++)
	{
		CTile* pTile = (CTile*)vecTile[i];
		if (0 != pTile->GetIdx() || GROUP_TILE::NONE != pTile->GetGroup())
			tileCount++;
	}

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);
	fwrite(&tileCount, sizeof(UINT), 1, pFile);

	for (UINT i = 0; i < vecTile.size(); i++)
	{
		CTile* pTile = (CTile*)vecTile[i];
		if (0 != pTile->GetIdx() || GROUP_TILE::NONE != pTile->GetGroup())
			((CTile*)vecTile[i])->Save(pFile);
	}




	const vector<CGameObject*>& rocks = GetGroupObject(GROUP_GAMEOBJ::ROCK);

	UINT rockObjCount = 0;

	for (UINT i = 0; i < rocks.size(); i++) {
		rockObjCount++;
	}
	fwrite(&rockObjCount, sizeof(UINT), 1, pFile);
	for (int i = 0; i < rocks.size(); i++) {

		CRock* rock = dynamic_cast<CRock*>(rocks[i]);

		if (rock != nullptr) {
			assert(rock);
		}

		UINT x = rock->GetPos().x;
		UINT y = rock->GetPos().y;
		UINT startX = rock->GetFrame().startX;
		UINT startY = rock->GetFrame().startY;
		UINT endX = rock->GetFrame().endX;
		UINT endY = rock->GetFrame().endY;
		fwrite(&x, sizeof(UINT), 1, pFile);
		fwrite(&y, sizeof(UINT), 1, pFile);
		fwrite(&startX, sizeof(UINT), 1, pFile);
		fwrite(&startY, sizeof(UINT), 1, pFile);
		fwrite(&endX, sizeof(UINT), 1, pFile);
		fwrite(&endY, sizeof(UINT), 1, pFile);

	}

	fclose(pFile);
}

void CScene_Tool::LoadTile(const wstring& strPath)
{
	DeleteGroup(GROUP_GAMEOBJ::TILE);
	DeleteGroup(GROUP_GAMEOBJ::ROCK);
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strPath.c_str(), L"rb");      // w : write, b : binary
	assert(pFile);

	UINT xCount = 0;
	UINT yCount = 0;
	UINT tileCount = 0;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);
	fread(&tileCount, sizeof(UINT), 1, pFile);

	CreateTile(xCount, yCount);

	const vector<CGameObject*>& vecTile = GetGroupObject(GROUP_GAMEOBJ::TILE);
	CD2DImage* pImg = CResourceManager::getInst()->LoadD2DImage(L"Tile", L"texture\\tile\\tilemap.bmp");
	CTile* pTile = new CTile;

	for (UINT i = 0; i < tileCount; i++)
	{
		pTile->Load(pFile);
		UINT iIdx = pTile->GetY() * xCount + pTile->GetX();
		((CTile*)vecTile[iIdx])->SetX(pTile->GetX());
		((CTile*)vecTile[iIdx])->SetY(pTile->GetY());
		((CTile*)vecTile[iIdx])->SetImgIdx(pTile->GetIdx());
		((CTile*)vecTile[iIdx])->SetGroup(pTile->GetGroup());
	}

	UINT rockCount = 0;
	fread(&rockCount, sizeof(UINT), 1, pFile);

	for (int i = 0; i < rockCount; i++) {

		UINT x;
		UINT y;
		UINT startX;
		UINT startY;
		UINT endX;
		UINT endY;


		fread(&x, sizeof(UINT), 1, pFile);
		fread(&y, sizeof(UINT), 1, pFile);
		fread(&startX, sizeof(UINT), 1, pFile);
		fread(&startY, sizeof(UINT), 1, pFile);
		fread(&endX, sizeof(UINT), 1, pFile);
		fread(&endY, sizeof(UINT), 1, pFile);

		CRock* rock = new CRock();
		rock->SetPos(fPoint(x, y));
		rock->SetFrame(startX, startY, endX, endY);
		AddObject(rock, GROUP_GAMEOBJ::ROCK);
	}





	fclose(pFile);
}

void CScene_Tool::SaveTileData()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);  // 구조체 사이즈.
	ofn.hwndOwner = hWnd;					// 부모 윈도우 지정.
	wchar_t szName[256] = {};
	ofn.lpstrFile = szName; // 나중에 완성된 경로가 채워질 버퍼 지정.
	ofn.nMaxFile = sizeof(szName); // lpstrFile에 지정된 버퍼의 문자 수.
	ofn.lpstrFilter = L"ALL\0*.*\0tile\0*.tile"; // 필터 설정
	ofn.nFilterIndex = 0; // 기본 필터 세팅. 0는 all로 초기 세팅됨. 처음꺼.
	ofn.lpstrFileTitle = nullptr; // 타이틀 바
	ofn.nMaxFileTitle = 0; // 타이틀 바 문자열 크기. nullptr이면 0.
	wstring strTileFolder = CPathManager::getInst()->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str(); // 초기경로. 우리는 타일 저장할거기 때문에, content->tile 경로로 해두자.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // 스타일

	if (GetSaveFileName(&ofn))
	{
		SaveTile(szName);
	}
}

void CScene_Tool::LoadTileData()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);  // 구조체 사이즈.
	ofn.hwndOwner = hWnd; // 부모 윈도우 지정.
	wchar_t szName[256] = {};
	ofn.lpstrFile = szName; // 나중에 완성된 경로가 채워질 버퍼 지정.
	ofn.nMaxFile = sizeof(szName); // lpstrFile에 지정된 버퍼의 문자 수.
	ofn.lpstrFilter = L"ALL\0*.*\0tile\0*.tile"; // 필터 설정
	ofn.nFilterIndex = 0; // 기본 필터 세팅. 0는 all로 초기 세팅됨. 처음꺼.
	ofn.lpstrFileTitle = nullptr; // 타이틀 바
	ofn.nMaxFileTitle = 0; // 타이틀 바 문자열 크기. nullptr이면 0.
	wstring strTileFolder = CPathManager::getInst()->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str(); // 초기경로. 우리는 타일 저장할거기 때문에, content->tile 경로로 해두자.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // 스타일

	if (GetOpenFileName(&ofn))
	{
		LoadTile(szName);
	}
}

void CScene_Tool::LoadMap()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);  // 구조체 사이즈.
	ofn.hwndOwner = hWnd; // 부모 윈도우 지정.
	wchar_t szName[256] = {};
	ofn.lpstrFile = szName; // 나중에 완성된 경로가 채워질 버퍼 지정.
	ofn.nMaxFile = sizeof(szName); // lpstrFile에 지정된 버퍼의 문자 수.
	ofn.lpstrFilter = L"ALL\0*.*\0Image\0*.png"; // 필터 설정
	ofn.nFilterIndex = 0; // 기본 필터 세팅. 0는 all로 초기 세팅됨. 처음꺼.
	ofn.lpstrFileTitle = nullptr; // 타이틀 바
	ofn.nMaxFileTitle = 0; // 타이틀 바 문자열 크기. nullptr이면 0.
	wstring strTileFolder = CPathManager::getInst()->GetContentPath();
	strTileFolder += L"map";
	ofn.lpstrInitialDir = strTileFolder.c_str(); // 초기경로. 우리는 타일 저장할거기 때문에, content->tile 경로로 해두자.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // 스타일

	if (GetOpenFileName(&ofn))
	{
		m_pMap = CResourceManager::getInst()->LoadToolD2DImage(szName);
	}
}

void ClickTileGroupButton(DWORD_PTR param1, DWORD_PTR param2)
{
	// param1 : Scene_tool
	// param2 : CButtonUI
	CScene_Tool* scene_tool = (CScene_Tool*)param1;
	CButtonUI* button = (CButtonUI*)param2;
	scene_tool->ClickTileGroup(button);
}

void ClickObjectGroupButton(DWORD_PTR param1, DWORD_PTR param2) {

	CScene_Tool* scene_tool = (CScene_Tool*)param1;
	CButtonUI* button = (CButtonUI*)param2;
	scene_tool->ClickObjectGroup(button);
}

void CScene_Tool::ClickObjectGroup(CButtonUI* button)
{
	if (m_gObject == GROUP_OBJECT::NONE)
	{
		m_gObject = GROUP_OBJECT::ROCK;
		
		button->SetText(L"ROCK");
	}
	else if (m_gObject == GROUP_OBJECT::ROCK)
	{
		m_gObject = GROUP_OBJECT::HART;
			
		button->SetText(L"HART");
	}
	else if (m_gObject == GROUP_OBJECT::HART)
	{
		m_gObject = GROUP_OBJECT::NONE;

		button->SetText(L"NONE");
	}




}

void CScene_Tool::ClickTileGroup(CButtonUI* button)
{
	if (m_gTile == GROUP_TILE::NONE)
	{
		m_gTile = GROUP_TILE::GROUND;
		button->SetText(L"Ground");
	}
	else if (m_gTile == GROUP_TILE::GROUND)
	{
		m_gTile = GROUP_TILE::WALL;
		button->SetText(L"WALL");
	}
	else if (m_gTile == GROUP_TILE::WALL)
	{
		m_gTile = GROUP_TILE::ROAD;
		button->SetText(L"ROAD_START");
	}
	else if (m_gTile == GROUP_TILE::ROAD) {
		m_gTile = GROUP_TILE::NONE;
		button->SetText(L"NONE");

	}
	
}

void ClickTileButton(DWORD_PTR param1, DWORD_PTR param2)
{
	// param1 : Scene_tool
	// param2 : CTileButton
	CScene_Tool* scene_tool = (CScene_Tool*)param1;
	CTileButton* button = (CTileButton*)param2;
	scene_tool->ClickTile(button);
}


void ClickRockTileBotton(DWORD_PTR param1, DWORD_PTR param2) {

	CScene_Tool* scene_tool = (CScene_Tool*)param1;
	CTileButton* button = (CTileButton*)param2;

	fPoint pos = button->GetPos();
	fPoint scale = button->GetScale();
	scene_tool->SetRockFrame(pos.x  , pos.y , pos.x + scale.x , pos.y +scale.y);

}

void CScene_Tool::ClickTile(CTileButton* button)
{
	SetIdx(button->GetIdx());
}

RockFrame CScene_Tool::GetRockFrame()
{
	return rockFrame;
}

void CScene_Tool::SetRockFrame(UINT x, UINT y, UINT w, UINT H)
{
	rockFrame.startX = x;
	rockFrame.startY = y;
	rockFrame.endX = w;
	rockFrame.endY = H;
}

void CScene_Tool::CreateTilePanel()
{
	CPanelUI* panelTile = new CPanelUI;
	panelTile->SetName(L"panelTile");
	panelTile->SetScale(fPoint(400.f, 600.f));
	panelTile->SetPos(fPoint(WINSIZEX - 450.f, 50.f));

	CD2DImage* pImg = CResourceManager::getInst()->LoadD2DImage(L"Rock", L"texture\\map\\rocks_basement.png");
	for (UINT y = 0; y < 8; y++)
	{
		for (UINT x = 0; x < 4; x++)
		{
			CTileButton* btnTile = new CTileButton;
			btnTile->SetScale(fPoint(CTile::SIZE_TILE, CTile::SIZE_TILE));
			btnTile->SetPos(fPoint((float)x * CTile::SIZE_TILE, (float)y * CTile::SIZE_TILE));
			//btnTile->SetPos(btnTile->GetPos() + fPoint(8.f, 8.f));
			btnTile->SetImage(pImg);
			btnTile->SetIdx(y * 4 + x);
			btnTile->SetClickedCallBack(ClickRockTileBotton, (DWORD_PTR)this, (DWORD_PTR)btnTile);
			panelTile->AddChild(btnTile);
		}
	}

	CButtonUI* btnTileGroup = new CButtonUI;
	btnTileGroup->SetScale(fPoint(100.f, 50.f));
	btnTileGroup->SetPos(fPoint(50.f, 500.f));
	btnTileGroup->SetText(L"NONE");
	btnTileGroup->SetClickedCallBack(ClickTileGroupButton, (DWORD_PTR)this, (DWORD_PTR)btnTileGroup);
	panelTile->AddChild(btnTileGroup);


	CButtonUI* btnTileGroup1 = new CButtonUI;
	btnTileGroup1->SetScale(fPoint(100.f, 50.f));
	btnTileGroup1->SetPos(fPoint(200.f, 500.f));
	btnTileGroup1->SetText(L"NONE");
	btnTileGroup1->SetClickedCallBack(ClickObjectGroupButton, (DWORD_PTR)this, (DWORD_PTR)btnTileGroup1);
	panelTile->AddChild(btnTileGroup1);




	AddObject(panelTile, GROUP_GAMEOBJ::UI);
}

void CScene_Tool::PrintMap()
{
	if (nullptr == m_pMap)
		return;

	fPoint pos = CCameraManager::getInst()->GetLookAt();
	pos = pos - fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f);

	CRenderManager::getInst()->RenderImage(
		m_pMap,
		0 - pos.x,
		0 - pos.y,
		2 * m_pMap->GetWidth() - pos.x,
		2 * m_pMap->GetHeight() - pos.y
	);
}

void CScene_Tool::PrintTileLine()
{
	fPoint pos = CCameraManager::getInst()->GetLookAt();
	pos = pos - fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f);

	// 가로줄 출력
	for (UINT y = 0; y <= m_iTileY; y++)
	{
		CRenderManager::getInst()->RenderLine(
			fPoint(0 - pos.x, y * CTile::SIZE_TILE - pos.y),
			fPoint(CTile::SIZE_TILE * m_iTileX - pos.x, y * CTile::SIZE_TILE - pos.y)
		);
	}

	// 세로줄 출력
	for (UINT x = 0; x <= m_iTileX; x++)
	{
		CRenderManager::getInst()->RenderLine(
			fPoint(x * CTile::SIZE_TILE - pos.x, 0 - pos.y),
			fPoint(x * CTile::SIZE_TILE - pos.x, CTile::SIZE_TILE * m_iTileY - pos.y)
		);
	}
}

void CScene_Tool::PrintTileGroup()
{
	fPoint pos = CCameraManager::getInst()->GetLookAt();
	pos = pos - fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f);

	const vector<CGameObject*>& vecTile = GetGroupObject(GROUP_GAMEOBJ::TILE);
	CTile* pTile;

	for (UINT i = 0; i < vecTile.size(); i++)
	{
		pTile = (CTile*)vecTile[i];
		if (GROUP_TILE::GROUND == pTile->GetGroup())
		{
			CRenderManager::getInst()->RenderEllipse(
				pTile->GetPos().x + CTile::SIZE_TILE / 2.f - pos.x,
				pTile->GetPos().y + CTile::SIZE_TILE / 2.f - pos.y,
				CTile::SIZE_TILE / 2.f,
				CTile::SIZE_TILE / 2.f,
				RGB(255, 0, 0),
				3.f
			);
		}
		else if (GROUP_TILE::WALL == pTile->GetGroup())
		{
			CRenderManager::getInst()->RenderEllipse(
				pTile->GetPos().x + CTile::SIZE_TILE / 2.f - pos.x,
				pTile->GetPos().y + CTile::SIZE_TILE / 2.f - pos.y,
				CTile::SIZE_TILE / 2.f,
				CTile::SIZE_TILE / 2.f,
				RGB(0, 255, 0),
				3.f
			);
		}
		else if (GROUP_TILE::ROAD == pTile->GetGroup()) {

			CRenderManager::getInst()->RenderEllipse(
				pTile->GetPos().x + CTile::SIZE_TILE / 2.f - pos.x,
				pTile->GetPos().y + CTile::SIZE_TILE / 2.f - pos.y,
				CTile::SIZE_TILE / 2.f,
				CTile::SIZE_TILE / 2.f,
				RGB(0, 255, 255),
				3.f
			);

		}
	
	}
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK TileWinProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_SAVE)
		{
			CScene* pCurScene = CSceneManager::getInst()->GetCurScene();

			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->SaveTileData();

			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDC_LOAD)
		{
			CScene* pCurScene = CSceneManager::getInst()->GetCurScene();

			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->LoadTileData();

			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDC_MAP)
		{
			CScene* pCurScene = CSceneManager::getInst()->GetCurScene();

			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->LoadMap();

			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDC_BUTTON_SIZE)
		{
			int x = GetDlgItemInt(hDlg, IDC_EDIT_SIZEX, nullptr, false);
			int y = GetDlgItemInt(hDlg, IDC_EDIT_SIZEY, nullptr, false);

			CScene* pCurScene = CSceneManager::getInst()->GetCurScene();

			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->DeleteGroup(GROUP_GAMEOBJ::TILE);
			pToolScene->CreateTile(x, y);
		}
		break;
	}
	return (INT_PTR)FALSE;
}