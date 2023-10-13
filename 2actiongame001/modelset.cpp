//=============================================================================
//
// ���f���z�u���� [modelset.cpp]
// Author ��� ��^
//
//=============================================================================
#include "modelset.h"
#include "manager.h"
#include "player3D.h"

//�ÓI�����o�ϐ�
CModelSet *CModelSet::m_apObject[MAX_MODEL] = {};

//-------------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------------
CModelSet::CModelSet()
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (m_apObject[nCnt] == NULL)
		{
			m_apObject[nCnt] = this;

			m_nID = nCnt;

			break;
		}
	}
}
//-------------------------------------------------------
//�f�X�g���N�^
//-------------------------------------------------------
CModelSet::~CModelSet()
{

}
//-------------------------------------------------------
//����������
//-------------------------------------------------------
HRESULT CModelSet::Init()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CModel *pModel = CManager::GetModel();  //���f���̃|�C���^

	m_nIdxModel[TYPE_GATE_1] = pModel->Regist("data\\MODEL\\gate001.x");  //�Q�[�g1
	m_nIdxModel[TYPE_GATE_2] = pModel->Regist("data\\MODEL\\gate001.x");  //�Q�[�g2
	m_nIdxModel[TYPE_GATE_3] = pModel->Regist("data\\MODEL\\gate001.x");  //�Q�[�g3
	m_nIdxModel[TYPE_KOIN] = pModel->Regist("data\\MODEL\\gate001.x");  //�R�C��

	//���f���̏���������
	CObjectX::Init();

	//��ނ̐ݒ�
	CObject::SetType(TYPE_MODEL);

	return (S_OK);
}
//-------------------------------------------------------
//�I������
//-------------------------------------------------------
void CModelSet::Uninit()
{
	int nID = m_nID;

	//�I�u�W�F�N�g�̍폜����
	CObjectX::Uninit();

	if (m_apObject[nID] != NULL)
	{
		m_apObject[nID] = NULL;
	}
}
//-------------------------------------------------------
//�X�V����
//-------------------------------------------------------
void CModelSet::Update()
{

}
//-------------------------------------------------------
//�`�揈��
//-------------------------------------------------------
void CModelSet::Draw()
{
	//���f��X�̕`�揈��
	CObjectX::Draw();
}
//-------------------------------------------------------
//��������
//-------------------------------------------------------
CModelSet *CModelSet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 size, int SetTypeTex)
{
	CModelSet *pModelSet = NULL;

	//���f���̐���
	pModelSet = new CModelSet;

	if (pModelSet != NULL)
	{
		//����������
		pModelSet->Init();
	}

	else
	{//�����Ɏ��s�����ꍇ
		return NULL;
	}

	pModelSet->SetPosition(pos);  //�ʒu�̐ݒ�
	pModelSet->SetRotation(rot);  //�����̐ݒ�
	pModelSet->SetScale(scale);  //�g�嗦�̐ݒ�
	pModelSet->SetSize(size);  //�T�C�Y�ݒ�
	pModelSet->SetTypeTex(SetTypeTex);  //�e�N�X�`���^�C�v�ݒ�

	//nCount����
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		//nCount�ƑI�����ꂽ���f������v������
		if (nCount == SetTypeTex)
		{
			//���f���̊��蓖��
			pModelSet->BindModel(pModelSet->m_nIdxModel[nCount]);
		}
	}

	return pModelSet;
}
//-------------------------------------------------------
//�v���C���[�Ƃ̓����蔻�菈��
//-------------------------------------------------------
bool CModelSet::ModelCollision(CPlayer3D *pPlayer)
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (m_apObject[nCnt] != NULL)
		{
			D3DXVECTOR3 m_pos = m_apObject[nCnt]->GetPosition();  //�ʒu�̎擾
			D3DXVECTOR3 m_size = m_apObject[nCnt]->GetScale();  //�g�嗦�̎擾
			CObject::TYPE type;  //���
			type = pPlayer->GetType();   //��ނ��擾

			 //��ނ��v���C���[�̏ꍇ
			if (type == CObject::TYPE_PLAYER)
			{
				D3DXVECTOR3 posPlayer = pPlayer->GetPosition();  //�v���C���[�̈ʒu�̎擾
				D3DXVECTOR3 sizePlayer = pPlayer->GetScale();  //�v���C���[�̊g�嗦�̎擾
				int typetex = m_apObject[nCnt]->GetTypeTex();  //�^�C�v����p

				//�Q�[�g1�̎�
				if (typetex == TYPE_GATE_1)
				{
					//�v���C���[�Əd�Ȃ�����
					if (m_pos.x - m_size.x <= posPlayer.x + sizePlayer.x + 50.0f
					&&  m_pos.x + m_size.x >= posPlayer.x - sizePlayer.x - 50.0f
					&&  m_pos.y - m_size.y <= posPlayer.y + sizePlayer.y + 50.0f
					&&  m_pos.y + m_size.y >= posPlayer.y - sizePlayer.y - 50.0f
					&&  m_pos.z - m_size.z <= posPlayer.z + sizePlayer.z + 200.0f
					&&  m_pos.z + m_size.z >= posPlayer.z - sizePlayer.z - 200.0f)
					{
						posPlayer = D3DXVECTOR3(-400.0f, 0.0f, -2000.0f);

						pPlayer->SetPosition(posPlayer);

						return TRUE;
					}
				}

				//�Q�[�g2�̎�
				else if (typetex == TYPE_GATE_2)
				{
					//�v���C���[�Əd�Ȃ�����
					if (m_pos.x - m_size.x <= posPlayer.x + sizePlayer.x + 50.0f
						&&  m_pos.x + m_size.x >= posPlayer.x - sizePlayer.x - 50.0f
						&&  m_pos.y - m_size.y <= posPlayer.y + sizePlayer.y + 50.0f
						&&  m_pos.y + m_size.y >= posPlayer.y - sizePlayer.y - 50.0f
						&&  m_pos.z - m_size.z <= posPlayer.z + sizePlayer.z + 200.0f
						&&  m_pos.z + m_size.z >= posPlayer.z - sizePlayer.z - 200.0f)
					{
						posPlayer = D3DXVECTOR3(-400.0f, 0.0f, 0.0f);

						pPlayer->SetPosition(posPlayer);

						return TRUE;
					}
				}
			}
		}
	}
	
	return FALSE;
}