//=============================================================================
//
// �G���� [enemy3D.cpp]
// Author ��� ��^
//
//=============================================================================
#include "enemy3D.h"
#include "manager.h"
#include "game.h"
#include "explosion.h"
#include "bullet3D.h"
#include "effect.h"
#include "block3D.h"

//�}�N����`
#define TEXSIZE_X	(80.0f)   //�T�C�YX
#define TEXSIZE_Y	(80.0f)   //�T�C�YY
#define TEXSIZE_Z	(80.0f)   //�T�C�YZ
#define BULLETSPEED (10.0f)   //�G�̒e�X�s�[�h
#define BESTPOS     (700.0f)  //�G�̓����Ă���ŋߋ���
#define MOVEKOUMORI (0.5f)    //�R�E�����̓����X�s�[�h

//�ÓI�����o�ϐ�
CEnemy3D *CEnemy3D::m_apObject[MAX_ENEMY] = {};

//-------------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------------
CEnemy3D::CEnemy3D()
{
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
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
CEnemy3D::~CEnemy3D()
{

}
//-------------------------------------------------------
//�G�̏���������
//-------------------------------------------------------
HRESULT CEnemy3D::Init()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CModel *pModel = CManager::GetModel();  //���f���̃|�C���^

	//���f����錾
	m_nIdxModel[TYPE_KOUMORI] = pModel->Regist("data\\MODEL\\koumori001.x");  //�R�E����
	m_nIdxModel[TYPE_OOKAMI] = pModel->Regist("data\\MODEL\\ookami001.x");     //�T

	//�I�u�W�F�N�gX�̏���������
	CObjectX::Init();

	//�l��������
	m_Life = 0;
	m_nCntHit = 0;
	m_nCounterMove = 0;
	m_nCounterBullet = 0;

	SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //�T�C�Y������
	SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //�ړ��ʏ�����

	SetEnemyMoveState(ENEMYMOVE_RIGHT);  //������
	CObject::SetType(TYPE_ENEMY);  //��ނ̐ݒ�
	CObjectX::SetState(CObject::STATE_NORMAL, 0);  //��ԊǗ��ݒ�

	return (S_OK);
}
//-------------------------------------------------------
//�G�̏I������
//-------------------------------------------------------
void CEnemy3D::Uninit(void)
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
//�G�̍X�V����
//-------------------------------------------------------
void CEnemy3D::Update(void)
{
	D3DXVECTOR3 m_pos = GetPosition();  //�ʒu�̎擾
	D3DXVECTOR3 m_move = GetMove();   //�ړ��ʂ̎擾
	D3DXVECTOR3 m_rot = GetRotation();  //�����̎擾
	D3DXVECTOR3 posPlayer;

	SetPositionOld(m_pos);  //�ߋ��̈ʒu�ݒ�

	//��ԊǗ��ݒ�
	CObject::UpdateState();

	//��ԊǗ�
	UpdateEnemyState();

	//�ړ��ݒ�
	//MoveEnemy();

	m_nCntHit++;

	//�ʒu�̍X�V
	m_pos += m_move;

	//�ړ��ʂ��X�V
	m_move.x += (0.0f - m_move.x) * ENEMYSPEEDUP;
	m_move.y += (0.0f - m_move.y) * ENEMYSPEEDUP;

	//������
	if (m_pos.y < 0)
	{
		m_pos.y = 0;
		m_move.y = 0;
	}

	SetPosition(m_pos);  //�ʒu�̐ݒ�
	SetMove(m_move);  //�ړ��ʂ̐ݒ�
	SetRotation(m_rot);  //�����̐ݒ�

	//�����蔻��
	CBlock3D::CollisionEnemy(this);

	if (m_nCntHit >= 60)
	{
		//�v���C���[�ƓG�Ƃ̓����蔻��
		if (CPlayer3D::CollisionEnemy(this))
		{
			m_nCntHit = 0;  //�J�E���g��0�Ƀ��Z�b�g����
		}
	}
}
//-------------------------------------------------------
//�G�̕`�揈��
//-------------------------------------------------------
void CEnemy3D::Draw(void)
{
	//�I�u�W�F�N�gX�̕`�揈��
	CObjectX::Draw();
}
//-------------------------------------------------------
//��������
//-------------------------------------------------------
CEnemy3D *CEnemy3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 size, int SetTypeTex, int Life)
{
	CEnemy3D *pEnemy3D;

	//�G�̐���
	pEnemy3D = new CEnemy3D;

	if (pEnemy3D != NULL)
	{
		//����������
		pEnemy3D->Init();

		//�ʒu�̐ݒ�
		pEnemy3D->SetPosition(pos);

		//�ʒu�̐ݒ�
		pEnemy3D->SetPositionOld(pos);

		//�ړ��ʂ̐ݒ�
		pEnemy3D->SetMove(move);

		//�����̐ݒ�
		pEnemy3D->SetRotation(rot);

		//�g�嗦�̐ݒ�
		pEnemy3D->SetScale(scale);

		//�T�C�Y
		pEnemy3D->SetSize(size);

		//�e�N�X�`���^�C�v
		pEnemy3D->SetTypeTex(SetTypeTex);

		//���C�t�̐ݒ�
		pEnemy3D->SetLife(Life);

		//nCount����
		for (int nCount = 0; nCount < TYPE_MAX; nCount++)
		{
			//nCount�ƑI�����ꂽ���f���^�C�v����v������
			if (nCount == SetTypeTex)
			{
				//�e�N�X�`���̊��蓖��
				pEnemy3D->BindModel(pEnemy3D->m_nIdxModel[nCount]);
			}
		}
	}

	else
	{//�����Ɏ��s�����ꍇ
		return NULL;
	}

	return pEnemy3D;
}
//-------------------------------------------------------
//�v���C���[�̋ߐڍU��
//-------------------------------------------------------
void CEnemy3D::PlayerAttack(CPlayer3D *pPlayer)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�Q�[���p�b�h�̎擾
	CInputPad *pInputPad;
	pInputPad = CManager::GetInputPad();

	//�T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetSound();

	CObject::TYPE type;  //���

	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		//m_apObject[nCnt]��NULL����Ȃ�������
		if (m_apObject[nCnt] != NULL)
		{
			//��ނ��擾
			type = pPlayer->GetType();

			//��ނ��v���C���[�̏ꍇ
			if (type == CObject::TYPE_PLAYER)
			{
				D3DXVECTOR3 m_pos = m_apObject[nCnt]->GetPosition();  //�ʒu�̎擾
				D3DXVECTOR3 m_rot = m_apObject[nCnt]->GetRotation();  //�����̎擾
				D3DXVECTOR3 m_size = m_apObject[nCnt]->GetScale();    //�g�嗦�̎擾
				D3DXVECTOR3 posPlayer = pPlayer->GetPosition();       //�v���C���[�̈ʒu�̎擾
				D3DXVECTOR3 rotPlayer = pPlayer->GetRotation();       //�v���C���[�̌����̎擾
				D3DXVECTOR3 sizePlayer = pPlayer->GetScale();         //�v���C���[�̊g�嗦�̎擾
				int BattleState = pPlayer->GetAttackState();

				if (BattleState == pPlayer->BATTLESTATE_PROXIMITY)
				{
					if (pInputKeyboard->GetTrigger(DIK_V) == true || pInputPad->GetTrigger(CInputPad::BUTTON_RB, 0))
					{
						//�v���C���[���E�����̎�
						if (rotPlayer.y == (-D3DX_PI * 0.5f))
						{
							//�G�t�F�N�g�̐���
							CEffect::Create(D3DXVECTOR3(posPlayer.x + 60.0f, posPlayer.y + 30.0f, posPlayer.z), D3DXVECTOR3(50.0f, 50.0f, 0.0f));

							//�G�Əd�Ȃ�����
							if (m_pos.x + m_size.x >= posPlayer.x - sizePlayer.x
								&&  m_pos.x - m_size.x - 20.0f <= posPlayer.x + sizePlayer.x + 100.0f
								&&  m_pos.y + m_size.y + 80.0f >= posPlayer.y - sizePlayer.y
								&&  m_pos.y - m_size.y <= posPlayer.y + sizePlayer.y)
							{
								//�G���E�����̎�
								if (m_rot.y == (-D3DX_PI * 0.5f))
								{
									m_pos.x -= 100.0f;
								}

								//�G���������̎�
								else if (m_rot.y == (D3DX_PI * 0.5f))
								{
									m_pos.x += 100.0f;
								}

								m_apObject[nCnt]->SetPosition(m_pos);

								//�G�̃q�b�g����
								HitEnemy(200, nCnt);
							}
						}

						//�v���C���[���������̎�
						else if (rotPlayer.y == (D3DX_PI * 0.5f))
						{
							//�G�t�F�N�g�̐���
							CEffect::Create(D3DXVECTOR3(posPlayer.x - 60.0f, posPlayer.y + 30.0f, posPlayer.z), D3DXVECTOR3(50.0f, 50.0f, 0.0f));

							//�G�Əd�Ȃ�����
							if (m_pos.x + m_size.x + 20.0f >= posPlayer.x - sizePlayer.x - 100.0f
								&&  m_pos.x - m_size.x <= posPlayer.x + sizePlayer.x
								&&  m_pos.y + m_size.y + 80.0f >= posPlayer.y - sizePlayer.y
								&&  m_pos.y - m_size.y <= posPlayer.y + sizePlayer.y)
							{
								//�G���E�����̎�
								if (m_rot.y == (-D3DX_PI * 0.5f))
								{
									m_pos.x -= 100.0f;
								}

								//�G���������̎�
								else if (m_rot.y == (D3DX_PI * 0.5f))
								{
									m_pos.x += 100.0f;
								}

								m_apObject[nCnt]->SetPosition(m_pos);

								//�G�̃q�b�g����
								HitEnemy(200, nCnt);
							}
						}

						//SE�̍Đ�
						//pSound->PlaySound(SOUND_LABEL_SE_MELEE);
					}
				}
			}
		}
	}
}
//-------------------------------------------------------
//�G�̈ړ�
//-------------------------------------------------------
void CEnemy3D::MoveEnemy(CPlayer3D *pPlayer)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		//m_apObject[nCnt]��NULL����Ȃ�������
		if (m_apObject[nCnt] != NULL)
		{
			D3DXVECTOR3 m_pos = m_apObject[nCnt]->GetPosition();  //�ʒu�̎擾
			D3DXVECTOR3 m_posOld = m_apObject[nCnt]->GetPositionOld();  //�ߋ��̈ʒu�̎擾
			D3DXVECTOR3 m_move = m_apObject[nCnt]->GetMove();  //�ړ��ʂ̎擾
			D3DXVECTOR3 m_rot = m_apObject[nCnt]->GetRotation();  //�����̎擾
			D3DXVECTOR3 m_size = m_apObject[nCnt]->GetSize();  //�T�C�Y�̎擾
			D3DXVECTOR3 posPlayer = pPlayer->GetPosition();  //�v���C���[�̈ʒu�̎擾
			D3DXVECTOR3 posOldPlayer = pPlayer->GetPositionOld();  //�v���C���[�̉ߋ��̈ʒu�擾
			D3DXVECTOR3 sizePlayer = pPlayer->GetSize();  //�v���C���[�̃T�C�Y�擾
			int typetex = m_apObject[nCnt]->GetTypeTex();

			CObject::TYPE type;  //���

			//��ނ��擾
			type = pPlayer->GetType();

			//��ނ��v���C���[�̏ꍇ
			if (type == CObject::TYPE_PLAYER)
			{
				if (typetex == TYPE_KOUMORI)
				{
					if (m_apObject[nCnt]->m_nCounterMove < 50)
					{
						//���ɓ�����
						m_move.x = -MOVEKOUMORI;
					}

					if (m_apObject[nCnt]->m_nCounterMove > 50)
					{
						//�E�ɓ�����
						m_move.x = MOVEKOUMORI;
					}

					if (m_apObject[nCnt]->m_nCounterMove < 25)
					{
						//��ɓ�����
						m_move.y = MOVEKOUMORI;
					}

					else if (m_apObject[nCnt]->m_nCounterMove < 50)
					{
						//���ɓ�����
						m_move.y = -MOVEKOUMORI;
					}

					else if (m_apObject[nCnt]->m_nCounterMove < 75)
					{
						//���ɓ�����
						m_move.y = -MOVEKOUMORI;
					}

					else if (m_apObject[nCnt]->m_nCounterMove < 100)
					{
						//��ɓ�����
						m_move.y = MOVEKOUMORI;
					}

					if (m_apObject[nCnt]->m_nCounterMove > 100)
					{
						m_apObject[nCnt]->m_nCounterMove = 0;
					}
				}

				if (m_pos.z - m_size.z <= posPlayer.z + sizePlayer.z + 50.0f &&
					m_pos.z + m_size.z >= posPlayer.z - sizePlayer.z - 50.0f)
				{
					//�v���C���[���E�ɂ��鎞
					if (m_pos.x  > posPlayer.x + 20.0f
						&&  m_pos.x - BESTPOS < posPlayer.x)
					{
						m_rot.y = (D3DX_PI * 0.5f);

						if (typetex == TYPE_OOKAMI)
						{
							//�v���C���[���G�Ɠ������炢�̍����ɂ���Ƃ�
							//if (m_pos.y + 20.0f >= posPlayer.y)
							{
								m_move.x = -1.0f;
								//m_apObject[nCnt]->SetEnemyMoveState(ENEMYMOVE_LEFT);
							}
						}

						if (typetex == TYPE_KOUMORI)
						{
							//�R�E�����̒e
							if (m_apObject[nCnt]->m_nCounterBullet >= 130)
							{
								//�e����
								CBullet3D::Create(m_apObject[nCnt]->GetPosition(), D3DXVECTOR3(-sinf(m_rot.z), -cosf(m_rot.z), 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXVECTOR3(0.8f, 0.8f, 0.8f), CBullet3D::BULLETTYPE_ENEMY);

								m_apObject[nCnt]->m_nCounterBullet = 0;  //���Z�b�g
							}
						}
					}

					//�v���C���[��荶�ɂ��鎞
					if (m_pos.x < posPlayer.x)
					{
						m_rot.y = (-D3DX_PI * 0.5f);

						if (typetex == TYPE_OOKAMI)
						{
							m_move.x = 1.0f;

							//m_apObject[nCnt]->SetEnemyMoveState(ENEMYMOVE_RIGHT);
						}

						if (typetex == TYPE_KOUMORI)
						{
							//�R�E�����̒e
							if (m_apObject[nCnt]->m_nCounterBullet >= 130)
							{
								//�e����
								CBullet3D::Create(m_apObject[nCnt]->GetPosition(), D3DXVECTOR3(-sinf(m_rot.z), -cosf(m_rot.z), 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f), D3DXVECTOR3(0.8f, 0.8f, 0.8f), CBullet3D::BULLETTYPE_ENEMY);

								m_apObject[nCnt]->m_nCounterBullet = 0;  //���Z�b�g
							}
						}
					}
				}
			}

			if (typetex == TYPE_OOKAMI)
			{
				//�d�͂�������
				m_move.y -= 3.0f;
			}

			if (typetex == TYPE_KOUMORI)
			{
				float fAngle = atan2f(m_pos.y - posOldPlayer.y, posOldPlayer.x - m_pos.x);

				m_rot.z = fAngle - D3DX_PI * 0.5f;

				m_apObject[nCnt]->SetRotation(m_rot);
			}

			//�ʒu�̍X�V
			m_pos += m_move;

			//�ړ��ʂ��X�V
			m_move.x += (0.0f - m_move.x) * ENEMYSPEEDUP;
			m_move.y += (0.0f - m_move.y) * ENEMYSPEEDUP;

			//�����̃J�E���^�[
			m_apObject[nCnt]->m_nCounterMove++;

			//�e�̃J�E���^�[
			m_apObject[nCnt]->m_nCounterBullet++;

			//�ʒu�̐ݒ�
			m_apObject[nCnt]->SetPosition(m_pos);

			//�ߋ��̈ʒu�̐ݒ�
			m_apObject[nCnt]->SetPositionOld(m_posOld);

			//�ړ��ʂ̐ݒ�
			m_apObject[nCnt]->SetMove(m_move);

			//�����̐ݒ�
			m_apObject[nCnt]->SetRotation(m_rot);
		}
	}
}
//-------------------------------------------------------
//��ԊǗ��ݒ�
//-------------------------------------------------------
void CEnemy3D::UpdateEnemyState(void)
{
	switch (m_state)
	{
	case ENEMYSTATE_NORMAL:
		break;

	case ENEMYSTATE_DAMAGE:

		for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
		{
			//m_apObject[nCnt]��NULL����Ȃ�������
			if (m_apObject[nCnt] != NULL)
			{
				D3DXVECTOR3 m_pos = m_apObject[nCnt]->GetPosition();  //�ʒu�̎擾
				D3DXVECTOR3 m_move = m_apObject[nCnt]->GetMove();	  //�ړ��ʂ̎擾

				//�l��ݒ�
				m_apObject[nCnt]->SetPosition(m_pos);
				m_apObject[nCnt]->SetMove(m_move);
			}
		}

		m_nCounterState--;

		if (m_nCounterState <= 0)
		{
			m_state = ENEMYSTATE_NORMAL;

			break;
		}
	}
}
//-------------------------------------------------------
//��ԊǗ��ݒ�
//-------------------------------------------------------
void CEnemy3D::MoveEnemy(void)
{
	switch (m_movestate)
	{
	case ENEMYMOVE_RIGHT:  //�E�Ɉړ�����

		for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
		{
			//m_apObject[nCnt]��NULL����Ȃ�������
			if (m_apObject[nCnt] != NULL)
			{
				D3DXVECTOR3 m_move = m_apObject[nCnt]->GetMove();	  //�ړ��ʂ̎擾
				m_move.x = 1.0f;
				m_apObject[nCnt]->SetMove(m_move);
			}
		}

		break;

	case ENEMYMOVE_LEFT:  //���Ɉړ�����

		for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
		{
			//m_apObject[nCnt]��NULL����Ȃ�������
			if (m_apObject[nCnt] != NULL)
			{
				D3DXVECTOR3 m_move = m_apObject[nCnt]->GetMove();	  //�ړ��ʂ̎擾
				m_move.x = -1.0f;
				m_apObject[nCnt]->SetMove(m_move);
			}
		}

		break;

	case ENEMYMOVE_AUTO:  //�����I�Ɉړ�����

		for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
		{
			//m_apObject[nCnt]��NULL����Ȃ�������
			if (m_apObject[nCnt] != NULL)
			{
				D3DXVECTOR3 m_move = m_apObject[nCnt]->GetMove();	  //�ړ��ʂ̎擾
				D3DXVECTOR3 m_rot = m_apObject[nCnt]->GetRotation();  //�����̎擾

				//�v���C���[���������̎�
				if (m_rot.y == (D3DX_PI * 0.5f))
				{
					m_move.x = -1.0f;
				}

				//�v���C���[���E�����̎�
				if (m_rot.y == (-D3DX_PI * 0.5f))
				{
					m_move.x = 1.0f;
				}

				m_apObject[nCnt]->SetMove(m_move);   //�ړ��ʂ̐ݒ�
			}
		}

		break;
	}
}
//-------------------------------------------------------
//�G�̃q�b�g����
//-------------------------------------------------------
void CEnemy3D::HitEnemy(int nDamage, int nCnt)
{
	//�T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetSound();

	if (m_apObject[nCnt] != NULL)
	{
		m_apObject[nCnt]->m_Life -= nDamage;
		int typetex = m_apObject[nCnt]->GetTypeTex();
		D3DXVECTOR3 m_pos = m_apObject[nCnt]->GetPosition();  //�ʒu�̎擾
		D3DXVECTOR3 m_rot = m_apObject[nCnt]->GetRotation();  //�����̎擾

		if (m_apObject[nCnt]->m_Life <= 0)
		{
			if (typetex == TYPE_KOUMORI)
			{
				//�����̐���
				CExplosion::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z));

				//���S���
				m_apObject[nCnt]->SetState(CObject::STATE_DEATH, 0);

				//�����̏I������
				m_apObject[nCnt]->Uninit();

				//�Q�[���̏�Ԃ̐ݒ�
				CGame::SetGameState(CGame::GAMESTATE_END, 60);
			}

			else if (typetex == TYPE_OOKAMI)
			{
				//�����̐���
				CExplosion::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z));

				//���S���
				m_apObject[nCnt]->SetState(CObject::STATE_DEATH, 0);

				//�����̏I������
				m_apObject[nCnt]->Uninit();
			}

			//SE�̍Đ�
			//pSound->PlaySound(SOUND_LABEL_SE_EXPLOSION);
		}

		else
		{
			m_apObject[nCnt]->SetState(CObject::STATE_DAMAGE, 20);  //�_���[�W���
			m_apObject[nCnt]->SetEnemyState(ENEMYSTATE_DAMAGE, 60);  //�_���[�W���

			//SE�̍Đ�
			//pSound->PlaySound(SOUND_LABEL_SE_DAMAGE);
		}
	}
}
//-------------------------------------------------------
//�e�Ƃ̓����蔻��
//-------------------------------------------------------
bool CEnemy3D::CollisionBullet(CBullet3D *pBullet)
{
	CObject::TYPE type;  //���

	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		if (m_apObject[nCnt] != NULL)
		{
			int typetex = m_apObject[nCnt]->GetTypeTex();
			type = pBullet->GetType();  //��ނ��擾

			//��ނ��e�̏ꍇ
			if (type == CObject::TYPE_BULLET)
			{
				D3DXVECTOR3 m_pos = m_apObject[nCnt]->GetPosition();  //�ʒu�̎擾
				D3DXVECTOR3 m_size = m_apObject[nCnt]->GetScale();  //�T�C�Y�̎擾
				D3DXVECTOR3 posBullet = pBullet->GetPosition();  //�e�̈ʒu�擾
				D3DXVECTOR3 sizeBullet = pBullet->GetScale();  //�e�̃T�C�Y�擾

				//�R�E�����̎�
				if (typetex == TYPE_KOUMORI)
				{
					//�G�Əd�Ȃ�����
					if (m_pos.x + m_size.x >= posBullet.x - sizeBullet.x - 40.0f
						&&  m_pos.x - m_size.x <= posBullet.x + sizeBullet.x + 40.0f
						&&  m_pos.y + m_size.y + 40.0f >= posBullet.y - sizeBullet.y
						&&  m_pos.y - m_size.y - 40.0f <= posBullet.y + sizeBullet.y)
					{
						//�G�̃q�b�g����
						CEnemy3D::HitEnemy(100, nCnt);

						return TRUE;
					}
				}

				//�T�̎�
				else if (typetex == TYPE_OOKAMI)
				{
					//�G�Əd�Ȃ�����
					if (m_pos.x + m_size.x >= posBullet.x - sizeBullet.x - 40.0f
						&&  m_pos.x - m_size.x <= posBullet.x + sizeBullet.x + 40.0f
						&&  m_pos.y + m_size.y + 80.0f >= posBullet.y - sizeBullet.y
						&&  m_pos.y - m_size.y <= posBullet.y + sizeBullet.y)
					{
						//�G�̃q�b�g����
						CEnemy3D::HitEnemy(100, nCnt);

						return TRUE;
					}
				}
			}
		}
	}

	return FALSE;
}
//-------------------------------------------------------
//�v���C���[���ːi�U����Ԃ̎��̓G�Ƃ̓����蔻��
//-------------------------------------------------------
bool CEnemy3D::AttackCollision(CPlayer3D *pPlayer)
{
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		if (m_apObject[nCnt] != NULL)
		{
			D3DXVECTOR3 m_pos = m_apObject[nCnt]->GetPosition();  //�ʒu�̎擾
			D3DXVECTOR3 m_size = m_apObject[nCnt]->GetScale();  //�g�嗦�̎擾
			CObject::TYPE type;  //���
			int typetex;

			//��ނ��擾
			type = pPlayer->GetType();

			//��ނ��G�̏ꍇ
			if (type == CObject::TYPE_PLAYER)
			{
				D3DXVECTOR3 posPlayer = pPlayer->GetPosition();  //�v���C���[�̈ʒu�̎擾
				D3DXVECTOR3 sizePlayer = pPlayer->GetScale();  //�v���C���[�̊g�嗦�̎擾
				typetex = m_apObject[nCnt]->GetTypeTex();  //�G�̎��

				//�G���R�E�����̎�
				if (typetex == CEnemy3D::TYPE_KOUMORI)
				{
					//�G�Əd�Ȃ�����
					if (m_pos.x - m_size.x <= posPlayer.x + sizePlayer.x + 50.0f
						&&  m_pos.x + m_size.x >= posPlayer.x - sizePlayer.x - 50.0f
						&&  m_pos.y - m_size.y <= posPlayer.y + sizePlayer.y + 50.0f
						&&  m_pos.y + m_size.y >= posPlayer.y - sizePlayer.y - 50.0f
						&&  m_pos.z - m_size.z <= posPlayer.z + sizePlayer.z + 50.0f
						&&  m_pos.z + m_size.z >= posPlayer.z - sizePlayer.z - 50.0f)
					{
						//�G�̃q�b�g����
						CEnemy3D::HitEnemy(200, nCnt);

						return TRUE;
					}
				}

				//�G���T�̎�
				else if (typetex == CEnemy3D::TYPE_OOKAMI)
				{
					//�G�Əd�Ȃ�����
					if (m_pos.x - m_size.x <= posPlayer.x + sizePlayer.x + 50.0f
						&&  m_pos.x + m_size.x >= posPlayer.x - sizePlayer.x - 50.0f
						&&  m_pos.y - m_size.y <= posPlayer.y + sizePlayer.y + 50.0f
						&&  m_pos.y + m_size.y >= posPlayer.y - sizePlayer.y - 50.0f
						&&  m_pos.z - m_size.z <= posPlayer.z + sizePlayer.z + 50.0f
						&&  m_pos.z + m_size.z >= posPlayer.z - sizePlayer.z - 50.0f)
					{
						//�G�̃q�b�g����
						CEnemy3D::HitEnemy(200, nCnt);

						return TRUE;
					}
				}
			}
		}
	}

	return FALSE;
}
//-------------------------------------------------------
//�̗͂̐ݒ菈��
//-------------------------------------------------------
void CEnemy3D::SetLife(int Life)
{
	m_Life = Life;
}
//-------------------------------------------------------
//��ԊǗ��ݒ�
//-------------------------------------------------------
void CEnemy3D::SetEnemyState(ENEMYSTATE state, int nCounterState)
{
	m_state = state;
	m_nCounterState = nCounterState;
}
//-------------------------------------------------------
//�ړ��Ǘ��ݒ�
//-------------------------------------------------------
void CEnemy3D::SetEnemyMoveState(ENEMYMOVE statemove)
{
	m_movestate = statemove;
}