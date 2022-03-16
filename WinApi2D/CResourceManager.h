#pragma once

class CTexture;
class CSound;

class CResourceManager
{
	SINGLETON(CResourceManager);

private:
	map<wstring, CTexture*> m_mapTex;		// Texture 리소스의 저장 자료구조
	map<wstring, CSound*> m_mapSound;		// Sound 리소스의 저장 자료구조
	CSound* m_pBGM;							// BGM 리소스의 저장 변수

public:
	CTexture* FindTexture(const wstring& strKey);	// 저장된 Texture 탐색
	CTexture* LoadTextrue(const wstring& strKey, const wstring& strRelativePath);	// Texture 불러오기 이미 있는 경우 있던 Texture 반환
	CTexture* CreateTexture(const wstring& strKey, UINT width, UINT height);

	CSound* FindSound(const wstring& strKey);		// 저장된 Sound 탐색
	CSound* LoadSound(const wstring& strKey, const wstring& strRelativePath);	// Sound 불러오기 이미 있는 경우 있던 Sound 반환

	CSound* LoadBGM(const wstring& strKey, const wstring& strRelativePath);		// BGM 불러오기 이미 있는 경우 있던 BGM 반환
};

