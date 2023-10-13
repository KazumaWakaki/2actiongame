//=============================================================================
//
// �J�������� [camera.cpp]
// Author ��� ��^
//
//=============================================================================
#include "camera.h"
#include "manager.h"

//�}�N����`
#define MOVE_SPEED		(3.0f)	  //�ړ��X�s�[�h
#define ROLL_SPEED		(0.03f)	  //��]�X�s�[�h
#define CAMERA_MAX_ROT (D3DX_PI * 0.99f)  //���_�̌��E�p
#define CAMERA_MIN_ROT (D3DX_PI * 0.01f)   //���_�̌��E�p

//-------------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------------
CCamera::CCamera()
{

}
//-------------------------------------------------------
//�f�X�g���N�^
//-------------------------------------------------------
CCamera::~CCamera()
{

}
//=======================================================
//�J�����̏���������
//=======================================================
HRESULT CCamera::Init(void)
{
	//���[�J���ϐ��錾
	D3DXVECTOR3 StartRot;

	//�l�̏�����
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 1.57f, 0.0f);
	fLengthX = 0.0f;       //X�ʂ̎��_���璍���_�܂ł̋���
	fLengthY = 0.0f;       //Y�ʂ̎��_���璍���_�܂ł̋���
	fLengthZ = -100.0f;  //Z�ʂ̎��_���璍���_�܂ł̋���

	//PRIORITY����
	for (int nCntPriority = 0; nCntPriority < PRIORITY; nCntPriority++)
	{
		//MAX_OBJECT����
		for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
		{
			CObject *pObj;  //�I�u�W�F�N�g�N���X�̃|�C���^

			//�I�u�W�F�N�g���擾
			pObj = CObject::GetObject(nCntPriority, nCntObj);

			//pObj��NULL����Ȃ�������
			if (pObj != NULL)
			{
				CObject::TYPE type;  //���

				//��ނ��擾
				type = pObj->GetType();

				//��ނ��v���C���[�̏ꍇ
				if (type == CObject::TYPE_PLAYER)
				{
					//�����ʒu���v���C���[�̌���ɐݒ肷��
					StartRot = -pObj->GetRotation();

					//�ڕW�ʒu�܂ňړ�����
					m_rot.x = StartRot.y + (-D3DX_PI * 0.5f);
				}
			}
		}
	}

	return (S_OK);
}
//=======================================================
//�J�����̏I������
//=======================================================
void CCamera::Uninit(void)
{

}
//=======================================================
//�J�����̍X�V����
//=======================================================
void CCamera::Update(void)
{
	CInputKeyboard *pInputKeyboard;

	//�L�[�{�[�h�̎擾
	pInputKeyboard = CManager::GetInputKeyboard();

	//�J�����Ǐ]
	MoveCamera();

	//�J�����ƒ����_�̋������Z�o
	//fLengthX = sqrtf    //X���_
	//(
	//	(m_posV.z - m_posR.z) * (m_posV.z - m_posR.z) + (m_posV.y - m_posR.y) * (m_posV.y - m_posR.y)
	//);

	//fLengthY = sqrtf    //Y���_
	//(
	//	(m_posV.x - m_posR.x) * (m_posV.x - m_posR.x) + (m_posV.z - m_posR.z) * (m_posV.z - m_posR.z)
	//);

	/////////////////////////////////
	//�ړ�
	/////////////////////////////////
	if (pInputKeyboard->GetPress(DIK_Y) == true)         //Y�L�[�������ꂽ (��ړ�)
	{
		m_posV.y += MOVE_SPEED;
	}

	if (pInputKeyboard->GetPress(DIK_N) == true)         //N�L�[�������ꂽ (���ړ�)
	{
		m_posV.y -= MOVE_SPEED;
	}

	/////////////////////////////////
	//���_��]
	/////////////////////////////////
	if (pInputKeyboard->GetPress(DIK_Q) == true)   //Q�L�[�������ꂽ  (����)
	{
		m_rot.y -= ROLL_SPEED;
	}

	if (pInputKeyboard->GetPress(DIK_E) == true)   //E�L�[�������ꂽ  (��)
	{
		m_rot.y += ROLL_SPEED;
	}

	if (pInputKeyboard->GetPress(DIK_Z) == true)   //Z�L�[�������ꂽ  (�����)
	{
		m_rot.y += ROLL_SPEED;

		m_posV.x = m_posR.x + sinf(m_rot.y) * -fLengthY;
		m_posV.z = m_posR.z + cosf(m_rot.y) * -fLengthY;
	}

	if (pInputKeyboard->GetPress(DIK_C) == true)   //C�L�[�������ꂽ  (�E���)
	{
		m_rot.y -= ROLL_SPEED;

		m_posV.x = m_posR.x + sinf(m_rot.y) * -fLengthY;
		m_posV.z = m_posR.z + cosf(m_rot.y) * -fLengthY;
	}

	//�p�x�̕␳
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI;
	}

	//�p�x�̕␳
	if (m_rot.z > CAMERA_MAX_ROT)
	{
		m_rot.z = CAMERA_MAX_ROT;
	}
	if (m_rot.z < CAMERA_MIN_ROT)
	{
		m_rot.z = CAMERA_MIN_ROT;
	}
	if (m_rot.x > D3DX_PI)
	{
		m_rot.x = -D3DX_PI;
	}
	if (m_rot.x < -D3DX_PI)
	{
		m_rot.x = D3DX_PI;
	}

	//�����_�𑊑Έʒu�ɐݒ�
	//m_posR =
	//{
	//	m_posV.x + sinf(m_rot.y) * fLengthY,
	//	m_posV.y - 20,
	//	m_posV.z + cosf(m_rot.y) * fLengthY
	//};

	//m_posR.x = m_posV.x + sinf(m_rot.y) * fLengthY;
	////m_posR.y = m_posV.y + cosf(m_rot.y) * fLengthY;
	//m_posR.z = m_posV.z + cosf(m_rot.y) * fLengthY;

	m_posV.x = m_posR.x + (sinf(m_rot.z) * cosf(m_rot.x)) * 0.0f;
	m_posV.y = m_posR.y + fLengthY;
	m_posV.z = m_posR.z + fLengthZ;

	SetPosV(m_posV);     //���_�̐ݒ�
	SetPosR(m_posR);     //�����_�̐ݒ�
	SetRotation(m_rot);  //�����̐ݒ�

	//-------------------------------------------------------
	//�J�����̃f�o�b�N�\��
	//-------------------------------------------------------
	CManager::GetDebugProc()->Print("���_ [%f, %f, %f]\n", m_posV.x, m_posV.y, m_posV.z);
	CManager::GetDebugProc()->Print("�����_ [%f, %f, %f]\n", m_posR.x, m_posR.y, m_posR.z);
	CManager::GetDebugProc()->Print("���� [%f, %f, %f]\n", m_rot.x, m_rot.y, m_rot.z);
	CManager::GetDebugProc()->Print("�J�������� [Q�AE�AZ�AC�AY�AN]\n");
}
//=======================================================
//�J�����̐ݒ菈��
//=======================================================
void CCamera::SetCamera(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxProjection);

	////�v���W�F�N�V�����}�g���b�N�X���쐬(�������e)
	//D3DXMatrixPerspectiveFovLH(&mtxProjection,
	//	D3DXToRadian(45.0f),
	//	(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
	//	1.0f,
	//	1000.0f);

	//�v���W�F�N�V�����}�g���b�N�X��ݒ�(���s���e)
	D3DXMatrixOrthoLH(&mtxProjection,
					  (float)SCREEN_WIDTH,
					  (float)SCREEN_HEIGHT,
					  1.0f,
					  1000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&mtxView,
					   &m_posV,
					   &m_posR,
					   &m_vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &mtxView);
}
//=======================================================
//�J�����̒Ǐ]����
//=======================================================
void CCamera::MoveCamera(void)
{
	//PRIORITY����
	for (int nCntPriority = 0; nCntPriority < PRIORITY; nCntPriority++)
	{
		//MAX_OBJECT����
		for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
		{
			CObject *pObj;  //�I�u�W�F�N�g�N���X�̃|�C���^

			//�I�u�W�F�N�g���擾
			pObj = CObject::GetObject(nCntPriority, nCntObj);

			//pObj��NULL����Ȃ�������
			if (pObj != NULL)
			{
				CObject::TYPE type;  //���

				//��ނ��擾
				type = pObj->GetType();

				//��ނ��v���C���[�̏ꍇ
				if (type == CObject::TYPE_PLAYER)
				{
					D3DXVECTOR3 posPlayer = pObj->GetPosition();  //�v���C���[�̈ʒu�̎擾
					D3DXVECTOR3 movePlayer = pObj->GetMove();     //�v���C���[�̈ړ��ʂ̎擾
					D3DXVECTOR3 rotPlayer = pObj->GetRotation();  //�v���C���[�̌����̎擾

					m_posR += movePlayer;

					//�����_�̖ڕW�ʒu���Z�o
					m_posRDest = D3DXVECTOR3
					(
						posPlayer.x - sinf(rotPlayer.y),
						posPlayer.y + 100.0f,
						posPlayer.z - cosf(rotPlayer.y)
					);

					//�����_��␳
					D3DXVECTOR3 RDeff = D3DXVECTOR3
					(
						m_posRDest.x - m_posR.x,
						m_posRDest.y - m_posR.y,
						m_posRDest.z - m_posR.z
					);

					//�����̕t�^
					m_posR += RDeff * 0.05f;

					//���_�����_�Ԃ̋��������߂�
					float fLength_X = sqrtf((m_posR.x * m_posR.x) + (m_posV.x * m_posV.x));
					float fLength_Y = sqrtf((m_posR.y * m_posR.y) + (m_posV.y * m_posV.y));
					float fLength_Z = sqrtf((m_posR.z * m_posR.z) + (m_posV.z * m_posV.z));

					//���_�̖ڕW�ʒu���Z�o
					m_posVDest = D3DXVECTOR3
					(
						movePlayer.x - sinf(rotPlayer.x * fLength_X),
						movePlayer.y - cosf(rotPlayer.y * fLength_Y),
						movePlayer.z - cosf(rotPlayer.z * fLength_Z)
					);

					//���_��␳
					D3DXVECTOR3 VDeff = D3DXVECTOR3
					(
						m_posVDest.x - m_posV.x,
						m_posVDest.y - m_posV.y,
						m_posVDest.z - m_posV.z
					);

					//�����̕t�^
					m_posV += VDeff * 0.01f;
				}
			}
		}
	}
}
//-------------------------------------------------------
//���_�̐ݒ菈��
//-------------------------------------------------------
void CCamera::SetPosV(const D3DXVECTOR3 posV)
{
	m_posV = posV;
}
//-------------------------------------------------------
//�����_�̐ݒ菈��
//-------------------------------------------------------
void CCamera::SetPosR(const D3DXVECTOR3 posR)
{
	m_posR = posR;
}
//-------------------------------------------------------
//������x�N�g���̐ݒ菈��
//-------------------------------------------------------
void CCamera::SetVecU(const D3DXVECTOR3 vecU)
{
	m_vecU = vecU;
}
//-------------------------------------------------------
//�����̐ݒ菈��
//-------------------------------------------------------
void CCamera::SetRotation(const D3DXVECTOR3 rot)
{
	m_rot = rot;
}