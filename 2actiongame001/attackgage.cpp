//=============================================================================
//
// �A�^�b�N�Q�[�W���� [life.cpp]
// Author�F��؈�^
//
//=============================================================================
#include "manager.h"
#include "attackgage.h"
#include "player3D.h"

//�ÓI�����o�ϐ�
CAttackGage *CAttackGage::m_apObject = NULL;

//-------------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------------
CAttackGage::CAttackGage()
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apObject == NULL)
		{
			m_apObject = this;

			m_nID = nCnt;

			break;
		}
	}
}
//-------------------------------------------------------
//�f�X�g���N�^
//-------------------------------------------------------
CAttackGage::~CAttackGage()
{

}
//-------------------------------------------------------
//�A�^�b�N�Q�[�W�̏���������
//-------------------------------------------------------
HRESULT CAttackGage::Init(void)
{
	CTexture *pTexture = CManager::GetTexture();

	m_nIdxTexture[TYPE_ATTACKFRAME] = pTexture->Regist("data\\texture\\attackgagecover001.png");
	m_nIdxTexture[TYPE_ATTACKGAUGE] = pTexture->Regist("data\\texture\\attackgage001.png");

	//�I�u�W�F�N�g2D�̏���������
	CObject2D::Init();

	//��ނ̐ݒ�
	CObject::SetType(TYPE_ATTACKGAGE);

	//������
	SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //�ʒu
	SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //�T�C�Y
	m_Gage = TYPE_GAUGE_2;

	return (S_OK);
}
//-------------------------------------------------------
//�A�^�b�N�Q�[�W�̏I������
//-------------------------------------------------------
void CAttackGage::Uninit(void)
{
	//�I�u�W�F�N�g2D�̏I������
	CObject2D::Uninit();
}
//-------------------------------------------------------
//�A�^�b�N�Q�[�W�̍X�V����
//-------------------------------------------------------
void CAttackGage::Update(void)
{
	CPlayer3D::AttackGageMove(this);  //�A�^�b�N�Q�[�W�̈ړ���
}
//-------------------------------------------------------
//�A�^�b�N�Q�[�W�̕`�揈��
//-------------------------------------------------------
void CAttackGage::Draw(void)
{
	//�I�u�W�F�N�g2D�̕`�揈��
	CObject2D::Draw();
}
//-------------------------------------------------------
//��������
//-------------------------------------------------------
CAttackGage *CAttackGage::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 scale, int SetTypeTex)
{
	CAttackGage *pAttackgage = NULL;

	//�A�^�b�N�Q�[�W�̐���
	pAttackgage = new CAttackGage;

	//pAttackgage��NULL����Ȃ�������
	if (pAttackgage != NULL)
	{
		//����������
		pAttackgage->Init();

		//�ʒu�̐ݒ�
		pAttackgage->SetPosition(pos);

		//�T�C�Y
		pAttackgage->SetSize(size);

		//�X�P�[��
		pAttackgage->SetScale(scale);

		//�e�N�X�`���^�C�v
		pAttackgage->SetTypeTex(SetTypeTex);

		//���_���̐���
		pAttackgage->SetVtxUI();

		//nCount����
		for (int nCount = 0; nCount < TYPE_MAX; nCount++)
		{
			//nCount�ƑI�����ꂽ���f���^�C�v����v������
			if (nCount == SetTypeTex)
			{
				//�e�N�X�`���̊��蓖��
				pAttackgage->BindTexture(pAttackgage->m_nIdxTexture[nCount]);
			}
		}
	}

	else
	{//�����Ɏ��s�����ꍇ
		return NULL;
	}

	return pAttackgage;
}
//-------------------------------------------------------
//�A�^�b�N�Q�[�W�̐ݒ菈��
//-------------------------------------------------------
void CAttackGage::SetAttackGage(int Gage)
{
	m_Gage = Gage;
}