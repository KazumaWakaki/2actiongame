//=============================================================================
//
// �}�l�[�W���[���� [manager.cpp]
// Author ��� ��^
//
//=============================================================================
#include "manager.h"
#include "title.h"
#include "game.h"
#include "tutorial.h"
#include"result.h"

//�ÓI�����o�ϐ�
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CInputPad *CManager::m_pInputPad = NULL;
CSound *CManager::m_pSound = NULL;
CCamera *CManager::m_pCamera = NULL;
CLight *CManager::m_pLight = NULL;
CDebugProc *CManager::m_pDebugProc = NULL;
CTexture *CManager::m_pTexture = NULL;
CModel *CManager::m_pModel = NULL;
CScene *CManager::m_pScene = NULL;

//===================================================================================================
// �V�[���̏���
//===================================================================================================
//-------------------------------------------------------
//�V�[���̃R���X�g���N�^
//-------------------------------------------------------
CScene::CScene()
{

}
//-------------------------------------------------------
//�V�[���̃f�X�g���N�^
//-------------------------------------------------------
CScene::~CScene()
{

}
//-------------------------------------------------------
//�V�[���̏���������
//-------------------------------------------------------
HRESULT CScene::Init(void)
{


	return (S_OK);
}
//-------------------------------------------------------
//�V�[���̏I������
//-------------------------------------------------------
void CScene::Uninit(void)
{
	Release();  //
}
//-------------------------------------------------------
//�V�[���̍X�V����
//-------------------------------------------------------
void CScene::Update(void)
{

}
//-------------------------------------------------------
//�V�[���̕`�揈��
//-------------------------------------------------------
void CScene::Draw(void)
{

}
//-------------------------------------------------------
//�V�[���̐���
//-------------------------------------------------------
CScene *CScene::Create(MODE mode)
{
	CScene *pScene = NULL;

	switch (mode)
	{
	case MODE_TITLE:

		pScene = new CTitle;  //�^�C�g���V�[���̐���

		break;

	case MODE_TUTORIAL:

		pScene = new CTutorial;  //�`���[�g���A���V�[���̐���

		break;

	case MODE_GAME:

		pScene = new CGame;  //�Q�[���V�[���̐���

		break;

	case MODE_RESULT:

		pScene = new CResult;  //���U���g�V�[���̐���

		break;
	}

	pScene->m_mode = mode;  //���[�h������

	if (pScene != NULL)
	{
		pScene->Init();  //����������
	}

	else
	{//�����Ɏ��s�����ꍇ
		return NULL;
	}

	return pScene;
}
//-------------------------------------------------------
//���[�h�̎擾
//-------------------------------------------------------
//CScene::MODE CScene::GetMode(void)
//{
//	//���݂̃��[�h��Ԃ�
//
//}
//-------------------------------------------------------
//�ʒu�̐ݒ菈��
//-------------------------------------------------------
void CScene::SetPosition(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//-------------------------------------------------------
//�ߋ��̈ʒu�̐ݒ菈��
//-------------------------------------------------------
void CScene::SetPositionOld(const D3DXVECTOR3 posOld)
{
	m_posOld = posOld;
}
//-------------------------------------------------------
//�ړ��ʂ̐ݒ菈��
//-------------------------------------------------------
void CScene::SetMove(const D3DXVECTOR3 move)
{
	m_move = move;
}
//-------------------------------------------------------
//�����̐ݒ菈��
//-------------------------------------------------------
void CScene::SetRotation(const D3DXVECTOR3 rot)
{
	m_rot = rot;
}
//-------------------------------------------------------
//�g�嗦�̐ݒ菈��
//-------------------------------------------------------
void CScene::SetScale(const D3DXVECTOR3 scale)
{
	m_scale = scale;
}
//-------------------------------------------------------
//�T�C�Y�̐ݒ菈��
//-------------------------------------------------------
void CScene::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}
//===================================================================================================
// �}�l�[�W���[�̏���
//===================================================================================================
//-------------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------------
CManager::CManager()
{

}
//-------------------------------------------------------
//�f�X�g���N�^
//-------------------------------------------------------
CManager::~CManager()
{

}
//-------------------------------------------------------
//����������
//-------------------------------------------------------
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	/////////////////////////////////
	//�����_���[�̐���
	/////////////////////////////////
	//m_pRenderer��NULL�̎�
	if (m_pRenderer == NULL)
	{
		//�����_���[�̃������m��
		m_pRenderer = new CRenderer;
	}

	//�����_���[�̏���������
	m_pRenderer->Init(hWnd, TRUE);

	/////////////////////////////////
	//�L�[�{�[�h�̐���
	/////////////////////////////////
	//m_pInputKeyboard��NULL�̎�
	if (m_pInputKeyboard == NULL)
	{
		//�L�[�{�[�h�̃������m��
		m_pInputKeyboard = new CInputKeyboard;
	}

	//�L�[�{�[�h�̏���������
	m_pInputKeyboard->Init(hInstance, hWnd);

	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	/////////////////////////////////
	//�Q�[���p�b�h�̐���
	/////////////////////////////////
	//m_pInputPad��NULL�̎�
	if (m_pInputPad == NULL)
	{
		//�Q�[���p�b�h�̃������m��
		m_pInputPad = new CInputPad;
	}

	//�Q�[���p�b�h�̏���������
	m_pInputPad->Init();

	//�Q�[���p�b�h�̎擾
	CInputPad *pInputPad;
	pInputPad = CManager::GetInputPad();

	/////////////////////////////////
	//�T�E���h�̐���
	/////////////////////////////////
	//m_pRenderer��NULL�̎�
	if (m_pSound == NULL)
	{
		//�T�E���h�̃������m��
		m_pSound = new CSound;
	}

	//�T�E���h�̏���������
	m_pSound->Init(hWnd);

	/////////////////////////////////
	//�J�����̐���
	/////////////////////////////////
	//m_pCamera��NULL�̎�
	if (m_pCamera == NULL)
	{
		//�J�����̃������m��
		m_pCamera = new CCamera;
	}

	//�J�����̏���������
	m_pCamera->Init();

	/////////////////////////////////
	//���C�g�̐���
	/////////////////////////////////
	//m_pLight��NULL�̎�
	if (m_pLight == NULL)
	{
		//���C�g�̃������m��
		m_pLight = new CLight;
	}

	//���C�g�̏���������
	m_pLight->Init();

	/////////////////////////////////
	//�f�o�b�O�\���̐���
	/////////////////////////////////
	//m_pDebugProc��NULL�̎�
	if (m_pDebugProc == NULL)
	{
		//�f�o�b�O�\���̃������m��
		m_pDebugProc = new CDebugProc;

		//�f�o�b�O�\���̏���������
		m_pDebugProc->Init();
	}

	/////////////////////////////////
	//�e�N�X�`���̐���
	/////////////////////////////////
	//m_pTexture��NULL�̎�
	if (m_pTexture == NULL)
	{
		//�e�N�X�`���̃������m��
		m_pTexture = new CTexture;

		//�e�N�X�`���̓ǂݍ���
		CTexture::Load();
	}

	/////////////////////////////////
	//���f���̐���
	/////////////////////////////////
	//m_pModel��NULL�̎�
	if (m_pModel == NULL)
	{
		//�e�N�X�`���̃������m��
		m_pModel = new CModel;

		//���f���̓ǂݍ���
		CModel::Load();
	}

	//���[�h�ݒ�(�^�C�g���Ɉڍs)
	SetMode(CScene::MODE_GAME);

