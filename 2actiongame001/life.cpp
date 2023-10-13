//=============================================================================
//
// ���C�t���� [life.cpp]
// Author�F��؈�^
//
//=============================================================================
#include "manager.h"
#include "life.h"
#include "player3D.h"

//�ÓI�����o�ϐ�
CLife *CLife::m_apObject = NULL;

//-------------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------------
CLife::CLife()
{
	if (m_apObject == NULL)
	{
		m_apObject = this;
	}

	SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //�ʒu�̏�����
	SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //�T�C�Y�̏�����
}
//-------------------------------------------------------
//�f�X�g���N�^
//-------------------------------------------------------
CLife::~CLife()
{

}
//-------------------------------------------------------
//���C�t�̏���������
//-------------------------------------------------------
HRESULT CLife::Init(void)
{
	CTexture *pTexture = CManager::GetTexture();

	m_nIdxTexture[TYPE_LIFEFRAME] = pTexture->Regist("data\\texture\\life001.png");
	m_nIdxTexture[TYPE_LIFEGAUGE] = pTexture->Regist("data\\texture\\lifegauge001.png");

	//�I�u�W�F�N�g�r���{�[�h�̏���������
	CObject2D::Init();

	//��ނ̐ݒ�
	CObject::SetType(TYPE_LIFE);

	return (S_OK);
}
//-------------------------------------------------------
//���C�t�̏I������
//-------------------------------------------------------
void CLife::Uninit(void)
{
	//�I�u�W�F�N�g�r���{�[�h�̏I������
	CObject2D::Uninit();

	m_apObject = NULL;
}
//-------------------------------------------------------
//���C�t�̍X�V����
//-------------------------------------------------------
void CLife::Update(void)
{

}
//-------------------------------------------------------
//���C�t�̕`�揈��
//-------------------------------------------------------
void CLife::Draw(void)
{
	//�I�u�W�F�N�g�r���{�[�h�̕`��(�A�j���[�V����)����
	CObject2D::Draw();
}
//-------------------------------------------------------
//��������
//-------------------------------------------------------
CLife *CLife::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 scale, int SetTypeTex)
{
	CLife *pLife = NULL;

	//���C�t�̐���
	pLife = new CLife;

	//pLife��NULL����Ȃ�������
	if (pLife != NULL)
	{
		//���C�t�̏���������
		pLife->Init();

		//���C�t�̈ʒu�̐ݒ�
		pLife->SetPosition(pos);

		//���C�t�̃T�C�Y
		pLife->SetSize(size);

		//���C�t�̃X�P�[��
		pLife->SetScale(scale);

		//�e�N�X�`���^�C�v
		pLife->SetTypeTex(SetTypeTex);

		//���_���̐���
		pLife->SetVtxUI();

		//nCount����
		for (int nCount = 0; nCount < TYPE_MAX; nCount++)
		{
			//nCount�ƑI�����ꂽ���f���^�C�v����v������
			if (nCount == SetTypeTex)
			{
				//�e�N�X�`���̊��蓖��
				pLife->BindTexture(pLife->m_nIdxTexture[nCount]);
			}
		}
	}

	else
	{//�����Ɏ��s�����ꍇ
		return NULL;
	}

	return pLife;
}
//-------------------------------------------------------
//���C�t�ݒ菈��
//-------------------------------------------------------
void CLife::LifeMove(CPlayer3D *pPlayer)
{
	if (m_apObject != NULL)
	{
		CObject::TYPE type;  //���

		//��ނ��擾
		type = pPlayer->GetType();
		int typetex = m_apObject->GetTypeTex();

		//��ނ��v���C���[�̏ꍇ
		if (type == CObject::TYPE_PLAYER)
		{
			int m_lifePlayer = pPlayer->GetLife();  //�v���C���[�̃��C�t�擾

			if (m_lifePlayer == 400)
			{
				if (typetex == TYPE_LIFEGAUGE)
				{
					m_apObject->Uninit();
				}

				//---------------------------------------------------------------
				//���C�t�̐���
				//---------------------------------------------------------------
				CLife::Create(D3DXVECTOR3(117.0f, 650.0f, 0.0f), D3DXVECTOR3(240.0f, 30.0f, 0.0f), D3DXVECTOR3(0.8f, 0.0f, 0.0f), CLife::TYPE_LIFEGAUGE);
			}

			if (m_lifePlayer == 300)
			{
				if (typetex == TYPE_LIFEGAUGE)
				{
					m_apObject->Uninit();
				}

				//---------------------------------------------------------------
				//���C�t�̐���
				//---------------------------------------------------------------
				CLife::Create(D3DXVECTOR3(117.0f, 650.0f, 0.0f), D3DXVECTOR3(180.0f, 30.0f, 0.0f), D3DXVECTOR3(0.6f, 0.0f, 0.0f), CLife::TYPE_LIFEGAUGE);
			}

			if (m_lifePlayer == 200)
			{
				if (typetex == TYPE_LIFEGAUGE)
				{
					m_apObject->Uninit();
				}

				//---------------------------------------------------------------
				//���C�t�̐���
				//---------------------------------------------------------------
				CLife::Create(D3DXVECTOR3(117.0f, 650.0f, 0.0f), D3DXVECTOR3(120.0f, 30.0f, 0.0f), D3DXVECTOR3(0.4f, 0.0f, 0.0f), CLife::TYPE_LIFEGAUGE);
			}

			if (m_lifePlayer == 100)
			{
				if (typetex == TYPE_LIFEGAUGE)
				{
					m_apObject->Uninit();
				}

				//---------------------------------------------------------------
				//���C�t�̐���
				//---------------------------------------------------------------
				CLife::Create(D3DXVECTOR3(117.0f, 650.0f, 0.0f), D3DXVECTOR3(60.0f, 30.0f, 0.0f), D3DXVECTOR3(0.2f, 0.0f, 0.0f), CLife::TYPE_LIFEGAUGE);
			}

			if (m_lifePlayer == 0)
			{
				if (typetex == TYPE_LIFEGAUGE)
				{
					m_apObject->Uninit();
				}

				//---------------------------------------------------------------
				//���C�t�̐���
				//---------------------------------------------------------------
				CLife::Create(D3DXVECTOR3(117.0f, 650.0f, 0.0f), D3DXVECTOR3(0.0f, 30.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CLife::TYPE_LIFEGAUGE);
			}
		}
	}
}