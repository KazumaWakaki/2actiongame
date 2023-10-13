//=============================================================================
//
// [effect.h]
// Author ��� ��^
//
//=============================================================================
#ifndef _EFFECT_H_  //���̃}�N����`������ĂȂ�������
#define _EFFECT_H_  //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "billboard.h"

//�G�t�F�N�g�N���X
class CEffect : public CBillboard
{
public:
	CEffect();   //�R���X�g���N�^
	~CEffect();  //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);  //����������
	void Uninit(void);	 //�I������
	void Update(void);	 //�X�V����
	void Draw(void);	 //�`�揈��
	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);  //�G�t�F�N�g����

private:
	D3DXCOLOR m_col;    //�F
	int m_nLife;		//����
	int m_nIdxTexture;  //�e�N�X�`��
};

#endif