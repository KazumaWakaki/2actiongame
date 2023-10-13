//=============================================================================
//
// [modelset.h]
// Author ��� ��^
//
//=============================================================================
#ifndef _MODELSET_H_  //���̃}�N����`������ĂȂ�������
#define _MODELSET_H_  //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "objectX.h"
#include "model.h"

class CPlayer3D;

//���f���ݒ�N���X
class CModelSet : public CObjectX
{
public:
	//���f���^�C�v���
	typedef enum
	{
		TYPE_GATE_1 = 0,  //�Q�[�g1
		TYPE_GATE_2,  //�Q�[�g2
		TYPE_GATE_3,  //�Q�[�g3
		TYPE_KOIN,  //�R�C��
		TYPE_MAX
	}TYPE;

	CModelSet();   //�R���X�g���N�^
	~CModelSet();  //�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(void);  //����������
	virtual void Uninit(void);	 //�I������
	virtual void Update(void);  //�X�V����
	virtual void Draw(void);  //�`�揈��
	static CModelSet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 size, int SetTypeTex);  //��������

	//�����蔻�菈��
	static bool ModelCollision(CPlayer3D *pPlayer);  //�v���C���[�Ƃ̓����蔻�菈��

private:
	int m_nID;  //�ԍ�
	int m_nIdxTexture[TYPE_MAX];   //�e�N�X�`���ۑ�
	int m_nIdxModel[TYPE_MAX];     //���f�����蓖��
	static CModelSet *m_apObject[MAX_MODEL];  //�I�u�W�F�N�g�N���X�̃|�C���^
};

#endif