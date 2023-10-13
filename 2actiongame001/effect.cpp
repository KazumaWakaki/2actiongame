//=============================================================================
//
// �G�t�F�N�g���� [effect.cpp]
// Author ��� ��^
//
//=============================================================================
#include "effect.h"
#include "manager.h"

//�}�N����`
#define EXPLOSIONAMIME (5)         //�A�j���[�V�������x
#define EXPLOSIONPATTERNAMIME (8)  //�A�j���[�V�����p�^�[����
#define TEXSIZE_X	(20.0f)        //�e�N�X�`���̃T�C�YX
#define TEXSIZE_Y	(20.0f)        //�e�N�X�`���̃T�C�YY
#define TEXSIZE_Z	(20.0f)        //�e�N�X�`���̃T�C�YZ
#define LIFE	    (20)           //����

//-------------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------------
CEffect::CEffect()
{
	SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //�ʒu�̏�����
	SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));      //�T�C�Y�̏�����
}
//-------------------------------------------------------
//�f�X�g���N�^
//-------------------------------------------------------
CEffect::~CEffect()
{

}
//-------------------------------------------------------
//����������
//-------------------------------------------------------
HRESULT CEffect::Init()
{
	CTexture *pTexture = CManager::GetTexture();

	m_nIdxTexture = pTexture->Regist("data\\texture\\kizuato001.png");

	//�T�C�Y������
	SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�I�u�W�F�N�g�r���{�[�h�̏���������
	CBillboard::Init();

	//��ނ̐ݒ�
	SetType(TYPE_EFFECT);

	return (S_OK);
}
//-------------------------------------------------------
//�I������
//-------------------------------------------------------
void CEffect::Uninit()
{
	//�I�u�W�F�N�g�r���{�[�h�̏I������
	CBillboard::Uninit();
}
//-------------------------------------------------------
//�X�V����
//-------------------------------------------------------
void CEffect::Update()
{
	D3DXVECTOR3 m_pos = GetPosition();  //�ʒu�̎擾

	CBillboard::SetVtx();

	//�ʒu�̐ݒ�
	SetPosition(m_pos);

	m_nLife++;

	//�e��������܂ł̃J�E���g
	if (m_nLife >= LIFE)
	{
		//�폜����
		Uninit();

		m_nLife = 0;  //0�ɖ߂�
	}

	//-------------------------------------------------------
	//�f�o�b�N�\��
	//-------------------------------------------------------
	CManager::GetDebugProc()->Print("�G�t�F�N�g�ʒu [%f, %f, %f]\n", m_pos.x, m_pos.y, m_pos.z);
}
//-------------------------------------------------------
//�`�揈��
//-------------------------------------------------------
void CEffect::Draw()
{
	//�I�u�W�F�N�g�r���{�[�h�̕`�揈��
	CBillboard::Draw();
}
//-------------------------------------------------------
//��������
//-------------------------------------------------------
CEffect *CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CEffect *pEffect;

	//�G�t�F�N�g�̐���
	pEffect = new CEffect;

	//pEffect��NULL����Ȃ�������
	if (pEffect != NULL)
	{
		//�G�t�F�N�g�̏���������
		pEffect->Init();

		//�G�t�F�N�g�̈ʒu�̐ݒ�
		pEffect->SetPosition(pos);

		//�G�t�F�N�g�̃T�C�Y
		pEffect->SetSize(size);

		//�F�̐ݒ�
		//pEffect->SetCol(col);

		//�e�N�X�`���̊��蓖��
		pEffect->BindTexture(pEffect->m_nIdxTexture);
	}

	else
	{//�����Ɏ��s�����ꍇ
		return NULL;
	}

	return pEffect;
}