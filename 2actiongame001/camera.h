//=============================================================================
//
// [camera.h]
// Author ��� ��^
//
//=============================================================================
#ifndef _CAMERA_H_  //���̃}�N����`������ĂȂ�������
#define _CAMERA_H_  //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"

class CObject3D;

//�����_���[�N���X
class CCamera
{
public:
	CCamera();  //�R���X�g���N�^
	~CCamera(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);                //����������
	void Uninit(void);                 //�I������
	void Update(void);                 //�X�V����
	void SetCamera(void);              //�ݒ菈��
	
	//�ݒ�
	void SetPosV(D3DXVECTOR3 posV);     //���_�̐ݒ菈��
	void SetPosR(D3DXVECTOR3 posR);     //�����_�̐ݒ菈��
	void SetVecU(D3DXVECTOR3 vecU);     //������x�N�g���̐ݒ菈��
	void SetRotation(D3DXVECTOR3 rot);  //�����̐ݒ菈��

	//�擾
	D3DXVECTOR3 GetCameraPos(void) { return m_posV; }  //�J�����ʒu(�f�o�b�O)
	D3DXVECTOR3 GetCameraRot(void) { return m_rot; }   //�J�����p�x�̎擾

private:
	//�ϐ�
	D3DXMATRIX mtxView;              //�r���[�}�g���b�N�X
	D3DXMATRIX mtxProjection;        //�v���W�F�N�V�����}�g���b�N�X
	D3DXVECTOR3 m_posV;              //���_
	D3DXVECTOR3 m_posR;              //�����_
	D3DXVECTOR3 m_vecU;              //������x�N�g��
	D3DXVECTOR3 m_rot;               //����
	D3DXVECTOR3 m_posVDest;          //�ړI�̎��_
	D3DXVECTOR3 m_posRDest;          //�ړI�̒����_
	LPDIRECT3D9 m_pD3D;              //Direct3D�I�u�W�F�N�g�̐���
	LPDIRECT3DDEVICE9 m_pD3DDevice;  //�f�o�C�X�̐錾
	float fLengthX;                  //X�ʂ̎��_���璍���_�܂ł̋���
	float fLengthY;                  //Y�ʂ̎��_���璍���_�܂ł̋���
	float fLengthZ;                  //Z�ʂ̎��_���璍���_�܂ł̋���
	float m_fLengthCamera;           //�Ίp���̒���
	float m_fAngleCamera;            //�Ίp���̊p�x

	//�֐�
	void MoveCamera(void);  //�Ǐ]����

};

#endif