//=============================================================================
//
// �u���b�N3D���� [block3D.cpp]
// Author ��� ��^
//
//=============================================================================
#include "block3D.h"
#include "manager.h"
#include "player3D.h"
#include "enemy3D.h"

//�}�N����`
#define COLLISION_COR	(10.0f) //���̓����蔻�� (�v���C���[)
#define CORRECTION	(6.0f)  //���̓����蔻��␳

//�ÓI�����o�ϐ�
CBlock3D *CBlock3D::m_apObject[MAX_BLOCK] = {};

//-------------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------------
CBlock3D::CBlock3D()
{
	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
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
CBlock3D::~CBlock3D()
{

}
//-------------------------------------------------------
//����������
//-------------------------------------------------------
HRESULT CBlock3D::Init()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CModel *pModel = CManager::GetModel();  //���f���̃|�C���^

	m_nIdxModel = pModel->Regist("data\\MODEL\\block000.x");  //�x���`

	//���f���̏���������
	CObjectX::Init();

	//��ނ̐ݒ�
	CObject::SetType(TYPE_BLOCK);

	return (S_OK);
}
//-------------------------------------------------------
//�I������
//-------------------------------------------------------
void CBlock3D::Uninit()
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
void CBlock3D::Update()
{
	D3DXVECTOR3 m_pos = GetPosition();  //�ʒu�̎擾
	D3DXVECTOR3 m_posOld = GetPositionOld();  //�ʒu�̎擾
	D3DXVECTOR3 m_move = GetMove();  //�ړ��ʂ̎擾
	D3DXVECTOR3 m_rot = GetRotation();   //�����̎擾
	D3DXVECTOR3 m_scale = GetScale();  //�g�嗦�̎擾
	D3DXVECTOR3 m_size = GetSize();  //�T�C�Y�̎擾

	//�ʒu�̍X�V
	m_pos += m_move;

	//�ړ��ʂ��X�V
	m_move.x += (0.0f - m_move.x) * 0.1f;
	m_move.y += (0.0f - m_move.y) * 0.1f;
}
//-------------------------------------------------------
//�`�揈��
//-------------------------------------------------------
void CBlock3D::Draw()
{
	//�I�u�W�F�N�gX�̕`�揈��
	CObjectX::Draw();
}
//-------------------------------------------------------
//��������
//-------------------------------------------------------
CBlock3D *CBlock3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 size)
{
	CBlock3D *pBlock3D = NULL;

	//�u���b�N�̐���
	pBlock3D = new CBlock3D;

	if (pBlock3D != NULL)
	{
		//����������
		pBlock3D->Init();
	}

	else
	{//�����Ɏ��s�����ꍇ
		return NULL;
	}

	//�u���b�N�̈ʒu�̐ݒ�
	pBlock3D->SetPosition(pos);

	//�u���b�N�̌����̐ݒ�
	pBlock3D->SetRotation(rot);

	//�u���b�N�̊g�嗦�̐ݒ�
	pBlock3D->SetScale(scale);

	//�u���b�N�̃T�C�Y�ݒ�
	pBlock3D->SetSize(size);

	//���f���̊��蓖��
	pBlock3D->BindModel(pBlock3D->m_nIdxModel);

	return pBlock3D;
}
//-------------------------------------------------------
//�v���C���[�Ƃ̓����蔻��
//-------------------------------------------------------
bool CBlock3D::CollisionPlayer(CPlayer3D *pPlayer)
{
	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
	{
		//m_apObject[nCnt]��NULL����Ȃ�������
		if (m_apObject[nCnt] != NULL)
		{
			D3DXVECTOR3 m_pos = m_apObject[nCnt]->GetPosition();  //�u���b�N�̈ʒu�̎擾
			D3DXVECTOR3 m_move = m_apObject[nCnt]->GetMove();  //�ړ��ʂ̎擾
			D3DXVECTOR3 m_size = m_apObject[nCnt]->GetScale();  //�u���b�N�̊g�嗦�̎擾
			CObject::TYPE type;  //���

			//��ނ��擾
			type = pPlayer->GetType();

			//��ނ��v���C���[�̏ꍇ
			if (type == CObject::TYPE_PLAYER)
			{
				D3DXVECTOR3 posPlayer = pPlayer->GetPosition();  //�v���C���[�̈ʒu
				D3DXVECTOR3 posOldPlayer = pPlayer->GetPositionOld();  //�v���C���[�̉ߋ��̈ʒu
				D3DXVECTOR3 movePlayer = pPlayer->GetMove();  //�v���C���[�̈ړ���
				D3DXVECTOR3 sizePlayer = pPlayer->GetScale();  //�v���C���[�̊g�嗦

				///////////////////////////////////
				//���̔���
				///////////////////////////////////
				//�G�Əd�Ȃ�����
				if (m_pos.z - m_size.z <= posPlayer.z + sizePlayer.z
					&&  m_pos.z + m_size.z >= posPlayer.z - sizePlayer.z)
				{
					if (m_pos.y - m_size.y * COLLISION_COR - 10.0f < posPlayer.y + sizePlayer.y * COLLISION_COR + 10.0f
						&&  m_pos.y + m_size.y * COLLISION_COR + 10.0f > posPlayer.y - sizePlayer.y * COLLISION_COR - 10.0f)
					{
						if (m_pos.x - m_size.x * COLLISION_COR - CORRECTION > posOldPlayer.x + sizePlayer.x * COLLISION_COR
							&&  m_pos.x - m_size.x * COLLISION_COR - CORRECTION < posPlayer.x + sizePlayer.x * COLLISION_COR)
						{//�Ђ���B
							posPlayer.x = m_pos.x - m_size.x * COLLISION_COR - 10.0f;  //�u���b�N�̍����甲���Ȃ�
							movePlayer.x = 0.0f;  //�v���C���[�̈ړ��ʂ�0�ɂ���
						}

						if (m_pos.x + m_size.x * COLLISION_COR + CORRECTION < posOldPlayer.x - sizePlayer.x * COLLISION_COR
							&&  m_pos.x + m_size.x * COLLISION_COR + CORRECTION > posPlayer.x - sizePlayer.x * COLLISION_COR)
						{//�~�M�[�B
							posPlayer.x = m_pos.x + m_size.x * COLLISION_COR + 10.0f;  //�u���b�N�̉E���甲���Ȃ�
							movePlayer.x = 0.0f;  //�v���C���[�̈ړ��ʂ�0�ɂ���
						}
					}
				}

				///////////////////////////////////
				//�c�̔���
				///////////////////////////////////
				if (m_pos.z - m_size.z <= posPlayer.z + sizePlayer.z
					&&  m_pos.z + m_size.z >= posPlayer.z - sizePlayer.z)
				{
					if ((m_pos.x - m_size.x * COLLISION_COR - 2.0f < posPlayer.x + sizePlayer.x * COLLISION_COR + 10.0f
						&& m_pos.x + m_size.x * COLLISION_COR + 2.0f > posPlayer.x - sizePlayer.x * COLLISION_COR - 10.0f))
					{
						if (m_pos.y + m_size.y * COLLISION_COR < posOldPlayer.y - sizePlayer.y * COLLISION_COR - 17.0f
							&&  m_pos.y + m_size.y * COLLISION_COR > posPlayer.y - sizePlayer.y * COLLISION_COR - 17.0f)
						{//�ゾ�B
							posPlayer.y = m_pos.y + m_size.y * COLLISION_COR + 25.0f;  //�u���b�N�̏�ɗ�������
							movePlayer.y = 0.0f;  //�ړ��ʂ�0�ɂ���
							pPlayer->SetAttack(false);
							pPlayer->SetPlayerJump(CPlayer3D::PLAYERJUMP_GROUND);  //�v���C���[��n���Ԃɂ���
						}

						if (m_pos.y - m_size.y * COLLISION_COR  > posOldPlayer.y + sizePlayer.y * COLLISION_COR + 60.0f
							&&  m_pos.y - m_size.y * COLLISION_COR  < posPlayer.y + sizePlayer.y * COLLISION_COR + 60.0f)
						{//��
							posPlayer.y = m_pos.y - m_size.y * COLLISION_COR - 80.0f;  //�u���b�N�̉�����ђʖh��
							movePlayer.y = 0.0f;  //�ړ��ʂ�0�ɂ���
						}
					}
				}

				pPlayer->SetPosition(posPlayer);  //�v���C���[�̈ʒu�̐ݒ�
				pPlayer->SetMove(movePlayer);	   //�v���C���[�̈ړ��ʂ̐ݒ�
			}
		}
	}
	
	return FALSE;
}
//-------------------------------------------------------
//�G�Ƃ̓����蔻��
//-------------------------------------------------------
bool CBlock3D::CollisionEnemy(CEnemy3D *pEnemy)
{
	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
	{
		//m_apObject[nCnt]��NULL����Ȃ�������
		if (m_apObject[nCnt] != NULL)
		{
			D3DXVECTOR3 m_pos = m_apObject[nCnt]->GetPosition();  //�u���b�N�̈ʒu�̎擾
			D3DXVECTOR3 m_move = m_apObject[nCnt]->GetMove();  //�ړ��ʂ̎擾
			D3DXVECTOR3 m_size = m_apObject[nCnt]->GetScale();  //�u���b�N�̃T�C�Y�̎擾
			CObject::TYPE type;  //���

			//��ނ��擾
			type = pEnemy->GetType();

			//��ނ��G�̏ꍇ
			if (type == CObject::TYPE_ENEMY)
			{
				D3DXVECTOR3 posEnemy = pEnemy->GetPosition();        //�G�̈ʒu�̎擾
				D3DXVECTOR3 posOldEnemy = pEnemy->GetPositionOld();  //�G�̉ߋ��̈ʒu�̎擾
				D3DXVECTOR3 moveEnemy = pEnemy->GetMove();           //�G�̈ړ��ʂ̎擾
				D3DXVECTOR3 sizeEnemy = pEnemy->GetScale();          //�G�̃T�C�Y�̎擾

				///////////////////////////////////
				//���̔���
				///////////////////////////////////
				if (m_pos.y - m_size.y * COLLISION_COR - 10.0f < posEnemy.y + sizeEnemy.y * COLLISION_COR + 10.0f
					&&  m_pos.y + m_size.y * COLLISION_COR + 10.0f > posEnemy.y - sizeEnemy.y * COLLISION_COR - 10.0f)
				{
					if (m_pos.x - m_size.x * COLLISION_COR - CORRECTION > posOldEnemy.x + sizeEnemy.x * COLLISION_COR + 20.0f
						&&  m_pos.x - m_size.x * COLLISION_COR - CORRECTION < posEnemy.x + sizeEnemy.x * COLLISION_COR + 20.0f)
					{//�Ђ���B
						posEnemy.x = m_pos.x - m_size.x * COLLISION_COR - 30.0f;  //�u���b�N�̍����甲���Ȃ�
						moveEnemy.x = 0.0f;  //�v���C���[�̈ړ��ʂ�0�ɂ���
					}

					if (m_pos.x + m_size.x * COLLISION_COR + CORRECTION < posOldEnemy.x - sizeEnemy.x * COLLISION_COR
						&&  m_pos.x + m_size.x * COLLISION_COR + CORRECTION > posEnemy.x - sizeEnemy.x * COLLISION_COR)
					{//�~�M�[�B
						posEnemy.x = m_pos.x + m_size.x * COLLISION_COR + 10.0f;  //�u���b�N�̉E���甲���Ȃ�
						moveEnemy.x = 0.0f;  //�v���C���[�̈ړ��ʂ�0�ɂ���
					}
				}

				///////////////////////////////////
				//�c�̔���
				///////////////////////////////////
				if ((m_pos.x - m_size.x * COLLISION_COR < posEnemy.x + sizeEnemy.x * COLLISION_COR + 20.0f
					&&   m_pos.x + m_size.x * COLLISION_COR > posEnemy.x - sizeEnemy.x * COLLISION_COR - 20.0f))
				{
					if (m_pos.y + m_size.y * COLLISION_COR < posOldEnemy.y - sizeEnemy.y * COLLISION_COR - 18.0f
						&&  m_pos.y + m_size.y * COLLISION_COR > posEnemy.y - sizeEnemy.y * COLLISION_COR - 18.0f)
					{//�ゾ�B
						posEnemy.y = m_pos.y + m_size.y * COLLISION_COR + 29.0f;  //�u���b�N�̏�ɗ�������
						moveEnemy.y = 0.0f;  //�ړ��ʂ�0�ɂ���
					}

					if (m_pos.y - m_size.y * COLLISION_COR > posOldEnemy.y + sizeEnemy.y * COLLISION_COR
						&&  m_pos.y - m_size.y * COLLISION_COR < posEnemy.y + sizeEnemy.y * COLLISION_COR)
					{//��
						posEnemy.y = m_pos.y - m_size.y * COLLISION_COR - 80.0f;  //�u���b�N�̉�����ђʖh��
						moveEnemy.y = 0.0f;  //�ړ��ʂ�0�ɂ���
					}
				}

				pEnemy->SetPosition(posEnemy);  //�G�̈ʒu�̐ݒ�
				pEnemy->SetMove(moveEnemy);	  //�G�̈ړ��ʂ̐ݒ�
			}
		}
	}

	return FALSE;
}