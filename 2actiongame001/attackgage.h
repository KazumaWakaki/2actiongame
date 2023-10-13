//=============================================================================
//
// [attackgage.h]
// Author ��� ��^
//
//=============================================================================
#ifndef _ATTACKGAGE_H_  //���̃}�N����`������Ȃ�������
#define _ATTACKGAGE_H_  //2�d�C���N���[�h�h�~�̃}�N����`

#include "object2D.h"

class CPlayer3D;

//�A�^�b�N�Q�[�W�N���X
class CAttackGage : public CObject2D
{
public:
	//�e�N�X�`���^�C�v���
	typedef enum
	{
		TYPE_ATTACKGAUGE = 0,  //�A�^�b�N�Q�[�W
		TYPE_ATTACKFRAME,  //�A�^�b�N�Q�[�W�g
		TYPE_MAX
	}TEXTYPE;

	//�Q�[�W�̒i�K����
	typedef enum
	{
		TYPE_GAUGE_1 = 0,  //�A�^�b�N�Q�[�W1
		TYPE_GAUGE_2,  //�A�^�b�N�Q�[�W2
		TYPE_GAUGE_3,  //�A�^�b�N�Q�[�W3
		TYPE_GAUGE_4,  //�A�^�b�N�Q�[�W4
		TYPE_GAUGE_5,  //�A�^�b�N�Q�[�W5
		TYPE_GAUGE_MAX
	}GAGETYPE;

	CAttackGage();   //�R���X�g���N�^
	~CAttackGage();  //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);  //����������
	void Uninit(void);  //�I������
	void Update(void);  //�X�V����
	void Draw(void);  //�`�揈��
	static CAttackGage *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 scale, int SetTypeTex);  //�A�^�b�N�Q�[�W����

	//�擾
	int GetGage(void) { return m_Gage; };  //�Q�[�W�̒i�K�擾

	//�ݒ�
	void SetAttackGage(int Gage);

private:
	int m_nID;  //�ԍ�
	int m_nLife;  //����
	int m_nIdxTexture[TYPE_MAX];  //�e�N�X�`��
	int m_Gage;  //�Q�[�W�̒i�K�Ǘ�
	static CAttackGage *m_apObject;  //�I�u�W�F�N�g�N���X�̃|�C���^
};

#endif