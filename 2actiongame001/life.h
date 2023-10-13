//=============================================================================
//
// [life.h]
// Author ��� ��^
//
//=============================================================================
#ifndef _LIFE_H_  //���̃}�N����`������Ȃ�������
#define _LIFE_H_  //2�d�C���N���[�h�h�~�̃}�N����`

#include "object2D.h"

class CPlayer3D;
class CEnemy3D;

//���C�t�N���X
class CLife : public CObject2D
{
public:
	//�e�N�X�`���^�C�v���
	typedef enum
	{
		TYPE_LIFEGAUGE = 0,  //���C�t�Q�[�W
		TYPE_LIFEFRAME,  //���C�t�g
		TYPE_MAX
	}TEXTYPE;

	CLife();   //�R���X�g���N�^
	~CLife();  //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);  //����������
	void Uninit(void);  //�I������
	void Update(void);  //�X�V����
	void Draw(void);  //�`�揈��
	static CLife *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 scale, int SetTypeTex);  //���C�t����
	static void LifeMove(CPlayer3D *pPlayer);  //�v���C���[�ݒ菈��
	static void DrawAnim(CEnemy3D *pEnemy);  //�G�ݒ菈��

private:
	int m_nID;  //�ԍ�
	int m_nLife;  //����
	int m_nIdxTexture[TYPE_MAX];  //�e�N�X�`��
	static CLife *m_apObject;  //�I�u�W�F�N�g�N���X�̃|�C���^
};

#endif