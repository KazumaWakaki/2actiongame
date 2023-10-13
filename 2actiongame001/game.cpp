//=======================================================
//
// �Q�[������ [game.cpp]
// Author ��؈�^
//
//=======================================================
#include "game.h"
#include "modelset.h"
#include "player3D.h"
#include "enemy3D.h"
#include "block3D.h"
#include "wall.h"

//�}�N����`
#define WALL_MAX  (7)  //�w�i�ǂ̐��l
#define START_TIME	(420)	//��������

//�ÓI�����o�ϐ�
CGame *CGame::m_apObject = NULL;

//-------------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------------
CGame::CGame()
{
	if (m_apObject == NULL)
	{
		m_apObject = this;
	}

	//m_pTime = NULL;
}
//-------------------------------------------------------
//�f�X�g���N�^
//-------------------------------------------------------
CGame::~CGame()
{

}
//-------------------------------------------------------
//�Q�[����ʂ̏���������
//-------------------------------------------------------
HRESULT CGame::Init(void)
{
	//�T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetSound();

	//�V�[���̏���������
	CScene::Init();

	//---------------------------------------------------------------
	//�ǂ̐���
	//---------------------------------------------------------------
	for (int nCntWall = 0; nCntWall <= WALL_MAX; nCntWall++)
	{
		CWall::Create(D3DXVECTOR3(30.0f + 620.0f * nCntWall, 150.0f, 200.0f), D3DXVECTOR3(0.0f, 0, 0.0f), D3DXVECTOR3(640.0f, 360.0f, 0.0f), CWall::TYPE_HAIKEI001);
	}

	//---------------------------------------------------------------
	//�u���b�N�̔z�u
	//---------------------------------------------------------------
	CBlock3D::Create(D3DXVECTOR3(1000.0f, -400.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(800.0f, 20.0f, 2.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //��
	CBlock3D::Create(D3DXVECTOR3(-770.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(20.0f, 40.0f, 2.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));      //����
	CBlock3D::Create(D3DXVECTOR3(-200.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 2.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));        //
	CBlock3D::Create(D3DXVECTOR3(0.0f, 200.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 2.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));        //
	CBlock3D::Create(D3DXVECTOR3(700.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(20.0f, 2.0f, 2.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));        //1�ڂ̒i��

	CBlock3D::Create(D3DXVECTOR3(1000.0f, -400.0f, -2000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(800.0f, 20.0f, 2.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //��
	CBlock3D::Create(D3DXVECTOR3(-770.0f, 0.0f, -2000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(20.0f, 40.0f, 2.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));      //����
	CBlock3D::Create(D3DXVECTOR3(0.0f, 120.0f, -2000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 2.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));        //
	CBlock3D::Create(D3DXVECTOR3(700.0f, 0.0f, -2000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(20.0f, 2.0f, 2.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));        //1�ڂ̒i��

	//---------------------------------------------------------------
	//���f���̐���
	//---------------------------------------------------------------
	CModelSet::Create(D3DXVECTOR3(1800.0f, 0.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.3f, 0.3f, 0.3f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelSet::TYPE_GATE_1);  //�Q�[�g1��
	CModelSet::Create(D3DXVECTOR3(700.0f, 40.0f, -1800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.3f, 0.3f, 0.3f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelSet::TYPE_GATE_2);  //�Q�[�g2��

	//---------------------------------------------------------------
	//�G3D�̐���
	//---------------------------------------------------------------
	CEnemy3D::Create(D3DXVECTOR3(400.0f, 0.0f, -5.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXVECTOR3(1.0f, 1.2f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy3D::TYPE_OOKAMI, 200);
	CEnemy3D::Create(D3DXVECTOR3(1200.0f, 0.0f, -5.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXVECTOR3(1.0f, 1.2f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy3D::TYPE_OOKAMI, 200);

	//---------------------------------------------------------------
	//�v���C���[3D�̐���
	//---------------------------------------------------------------
	CPlayer3D::Create(D3DXVECTOR3(-400.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f), D3DXVECTOR3(0.3f, 0.3f, 0.3f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//BGM�̍Đ�
	//pSound->PlaySound(SOUND_LABEL_BGM_GAME);

	return (S_OK);
}
//-------------------------------------------------------
//�Q�[����ʂ̏I������
//-------------------------------------------------------
void CGame::Uninit(void)
{
	//�T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetSound();

	//BGM�̍Đ�
	pSound->StopSound();

	//�V�[���̏I������
	CScene::Uninit();

	if (m_apObject != NULL)
	{
		m_apObject = NULL;
	}
}
//-------------------------------------------------------
//�Q�[����ʂ̍X�V����
//-------------------------------------------------------
void CGame::Update(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	if (pInputKeyboard->GetTrigger(DIK_R) == true)  //ENTER�L�[�������ꂽ
	{
		//���[�h�ݒ�(���U���g�Ɉڍs)
		CManager::SetMode(MODE_RESULT);
		//CManager::GetFade()->Set(CScene::MODE_RESULT);

		////�T�E���h�̍Đ�
		//PlaySound(SOUND_LABEL_SE_NEXT);
	}

	switch (m_gameState)
	{
	case GAMESTATE_NORMAL:  //�ʏ���
		break;

	case GAMESTATE_RESET:  //���Z�b�g���

		m_nCounterGameState++;

		if (m_nCounterGameState >= 10)
		{
			m_nCounterGameState = 0;
			m_gameState = GAMESTATE_NORMAL;  //�ʏ��Ԃɐݒ�
		}

		break;

	case GAMESTATE_END:  //�I�����

		m_nCounterGameState--;

		if (m_nCounterGameState <= 0)
		{
			m_gameState = GAMESTATE_NONE;  //�������Ă��Ȃ���Ԃɐݒ�

			//���[�h�ݒ�(���U���g�Ɉڍs)
			CManager::SetMode(MODE_RESULT);
			//CManager::GetFade()->Set(CScene::MODE_RESULT);

			////���[�h�ݒ�(���U���g��ʂɈڍs)
			//SetFade(MODE_RESULT);
		}

		break;
	}
}
//-------------------------------------------------------
//�Q�[����ʂ̕`�揈��
//-------------------------------------------------------
void CGame::Draw(void)
{
	//�V�[���̕`�揈��
	CScene::Draw();
}
//-------------------------------------------------------
//�Q�[���̏�Ԃ̐ݒ�
//-------------------------------------------------------
void CGame::SetGameState(GAMESTATE state, int nCounter)
{
	if (m_apObject != NULL)
	{
		m_apObject->m_gameState = state;
		m_apObject->m_nCounterGameState = nCounter;
	}
}
//-------------------------------------------------------
//�Q�[���̃|�[�Y��Ԃ̎擾
//-------------------------------------------------------
void CGame::SetEnablePause(bool Pause)
{
	m_bPause = Pause;
}
//-------------------------------------------------------
// �^�C�}�[�̎擾
//-------------------------------------------------------
//CTime *CGame::GetTime(void)
//{
//	return m_pTime;
//}