//=============================================================================
//
// �e�̏���(3D) [bullet3D.cpp]
// Author ��� ��^
//
//=============================================================================
#include "bullet3D.h"
#include "manager.h"
#include "explosion.h"

//�}�N����`
#define LIFE_ENEMY	 (150)    //����
#define LIFE_PLAYER	 (80)     //����
#define TEXSIZE_X	 (40.0f)  //�T�C�YX
#define TEXSIZE_Y	 (10.0f)  //�T�C�YY
#define TEXSIZE_Z	 (10.0f)  //�T�C�YZ
#define ENEMY_SPEED  (5.0f)   //�G�̒e�̑��x

//�ÓI�����o�ϐ�
CBullet3D *CBullet3D::m_apObject[MAX_BULLET] = {};

//-------------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------------
CBullet3D::CBullet3D()
{
	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
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
CBullet3D::~CBullet3D()
{

}
//-------------------------------------------------------
//����������
//-------------------------------------------------------
HRESULT CBullet3D::Init(void)
{
	//�f�o�C�X�̎擾
	//LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CModel *pModel = CManager::GetModel();  //���f���̃|�C���^

	//���f����錾
	m_nIdxModel[BULLETTYPE_PLAYER] = pModel->Regist("data\\MODEL\\kunai001.x");    //�N�i�C
	//m_nIdxModel[BULLETTYPE_ENEMY] = pModel->Regist("data\\MODEL\\hane001.x");      //�G�̒e

	//�I�u�W�F�N�gX�̏���������
	CObjectX::Init();

	//�l�̃N���A
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_nCntHit = 0;

	//�e�̃T�C�Y
	SetSize(D3DXVECTOR3(10.0f, 10.0f, 0.0f));

	////��ނ̐ݒ�
	CObject::SetType(TYPE_BULLET);

	return (S_OK);
}
//-------------------------------------------------------
//�I������
//-------------------------------------------------------
void CBullet3D::Uninit(void)
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
void CBullet3D::Update(void)
{
	D3DXVECTOR3 m_pos = GetPosition();  //�ʒu�̎擾
	D3DXVECTOR3 m_move = GetMove();	    //�ړ��ʂ̎擾

	int nID = m_nID;

	//�ʒu�̍X�V
	m_pos += m_move;

	//�ʒu�̐ݒ�
	SetPosition(m_pos);

	//�G�t�F�N�g�̐���
	//CEffect::Create(GetPosition() - D3DXVECTOR3(50.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(255, 0, 0, 255));

	//�u���b�N�Ƃ̓����蔻��
	//if (CollisionBlock(m_pos))
	{

	}

	m_nLife++;
	m_nCntHit++;

	//�e�̃^�C�v���G�̎�
	if (m_type == BULLETTYPE_ENEMY)
	{
		//�e��������܂ł̃J�E���g
		if (m_nLife >= LIFE_ENEMY)
		{
			//�폜����
			Uninit();

			m_nLife = 0;  //0�ɖ߂�
		}
	}

	//�e�̃^�C�v���v���C���[�̎�
	if (m_type == BULLETTYPE_PLAYER)
	{
		//�e��������܂ł̃J�E���g
		if (m_nLife >= LIFE_PLAYER)
		{
			//�폜����
			Uninit();

			m_nLife = 0;  //0�ɖ߂�
		}
	}

	if (m_apObject[nID] != NULL)
	{
		//�e�̃^�C�v���G�̎�
		if (m_type == BULLETTYPE_ENEMY)
		{
			if (m_nCntHit >= 10)
			{
				//�v���C���[�Ƃ̓����蔻��
				if (CPlayer3D::CollisionBullet(this) == true)
				{
					//�����̏I������
					Uninit();

					m_nCntHit = 0;  //�J�E���g��0�Ƀ��Z�b�g����
				}
			}
		}

		//�e�̃^�C�v���v���C���[�̎�
		if (m_type == BULLETTYPE_PLAYER)
		{
			//�G�Ƃ̓����蔻��
			if (CEnemy3D::CollisionBullet(this) == true)
			{
				//�����̏I������
				Uninit();
			}
		}
	}
}
//-------------------------------------------------------
//�`�揈��
//-------------------------------------------------------
void CBullet3D::Draw(void)
{
	//�I�u�W�F�N�g�̕`�揈��
	CObjectX::Draw();
}
//-------------------------------------------------------
//��������
//-------------------------------------------------------
CBullet3D *CBullet3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR3 scale, int type)
{
	CBullet3D *pBullet = NULL;;

	//�e�̐���
	pBullet = new CBullet3D;

	if (pBullet != NULL)
	{
		//����������
		pBullet->Init();
	}

	else
	{//�����Ɏ��s�����ꍇ
		return NULL;
	}

	//�e�̈ʒu�̐ݒ�
	pBullet->SetPosition(pos);

	//�e�̈ړ��ʂ̐ݒ�
	pBullet->SetMove(move);

	//�e�̌����̐ݒ�
	pBullet->SetRotation(rot);

	//�e�̊g�嗦�̐ݒ�
	pBullet->SetScale(scale);

	//�e�̃T�C�Y
	pBullet->SetSize(D3DXVECTOR3(TEXSIZE_X, TEXSIZE_Y, TEXSIZE_Z));

	//�e�̎�ނ̐ݒ�
	pBullet->SetTypeBullet(type);

	//
	if (pBullet->m_type == BULLETTYPE_ENEMY)
	{
		//�e�̈ړ��ʂ̐ݒ�
		pBullet->SetMove(move * ENEMY_SPEED);
	}

	//nCount����
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		//nCount�ƑI�����ꂽ���f���^�C�v����v������
		if (nCount == type)
		{
			//���f���̊��蓖��
			pBullet->BindModel(pBullet->m_nIdxModel[nCount]);
		}
	}

	return pBullet;
}
//-------------------------------------------------------
//�u���b�N�Ƃ̓����蔻��
//-------------------------------------------------------
bool CBullet3D::CollisionBlock(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 m_pos = GetPosition();  //�ʒu�̎擾
	D3DXVECTOR3 m_size = GetScale();     //�T�C�Y�̎擾
	D3DXVECTOR3 posBlock;
	D3DXVECTOR3 sizeBlock;

	//PRIORITY����
	for (int nCntPriority = 0; nCntPriority < PRIORITY; nCntPriority++)
	{
		//MAX_BULLET����
		for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
		{
			CObject *pObj;  //�I�u�W�F�N�g�N���X�̃|�C���^

			//�I�u�W�F�N�g���擾
			pObj = GetObject(nCntPriority, nCntObj);

			//pObj��NULL����Ȃ�������
			if (pObj != NULL)
			{
				CObject::TYPE type;  //���

				//��ނ��擾
				type = pObj->GetType();

				//��ނ��G�̏ꍇ
				if (type == CObject::TYPE_BLOCK)
				{
					//�u���b�N�̈ʒu�̎擾
					posBlock = pObj->GetPosition();

					//�u���b�N�̃T�C�Y�̎擾
					sizeBlock = pObj->GetScale();

					//�u���b�N�Əd�Ȃ�����
					if (m_pos.x - m_size.x <= posBlock.x + sizeBlock.x
						&&  m_pos.x + m_size.x >= posBlock.x - sizeBlock.x
						&&  m_pos.z - m_size.z <= posBlock.z + sizeBlock.z
						&&  m_pos.z + m_size.z >= posBlock.z - sizeBlock.z)
					{
						//�����̐���
						CExplosion::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z));

						//�u���b�N�̏I������
						//pObj->Uninit();

						//�����̏I������
						Uninit();

						return TRUE;
					}
				}
			}
		}
	}

	return FALSE;
}
//-------------------------------------------------------
//�e�̎�ރ^�C�v�̐ݒ�
//-------------------------------------------------------
void CBullet3D::SetTypeBullet(int Type)
{
	m_type = Type;
}