//=============================================================================
//
// �v���C���[3D���� [player3D.cpp]
// Author ��� ��^
//
//=============================================================================
#include "player3D.h"
#include "manager.h"
#include "bullet3D.h"
#include "explosion.h"
#include "game.h"
#include "modelset.h"
#include "block3D.h"
#include "life.h"
#include "attackgage.h"

//�}�N����`
#define PLAYERSPEED (3.0f)  //�ړ����̃X�s�[�h
#define PLAYERSPEEDUP (0.2f)  //�ړ��ʍX�V���̃X�s�[�h
#define PLAYERJAMPSPEED (3.0f)  //�W�����v���̗����X�s�[�h
#define JAMPCNT (10)  //�d�͂�������܂ł̃J�E���g
#define BULLETSPEED (7.0f)  //�v���C���[�̒e�X�s�[�h
#define ATTACKCNT (10)  //�A�^�b�N�J�E���g
#define ATTACKGAGE (100)  //�A�^�b�N�Q�[�W

//�ÓI�����o�ϐ�
CPlayer3D *CPlayer3D::m_apObject = NULL;

//-------------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------------
CPlayer3D::CPlayer3D()
{
	if (m_apObject == NULL)
	{
		m_apObject = this;
	}
}
//-------------------------------------------------------
//�f�X�g���N�^
//-------------------------------------------------------
CPlayer3D::~CPlayer3D()
{

}
//-------------------------------------------------------
//����������
//-------------------------------------------------------
HRESULT CPlayer3D::Init()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	CModel *pModel = CManager::GetModel();  //���f���̃|�C���^

	//���f����錾
	m_nIdxModel = pModel->Regist("data\\MODEL\\rob001.x");  //�v���C���[

	//�I�u�W�F�N�gX�̏���������
	CObjectX::Init();

	//��ނ̐ݒ�
	CObject::SetType(TYPE_PLAYER);

	//��ԊǗ��ݒ�
	CObjectX::SetState(CObject::STATE_NORMAL, 0);

	//���C�t�̐ݒ�
	m_Life = 500;

	//�l��������
	m_nCnt = 0;
	m_nCntState = 0;
	m_nCntDown = 0;
	m_nCntAttack = 0;
	m_AttackGage = ATTACKGAGE;
	m_jump = PLAYERJUMP_GROUND;
	m_AttackState = ATTACKSTATE_NONE;
	m_BattleState = BATTLESTATE_PROXIMITY;
	m_WarpState = WARPSTATE_FALSE;
	m_StartPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return (S_OK);
}
//-------------------------------------------------------
//�I������
//-------------------------------------------------------
void CPlayer3D::Uninit()
{
	//�I�u�W�F�N�gX�̏I������
	CObjectX::Uninit();

	m_apObject = NULL;
}
//-------------------------------------------------------
//�X�V����
//-------------------------------------------------------
void CPlayer3D::Update()
{
	D3DXVECTOR3 m_pos = GetPosition();  //�ʒu�̎擾
	D3DXVECTOR3 m_move = GetMove();	//�ړ��ʂ̎擾
	D3DXVECTOR3 m_rot = GetRotation();  //�����̎擾
	D3DXVECTOR3 m_size = GetSize();        //�T�C�Y�̎擾

	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�Q�[���p�b�h�̎擾
	CInputPad *pInputPad;
	pInputPad = CManager::GetInputPad();

	//�T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetSound();

	SetPositionOld(m_pos);  //�ߋ��̈ʒu�ݒ�

	//��ԊǗ��ݒ�
	CObject::UpdateState();

	//�v���C���[�̋ߐڍU��
	CEnemy3D::PlayerAttack(this);

	//�G�̈ړ�
	CEnemy3D::MoveEnemy(this);

	m_nCntState = 0;

	if (m_AttackState == ATTACKSTATE_NONE)
	{
		///////////////////////////////////////////
		//�v���C���[�L�[�{�[�h����
		///////////////////////////////////////////
		//D�L�[��������Ă��鎞
		if (pInputKeyboard->GetPress(DIK_D) == true || pInputPad->CInputPad::GetJoyStickLX(0) > 0)
		{
			//D�L�[�������ꂽ
			m_move.x += sinf(D3DX_PI * 0.5f) * PLAYERSPEED;
			m_rot.y = (-D3DX_PI * 0.5f);
		}

		//A�L�[��������Ă��鎞
		else if (pInputKeyboard->GetPress(DIK_A) == true || pInputPad->CInputPad::GetJoyStickLX(0) < 0)
		{
			//A�L�[�������ꂽ
			m_move.x += sinf(D3DX_PI * -0.5f) * PLAYERSPEED;
			m_rot.y = (D3DX_PI * 0.5f);	
		}

		//�W�����v
		if (pInputKeyboard->GetTrigger(DIK_SPACE) == true && m_jump == PLAYERJUMP_GROUND   //SPACE�������ꂽ��
			|| pInputPad->GetTrigger(CInputPad::BUTTON_A, 0) && m_jump == PLAYERJUMP_GROUND)  //A�{�^���������ꂽ��
		{
			m_move.y = 60.0f;     //��Ɉړ�����
			//m_move.y -= 3.0f;     //�d�͂�������
			m_pos.y -= m_move.y;  //����

			m_jump = PLAYERJUMP_SKY;  //�W�����v���Ă����Ԃɂ���

			m_nCntDown = 0;

			//SE�̍Đ�
			//pSound->PlaySound(SOUND_LABEL_SE_JAMP);
		}
	}

	//�ߐڏ�Ԃ̎�
	if (m_BattleState == BATTLESTATE_PROXIMITY  &&
		m_Attack == false)
	{
		if (m_AttackState == ATTACKSTATE_NONE)
		{
			if (m_AttackGage >= 25)
			{
				if (pInputKeyboard->GetTrigger(DIK_B) == true)  //B���������Ƃ�
				{
					m_AttackGage -= 25;  //�Q�[�W��25���炷
					m_AttackState = ATTACKSTATE_RUSHATTACK;  //�ːi�U����Ԃɐ؂�ւ�
					m_nCntAttack = ATTACKCNT;  //�A�^�b�N�J�E���g��ݒ�
					m_StartPos = m_pos;  //�ʒu��ۑ�
					m_Attack = true;
				}
			}
		}
	}

	if (m_nCntDown > JAMPCNT)
	{
		//�d�͂�������
		m_move.y -= PLAYERJAMPSPEED;
	}

	if (m_nCnt >= 10)
	{
		m_AttackGage++;  //�A�^�b�N�Q�[�W��+1����
		m_nCnt = 0;  //������
	}

	//�A�^�b�N�Q�[�W��100���������Ȃ�����
	if (m_AttackGage >= ATTACKGAGE)
	{
		m_AttackGage = ATTACKGAGE;  //100�ɌŒ�
	}

	//�C���N�������g
	m_nCnt++;
	m_nCntDown++;
	m_nCntBullet++;

	//�ʒu�̍X�V
	m_pos += m_move;

	//�ړ��ʂ��X�V
	m_move.x += (0.0f - m_move.x) * PLAYERSPEEDUP;
	m_move.y += (0.0f - m_move.y) * PLAYERSPEEDUP;
	m_move.z += (0.0f - m_move.z) * PLAYERSPEEDUP;

	///////////////////////////////////////////
	//��ʊO�ɏo����
	///////////////////////////////////////////
	////�E��
	//if (m_pos.x >= SCREEN_WIDTH - 100)
	//{
	//	m_pos.x = SCREEN_WIDTH - 100;
	//}

	//����
	if (m_pos.x <= -570)
	{
		m_pos.x = -570;
	}

	//������
	if (m_pos.y < 0)
	{
		m_pos.y = 0;
		m_move.y = 0;

		m_Attack = false;
		m_jump = PLAYERJUMP_GROUND;  //�W�����v���ĂȂ���Ԃɂ���
	}

	SetPosition(m_pos);  //�ʒu�̐ݒ�
	SetMove(m_move);  //�ړ��ʂ̐ݒ�
	SetRotation(m_rot);  //�����̐ݒ�
	SetLife(m_Life);  //���C�t�̐ݒ�
	SetAttackState(m_AttackState);  //�퓬��Ԃ̐ݒ�
	SetAttackGage(m_AttackGage);  //�A�^�b�N�Q�[�W�̐ݒ�
	CLife::LifeMove(this);  //���C�t�̈ړ���

	//�U����Ԃ̍X�V
	AttackState();

	CBlock3D::CollisionPlayer(this);  //�u���b�N�Ƃ̓����蔻��
	CModelSet::ModelCollision(this);  //���f���Ƃ̓����蔻��

	//-------------------------------------------------------
	//�v���C���[�̃f�o�b�N�\��
	//-------------------------------------------------------
	CManager::GetDebugProc()->Print("�v���C���[�ʒu [%f, %f, %f]\n", m_pos.x, m_pos.y, m_pos.z);
	CManager::GetDebugProc()->Print("�v���C���[�ړ��� [%f, %f, %f]\n", m_move.x, m_move.y, m_move.z);
	CManager::GetDebugProc()->Print("�v���C���[���� [%f, %f, %f]\n", m_rot.x, m_rot.y, m_rot.z);
	CManager::GetDebugProc()->Print("�v���C���[�̗� [%d]\n", m_Life);
	CManager::GetDebugProc()->Print("�v���C���[�̃A�^�b�N�Q�[�W [%d]\n", m_AttackGage);
}
//-------------------------------------------------------
//�`�揈��
//-------------------------------------------------------
void CPlayer3D::Draw()
{
	//�I�u�W�F�N�gX�̕`�揈��
	CObjectX::Draw();
}
//-------------------------------------------------------
//��������
//-------------------------------------------------------
CPlayer3D *CPlayer3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 size)
{
	CPlayer3D *pPlayer3D = NULL;

	//�v���C���[�̐���
	pPlayer3D = new CPlayer3D;

	if (pPlayer3D != NULL)
	{
		//����������
		pPlayer3D->Init();
	}

	else
	{//�����Ɏ��s�����ꍇ
		return NULL;
	}

	//�ʒu�̐ݒ�
	pPlayer3D->SetPosition(pos);

	//�����̐ݒ�
	pPlayer3D->SetRotation(rot);

	//�g�嗦�̐ݒ�
	pPlayer3D->SetScale(scale);

	//�T�C�Y�ݒ�
	pPlayer3D->SetSize(size);

	//���f���̊��蓖��
	pPlayer3D->BindModel(pPlayer3D->m_nIdxModel);

	//---------------------------------------------------------------
	//���C�t�̐���
	//---------------------------------------------------------------
	CLife::Create(D3DXVECTOR3(117.0f, 650.0f, 0.0f), D3DXVECTOR3(300.0f, 30.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), CLife::TYPE_LIFEGAUGE);
	CLife::Create(D3DXVECTOR3(10.0f, 650.0f, 0.0f), D3DXVECTOR3(410.0f, 40.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), CLife::TYPE_LIFEFRAME);

	//---------------------------------------------------------------
	//�A�^�b�N�Q�[�W�̐���
	//---------------------------------------------------------------
	CAttackGage::Create(D3DXVECTOR3(600.0f, 650.0f, 0.0f), D3DXVECTOR3(410.0f, 35.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), CAttackGage::TYPE_ATTACKFRAME);
	CAttackGage::Create(D3DXVECTOR3(625.0f, 647.0f, 0.0f), D3DXVECTOR3(360.0f, 18.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), CAttackGage::TYPE_ATTACKGAUGE);

	return pPlayer3D;
}
//-------------------------------------------------------
//�U�����
//-------------------------------------------------------
void CPlayer3D::AttackState(void)
{
	D3DXVECTOR3 m_pos = GetPosition();  //�ʒu�̎擾
	D3DXVECTOR3 m_move = GetMove();   //�ړ��ʂ̎擾
	D3DXVECTOR3 m_rot = GetRotation();  //�����̎擾
	D3DXVECTOR3 m_startpos = GetStartPos();  //�X�^�[�g�ʒu�̎擾

    //�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�Q�[���p�b�h�̎擾
	CInputPad *pInputPad;
	pInputPad = CManager::GetInputPad();

	switch (m_AttackState)
	{
	case ATTACKSTATE_NONE:  //�ʏ���

		//if (m_move.x >= 1.0f)
		//{
		//	if (m_rot.y <= (-D3DX_PI * 0.5f))
		//	{
		//		m_rot.y = (-D3DX_PI * 0.5f);

		//		SetRotation(m_rot);
		//	}
		//}

		break;

	case ATTACKSTATE_MELEEATTACK:  //�ߐڍU�����

		break;

	case	ATTACKSTATE_RUSHATTACK:  //�ːi�U�����
		
		//�v���C���[���E�����̎�
		if (m_rot.y == (-D3DX_PI * 0.5f))
		{
			if (m_jump == PLAYERJUMP_GROUND)
			{
				m_move = D3DXVECTOR3(30.0f, 0.0f, 0.0f);  //�U���X�s�[�h
			}

			else if (m_jump == PLAYERJUMP_SKY)
			{
				//D�L�[��������Ă��鎞
				if (pInputKeyboard->GetPress(DIK_D) == true || pInputPad->CInputPad::GetJoyStickLX(0) > 0)
				{
					if (pInputKeyboard->GetPress(DIK_W) == true)       //A�L�[��������Ă�Ƃ���W�L�[�������ꂽ
					{
						//�E��ړ�
						m_move = D3DXVECTOR3(30.0f, 30.0f, 0.0f);  //�U���X�s�[�h
					}

					else if (pInputKeyboard->GetPress(DIK_S) == true)  //A�L�[��������Ă�Ƃ���S�L�[�������ꂽ
					{
						//�E���ړ�
						m_move = D3DXVECTOR3(30.0f, -30.0f, 0.0f);  //�U���X�s�[�h
					}

					else
					{
						//D�L�[�������ꂽ
						m_move = D3DXVECTOR3(30.0f, 0.0f, 0.0f);  //�U���X�s�[�h
					}
				}

				//W�L�[��������Ă��鎞
				else if (pInputKeyboard->GetPress(DIK_W) == true)
				{
					//������ֈړ�
					m_move = D3DXVECTOR3(0.0f, 30.0f, 0.0f);  //�U���X�s�[�h
				}

				//S�L�[��������Ă��鎞
				else if (pInputKeyboard->GetPress(DIK_S) == true)
				{
					//�������ֈړ�
					m_move = D3DXVECTOR3(0.0f, -30.0f, 0.0f);  //�U���X�s�[�h
				}

				//����������ĂȂ��Ƃ�
				else
				{
					//�E�ɐi��
					m_move = D3DXVECTOR3(30.0f, 0.0f, 0.0f);  //�U���X�s�[�h
				}
			}

			if (m_nCntAttack < 0)
			{
				m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				m_nCntAttack = 0;
				m_AttackState = ATTACKSTATE_NONE;
			}

			//SE�̍Đ�
			//pSound->PlaySound(SOUND_LABEL_SE_FIRING);
		}

		//�v���C���[���������̎�
		if (m_rot.y == (D3DX_PI * 0.5f))
		{
			if (m_jump == PLAYERJUMP_GROUND)
			{
				m_move = D3DXVECTOR3(-30.0f, 0.0f, 0.0f);  //�U���X�s�[�h
			}

			else if (m_jump == PLAYERJUMP_SKY)
			{
				//A�L�[��������Ă��鎞
				if (pInputKeyboard->GetPress(DIK_A) == true || pInputPad->CInputPad::GetJoyStickLX(0) < 0)
				{
					if (pInputKeyboard->GetPress(DIK_W) == true)       //A�L�[��������Ă�Ƃ���W�L�[�������ꂽ
					{
						//����ړ�
						m_move = D3DXVECTOR3(-30.0f, 30.0f, 0.0f);  //�U���X�s�[�h
					}

					else if (pInputKeyboard->GetPress(DIK_S) == true)  //A�L�[��������Ă�Ƃ���S�L�[�������ꂽ
					{
						//�����ړ�
						m_move = D3DXVECTOR3(-30.0f, -30.0f, 0.0f);  //�U���X�s�[�h
					}

					else
					{
						//A�L�[�������ꂽ
						m_move = D3DXVECTOR3(-30.0f, 0.0f, 0.0f);  //�U���X�s�[�h
					}
				}

				//W�L�[��������Ă��鎞
				else if (pInputKeyboard->GetPress(DIK_W) == true)
				{
					//������ֈړ�
					m_move = D3DXVECTOR3(0.0f, 30.0f, 0.0f);  //�U���X�s�[�h
				}

				//S�L�[��������Ă��鎞
				else if (pInputKeyboard->GetPress(DIK_S) == true)
				{
					//�������ֈړ�
					m_move = D3DXVECTOR3(0.0f, -30.0f, 0.0f);  //�U���X�s�[�h
				}

				//����������ĂȂ��Ƃ�
				else
				{
					//���ɐi��
					m_move = D3DXVECTOR3(-30.0f, 0.0f, 0.0f);  //�U���X�s�[�h
				}
			}

			if (m_nCntAttack < 0)
			{
				m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				m_nCntAttack = 0;
				m_AttackState = ATTACKSTATE_NONE;
			}

			//SE�̍Đ�
			//pSound->PlaySound(SOUND_LABEL_SE_FIRING);
		}

		//�G�Ƃ̓����蔻��
		CEnemy3D::AttackCollision(this);

		m_nCntAttack--;
		SetMove(m_move);

		break;
	}
}
//-------------------------------------------------------
//�v���C���[�̃q�b�g����
//-------------------------------------------------------
void CPlayer3D::HitPlayer(int nDamage)
{
	//�T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetSound();

	if (m_apObject != NULL)
	{
		m_apObject->m_Life -= nDamage;

		D3DXVECTOR3 m_pos = m_apObject->GetPosition();  //�ʒu�̎擾
		D3DXVECTOR3 m_rot = m_apObject->GetRotation();  //�����̎擾

		if (m_apObject->m_Life <= 0)
		{
			//�����̐���
			CExplosion::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z));

			m_apObject->SetState(CObject::STATE_DEATH, 0);  //���S���

			//�����̏I������
			m_apObject->Uninit();

			//�Q�[���̏�Ԃ̐ݒ�
			CGame::SetGameState(CGame::GAMESTATE_END, 60);

			//SE�̍Đ�
			//pSound->PlaySound(SOUND_LABEL_SE_DEATH);
		}
		else
		{
			//�v���C���[���E�����̎�
			if (m_rot.y == (-D3DX_PI * 0.5f))
			{
				m_pos.x -= 150.0f;
			}

			//�v���C���[���������̎�
			else if (m_rot.y == (D3DX_PI * 0.5f))
			{
				m_pos.x += 150.0f;
			}

			m_apObject->SetPosition(m_pos);
			m_apObject->SetState(CObject::STATE_DAMAGE, 20);  //�_���[�W���

			//SE�̍Đ�
			//pSound->PlaySound(SOUND_LABEL_SE_DAMAGE);
		}
	}
}
//-------------------------------------------------------
//�G�Ƃ̓����蔻��
//-------------------------------------------------------
bool CPlayer3D::CollisionEnemy(CEnemy3D *pEnemy)
{	
	if (m_apObject != NULL)
	{
		D3DXVECTOR3 m_pos = m_apObject->GetPosition();  //�ʒu�̎擾
		D3DXVECTOR3 m_size = m_apObject->GetScale();    //�g�嗦�̎擾
		CObject::TYPE type;  //���
		int typetex = 0;  //�G�̎�ޗp
		int BattleState = m_apObject->GetAttackState();  //�v���C���[�̍U����Ԏ擾
		type = pEnemy->GetType();   //��ނ��擾

		//��ނ��G�̏ꍇ
		if (type == CObject::TYPE_ENEMY)
		{
			D3DXVECTOR3 posEnemy = pEnemy->GetPosition();  //�G�̈ʒu�̎擾
			D3DXVECTOR3 sizeEnemy = pEnemy->GetScale();  //�G�̊g�嗦�̎擾
			typetex = pEnemy->GetTypeTex();  //�G�̎��

			//�G���R�E�����̎�
			if (typetex == CEnemy3D::TYPE_KOUMORI)
			{
				//�G�Əd�Ȃ�����
				if (m_pos.x - m_size.x <= posEnemy.x + sizeEnemy.x + 50.0f
					&&  m_pos.x + m_size.x >= posEnemy.x - sizeEnemy.x - 50.0f
					&&  m_pos.y - m_size.y <= posEnemy.y + sizeEnemy.y + 50.0f
					&&  m_pos.y + m_size.y >= posEnemy.y - sizeEnemy.y - 50.0f)
				{
					if (BattleState != CPlayer3D::ATTACKSTATE_RUSHATTACK)
					{
						//�v���C���[�̃q�b�g����
						HitPlayer(100);
					}

					return TRUE;
				}
			}

			//�G���T�̎�
			else if (typetex == CEnemy3D::TYPE_OOKAMI)
			{
				//�G�Əd�Ȃ�����
				if (m_pos.x - m_size.x <= posEnemy.x + sizeEnemy.x + 40.0f
					&&  m_pos.x + m_size.x >= posEnemy.x - sizeEnemy.x - 40.0f
					&&  m_pos.y - m_size.y <= posEnemy.y + sizeEnemy.y + 50.0f
					&&  m_pos.y + m_size.y >= posEnemy.y - sizeEnemy.y - 50.0f
					&&  m_pos.z - m_size.z <= posEnemy.z + sizeEnemy.z + 50.0f
					&&  m_pos.z + m_size.z >= posEnemy.z - sizeEnemy.z - 50.0f)
				{
					//�ːi�U����Ԃ���Ȃ���
					if (BattleState != CPlayer3D::ATTACKSTATE_RUSHATTACK)
					{
						//�v���C���[�̃q�b�g����
						HitPlayer(100);
					}

					return TRUE;
				}
			}
		}
	}
	
	return FALSE;
}
//-------------------------------------------------------
//�e�Ƃ̓����蔻��
//-------------------------------------------------------
bool CPlayer3D::CollisionBullet(CBullet3D *pBullet)
{
	D3DXVECTOR3 posBullet = pBullet->GetPosition();  //�e�̈ʒu�擾
	D3DXVECTOR3 sizeBullet = pBullet->GetScale();    //�e�̃T�C�Y�擾
	CObject::TYPE type;  //���

	//��ނ��擾
	type = pBullet->GetType();

	if (m_apObject != NULL)
	{
		//��ނ��e�̏ꍇ
		if (type == CObject::TYPE_BULLET)
		{
			D3DXVECTOR3 m_pos = m_apObject->GetPosition();  //�ʒu�̎擾
			D3DXVECTOR3 m_size = m_apObject->GetScale();  //�T�C�Y�̎擾

			//�v���C���[�Əd�Ȃ�����
			if (m_pos.x + m_size.x >= posBullet.x - sizeBullet.x - 40.0f
			&&  m_pos.x - m_size.x <= posBullet.x + sizeBullet.x + 40.0f
			&&  m_pos.y + m_size.y + 80.0f >= posBullet.y - sizeBullet.y
			&&  m_pos.y - m_size.y <= posBullet.y + sizeBullet.y)
			{
				//�v���C���[�̃q�b�g����
				CPlayer3D::HitPlayer(100);

				return TRUE;
			}
		}
	}

	return FALSE;
}
//-------------------------------------------------------
//�A�^�b�N�Q�[�W�ݒ菈��
//-------------------------------------------------------
void CPlayer3D::AttackGageMove(CAttackGage *pAttackGage)
{
	if (m_apObject != NULL)
	{
		CObject::TYPE type;  //���

		//��ނ��擾
		type = pAttackGage->GetType();
		int typetex = pAttackGage->GetTypeTex();

		//�^�C�v���A�^�b�N�Q�[�W�̏ꍇ
		if (type == CObject::TYPE_ATTACKGAGE)
		{
			int m_AttackGagePlayer = m_apObject->GetAttackGage();  //�A�^�b�N�Q�[�W�擾
			int Gage = pAttackGage->GetGage();

			if (m_AttackGagePlayer >= 100 &&
				Gage != CAttackGage::TYPE_GAUGE_1)
			{
				if (typetex == CAttackGage::TYPE_ATTACKGAUGE)
				{
					pAttackGage->Uninit();
				}

				//---------------------------------------------------------------
				//�A�^�b�N�Q�[�W�̐���
				//---------------------------------------------------------------
				CAttackGage::Create(D3DXVECTOR3(625.0f, 647.0f, 0.0f), D3DXVECTOR3(360.0f, 18.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), CAttackGage::TYPE_ATTACKGAUGE);

				Gage = CAttackGage::TYPE_GAUGE_1;
			}

			if (m_AttackGagePlayer >= 75 &&
				m_AttackGagePlayer < 100 &&
				Gage != CAttackGage::TYPE_GAUGE_2)
			{
				if (typetex == CAttackGage::TYPE_ATTACKGAUGE)
				{
					pAttackGage->Uninit();
				}

				//---------------------------------------------------------------
				//�A�^�b�N�Q�[�W�̐���
				//---------------------------------------------------------------
				CAttackGage::Create(D3DXVECTOR3(625.0f, 647.0f, 0.0f), D3DXVECTOR3(270.0f, 18.0f, 0.0f), D3DXVECTOR3(0.75f, 0.0f, 0.0f), CAttackGage::TYPE_ATTACKGAUGE);

				Gage = CAttackGage::TYPE_GAUGE_2;
			}

			if (m_AttackGagePlayer >= 50 &&
				m_AttackGagePlayer < 75 &&
				Gage != CAttackGage::TYPE_GAUGE_3)
			{
				if (typetex == CAttackGage::TYPE_ATTACKGAUGE)
				{
					pAttackGage->Uninit();
				}

				//---------------------------------------------------------------
				//�A�^�b�N�Q�[�W�̐���
				//---------------------------------------------------------------
				CAttackGage::Create(D3DXVECTOR3(625.0f, 647.0f, 0.0f), D3DXVECTOR3(180.0f, 18.0f, 0.0f), D3DXVECTOR3(0.5f, 0.0f, 0.0f), CAttackGage::TYPE_ATTACKGAUGE);

				Gage = CAttackGage::TYPE_GAUGE_3;
			}

			if (m_AttackGagePlayer >= 25 &&
				m_AttackGagePlayer < 50 &&
				Gage != CAttackGage::TYPE_GAUGE_4)
			{
				if (typetex == CAttackGage::TYPE_ATTACKGAUGE)
				{
					pAttackGage->Uninit();
				}

				//---------------------------------------------------------------
				//�A�^�b�N�Q�[�W�̐���
				//---------------------------------------------------------------
				CAttackGage::Create(D3DXVECTOR3(625.0f, 647.0f, 0.0f), D3DXVECTOR3(90.0f, 18.0f, 0.0f), D3DXVECTOR3(0.25f, 0.0f, 0.0f), CAttackGage::TYPE_ATTACKGAUGE);

				Gage = CAttackGage::TYPE_GAUGE_4;
			}

			if (m_AttackGagePlayer >= 0 &&
				m_AttackGagePlayer < 25 &&
				Gage != CAttackGage::TYPE_GAUGE_5)
			{
				if (typetex == CAttackGage::TYPE_ATTACKGAUGE)
				{
					pAttackGage->Uninit();
				}

				//---------------------------------------------------------------
				//�A�^�b�N�Q�[�W�̐���
				//---------------------------------------------------------------
				CAttackGage::Create(D3DXVECTOR3(625.0f, 647.0f, 0.0f), D3DXVECTOR3(0.0f, 18.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CAttackGage::TYPE_ATTACKGAUGE);

				Gage = CAttackGage::TYPE_GAUGE_5;
			}

			pAttackGage->SetAttackGage(Gage);
		}
	}
}
//-------------------------------------------------------
//�̗͂̐ݒ菈��
//-------------------------------------------------------
void CPlayer3D::SetPlayerJump(PLAYERJAMP Jamp)
{
	m_jump = Jamp;
}
//-------------------------------------------------------
//�̗͂̐ݒ菈��
//-------------------------------------------------------
void CPlayer3D::SetLife(int Life)
{
	m_Life = Life;
}
//-------------------------------------------------------
//�U���̐ݒ菈��
//-------------------------------------------------------
void CPlayer3D::SetAttack(bool Attack)
{
	m_Attack = Attack;
}
//-------------------------------------------------------
//�U����Ԃ̐ݒ菈��
//-------------------------------------------------------
void CPlayer3D::SetAttackState(ATTACKSTATE AttackState)
{
	m_AttackState = AttackState;
}
//-------------------------------------------------------
//�A�^�b�N�Q�[�W�̐ݒ菈��
//-------------------------------------------------------
void CPlayer3D::SetAttackGage(int AttackGage)
{
	m_AttackGage = AttackGage;
}