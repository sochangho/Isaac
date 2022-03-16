#pragma once

class CAnimator;
class CTexture;

struct tAniFrm
{
	fPoint fptLT;
	fPoint fptSlice;
	fPoint fptOffset;
	float fDuration;
};

class CAnimation
{
	friend class CAnimator;

private:
	wstring			m_strName;		// �ִϸ��̼� �̸�
	CAnimator*		m_pAnimator;	// �ִϸ�����
	CTexture*		m_pTex;			// �ִϸ��̼� �̹���
	vector<tAniFrm> m_vecFrm;		// ��� �������� �ڸ��� ���� �� �����ð�
	int				m_iCurFrm;		// ���� �������� index
	float			m_fAccTime;		// ���� �����ӱ��� �����ð�

public:
	CAnimation();
	~CAnimation();

	void SetName(const wstring& strName);
	const wstring& GetName();

	void SetFrame(int frmIndex);
	tAniFrm& GetFrame(int frmIndex);

	void update();
	void render(HDC hDC);	

	void Create(CTexture* tex, fPoint lt, fPoint slice, fPoint step, float duration, UINT frmCount);	// �ִϸ��̼� ����
};