#if _DEBUG

	//���[�h�ݒ�(�^�C�g���Ɉڍs)
	SetMode(CScene::MODE_GAME);

#endif

	return (S_OK);
}
//-------------------------------------------------------
//�I������
//-------------------------------------------------------
void CManager::Uninit(void)
{
	//�S�ẴI�u�W�F�N�g��j��
	CObject::ReleaseAll();

	//�L�[�{�[�h�̏I������
	m_pInputKeyboard->Uninit();
	m_pInputKeyboard = NULL;

	//�Q�[���p�b�h�̏I������
	m_pInputPad->Uninit();
	m_pInputPad = NULL;

	//�����_���[�̏I������
	m_pRenderer->Uninit();
	m_pRenderer = NULL;

	//�T�E���h�̏I������
	m_pSound->Uninit();
	m_pSound = NULL;

	//�J�����̏I������
	m_pCamera->Uninit();
	m_pCamera = NULL;

	//���C�g�̏I������
	m_pLight->Uninit();
	m_pLight = NULL;

	//�f�o�b�O�\���̏I������
	m_pDebugProc->Uninit();
	m_pDebugProc = NULL;

	//�e�N�X�`���̏I������
	m_pTexture->Unload();
	m_pTexture = NULL;

	//���f���̏I������
	m_pModel->Unload();
	m_pModel = NULL;
}
//-------------------------------------------------------
//�X�V����
//-------------------------------------------------------
HRESULT CManager::Update(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//�L�[�{�[�h�̍X�V����
	m_pInputKeyboard->Update();

	//�Q�[���p�b�h�̍X�V����
	m_pInputPad->Update();

	//�����_���[�̍X�V����
	m_pRenderer->Update();

	//�J�����̍X�V����
	m_pCamera->Update();

	//���C�g�̍X�V����
	m_pLight->Update();

	//�f�o�b�O�\���̍X�V����
	m_pDebugProc->Update();

	return (S_OK);
}
//-------------------------------------------------------
//�`�揈��
//-------------------------------------------------------
void CManager::Draw(void)
{
	//�����_���[�̕`�揈��
	m_pRenderer->Draw();
}
//-------------------------------------------------------
//���[�h�̐ݒ�
//-------------------------------------------------------
void CManager::SetMode(CScene::MODE mode)
{
	//���݂̃��[�h�̔j��
	if (m_pScene != NULL)
	{
		m_pScene->Uninit();

		m_pScene = NULL;  //�g�p���Ă��Ȃ���Ԃɂ���
	}

	CObject::ReleaseAll();  //�S�폜����

	//�V�������[�h�̐���
	if (m_pScene == NULL)
	{
		m_pScene = CScene::Create(mode);
	}

	//�t�F�[�h�̐���
	//if (m_pFade == NULL)
	//{
	//	m_pFade = CFade::Create(mode);
	//}	
}
//-------------------------------------------------------
//�V�[���̍X�V����
//-------------------------------------------------------
void CManager::UpdateFade(void)
{
	//�t�F�[�h�̐���
	//if (m_pFade == NULL)
	//{
	//	m_pFade->Update();
	//}
}