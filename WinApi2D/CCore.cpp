#include "framework.h"
#include "CCore.h"
#include "CGameObject.h"
#include "CTexture.h"

CCore::CCore()
{
	// ���� ȭ���� �׸��� ���� DC �ڵ鰪 �ʱ�ȭ
	m_hDC = 0;
	m_arrPen[0] = 0;
	m_arrBrush[0] = 0;
}

CCore::~CCore()
{
	// ���� �ھ� ���� ������ DC �ڵ鰪 �ݳ�
	ReleaseDC(hWnd, m_hDC);

	for (int i = 0; i < (int)TYPE_PEN::SIZE; i++)
	{
		DeleteObject(m_arrPen[i]);
	}
}

void CCore::update()
{
	// ���� update���� �߰��� �̺�Ʈ�� ������ �ʱ⿡ �Ѳ����� ó��
	CEventManager::getInst()->update();

	CTimeManager::getInst()->update();
	CKeyManager::getInst()->update();
	CSceneManager::getInst()->update();
	CCollisionManager::getInst()->update();
	CCameraManager::getInst()->update();
	CUIManager::getInst()->update();
	CSoundManager::getInst()->update();
}

void CCore::render()
{
	Rectangle(m_pMemTex->GetDC(), -1, -1, WINSIZEX + 1, WINSIZEY + 1);

	CSceneManager::getInst()->render(m_pMemTex->GetDC());
	CCameraManager::getInst()->render(m_pMemTex->GetDC());

	// ������ ��ܿ� FPS ǥ��
	WCHAR strFPS[6];
	swprintf_s(strFPS, L"%5d", CTimeManager::getInst()->GetFPS());
	TextOutW(m_pMemTex->GetDC(), WINSIZEX - 50, 10, strFPS, 5);

	BitBlt(m_hDC, 0, 0, WINSIZEX, WINSIZEY, m_pMemTex->GetDC(), 0, 0, SRCCOPY);
}

void CCore::init()
{
	// GDI
	CreateBrushPen();
	m_hDC = GetDC(hWnd);

	CPathManager::getInst()->init();
	CTimeManager::getInst()->init();
	CKeyManager::getInst()->init();
	CCameraManager::getInst()->init();
	CSceneManager::getInst()->init();
	CCollisionManager::getInst()->init();
	CSoundManager::getInst()->init();

	// ���� ���۸� �뵵�� �ؽ��� ������ ����
	m_pMemTex = CResourceManager::getInst()->CreateTexture(L"BackBuffer", WINSIZEX, WINSIZEY);
}

HDC CCore::GetMainDC()
{
	return m_hDC;
}

void CCore::CreateBrushPen()
{
	// brush
	m_arrBrush[(int)TYPE_BRUSH::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

	// pen
	m_arrPen[(int)TYPE_PEN::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(int)TYPE_PEN::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(int)TYPE_PEN::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}

HBRUSH CCore::GetBrush(TYPE_BRUSH type)
{
	return m_arrBrush[(int)type];
}

HPEN CCore::GetPen(TYPE_PEN type)
{
	return m_arrPen[(int)type];
}
