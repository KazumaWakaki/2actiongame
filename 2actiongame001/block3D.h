//=============================================================================
//
//[block3D.h]
//Author ��� ��^
//
//=============================================================================
#ifndef _BLOCK3D_H_  //���̃}�N����`������ĂȂ�������
#define _BLOCK3D_H_  //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "objectX.h"

//�}�N����`
#define BLOCKSPEED   (3.0f)    //�ړ����̃X�s�[�h
#define BLOCKSPEEDUP (0.15f)   //�ړ��ʍX�V���̃X�s�[�h
#define MAX_BLOCK (128)   //�u���b�N�̍ő吔

class CPlayer3D;
class CEnemy3D;

//�u���b�N3D�N���X
class CBlock3D : public CObjectX
{
public:
	CBlock3D();   //�R���X�g���N�^
	~CBlock3D();  //�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(void);                                                   //����������
	virtual void Uninit(void);	                                                  //�I������
	virtual void Update(void);	                                                  //�X�V����
	virtual void Draw(void);	                                                  //�`�揈��
	static CBlock3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 size);  //��������

	//�����蔻��
	static bool CollisionPlayer(CPlayer3D *pPlayer);  //�v���C���[�Ƃ̓����蔻��
	static bool CollisionEnemy(CEnemy3D *pEnemy);   //�G�Ƃ̓����蔻��

private:
	int m_nID;  //�ԍ�
	int m_nIdxTexture;   //�e�N�X�`���ۑ�
	int m_nIdxModel;     //���f�����蓖��
	static CBlock3D *m_apObject[MAX_BLOCK];  //�I�u�W�F�N�g�N���X�̃|�C���^
};

#endif