//=============================================================================
//
// 3D���f������ [objectX.cpp]
// Author ��� ��^
//
//=============================================================================
#include "objectX.h"
#include "manager.h"
#include "model.h"
#include "player3D.h"

//-------------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------------
CObjectX::CObjectX()
{
	//���f�����̃N���A
	LPD3DXMESH m_pMesh = NULL;                //���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat = NULL;           //�}�e���A���ւ̃|�C���^
	DWORD m_dwNumMat = NULL;                  //�}�e���A���̐�
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    //�ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   //�ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    //����
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //�g�嗦
	m_vtxMin = INIT_VTX_MIN;                  //�ŏ��̒��_���W
	m_vtxMax = INIT_VTX_MAX;                  //�ő�̒��_���W
}
//-------------------------------------------------------
//�f�X�g���N�^
//-------------------------------------------------------
CObjectX::~CObjectX()
{

}
//=======================================================
//���f���̏���������
//=======================================================
HRESULT CObjectX::Init(void)
{
	//CModel::Model *pModel = CManager::GetModel()->GetAddress(m_nIdxModel);

	//D3DXMATERIAL *pMat;   //�}�e���A���ւ̃|�C���^

	////�}�e���A���f�[�^�ւ̃|�C���^���擾
	//pMat = (D3DXMATERIAL*)pModel->m_pBuffMat->GetBufferPointer();

	//for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	//{
	//}

	return (S_OK);
}
//=======================================================
//���f���̏I������
//=======================================================
void CObjectX::Uninit(void)
{
	//���b�V���̔j��
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	//�}�e���A���̔j��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

	//�폜����
	Release();
}
//=======================================================
//���f���̍X�V����
//=======================================================
void CObjectX::Update(void)
{

}
//=======================================================
//���f���̕`�揈��
//=======================================================
void CObjectX::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();  //�f�o�C�X�̎擾
	D3DXMATRIX mtxScale, mtxRot, mtxTrans;                             //�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;                                               //���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;                                                //�}�e���A���f�[�^�ւ̃|�C���^

	CModel::Model *pModel = CManager::GetModel()->GetAddress(m_nIdxModel);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�g�嗦�𔽉f
	D3DXMatrixScaling(&mtxScale, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)pModel->m_pBuffMat->GetBufferPointer();
	 
	for (int nCntMat = 0; nCntMat < (int)pModel->m_dwNumMat; nCntMat++)
	{
		int m_State = GetState();

			MatCopy[nCntMat] = pMat[nCntMat];

		//�v���C���[�̏��
		switch (m_State)
		{
		case STATE_NORMAL:

			pMat[nCntMat].MatD3D;

			break;

		case STATE_DAMAGE:

			//MatCopy[nCntMat].MatD3D.Ambient = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			MatCopy[nCntMat].MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			MatCopy[nCntMat].MatD3D.Emissive = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		case STATE_DEATH:

			break;
		}

		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&MatCopy[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, CManager::GetTexture()->GetAddress(pModel->pIndxTex[nCntMat]));

		//���f��(�p�[�c)�̕`��
		pModel->m_pMesh->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}
//-------------------------------------------------------
//��������
//-------------------------------------------------------
CObjectX *CObjectX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 size, TYPE type)
{
	CObjectX *pObjectX;

	//���f���̐���
	pObjectX = new CObjectX;

	//���f���̈ʒu�̐ݒ�
	pObjectX->SetPosition(pos);

	//���f���̌����̐ݒ�
	pObjectX->SetRotation(rot);

	//���f���̊g�嗦�̐ݒ�
	pObjectX->SetScale(scale);

	//���f���̃T�C�Y�ݒ�
	pObjectX->SetSize(size);

	//����������
	pObjectX->Init();

	//���f���̊��蓖��
	pObjectX->BindModel(pObjectX->m_nIdxModel);

	return pObjectX;
}
//-------------------------------------------------------
//�ʒu�̐ݒ菈��
//-------------------------------------------------------
void CObjectX::SetPosition(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//-------------------------------------------------------
//�ߋ��̈ʒu�̐ݒ菈��
//-------------------------------------------------------
void CObjectX::SetPositionOld(const D3DXVECTOR3 posOld)
{
	m_posOld = posOld;
}
//-------------------------------------------------------
//�ړ��ʂ̐ݒ菈��
//-------------------------------------------------------
void CObjectX::SetMove(const D3DXVECTOR3 move)
{
	m_move = move;
}
//-------------------------------------------------------
//�����̐ݒ菈��
//-------------------------------------------------------
void CObjectX::SetRotation(const D3DXVECTOR3 rot)
{
	m_rot = rot;
}
//-------------------------------------------------------
//�����̐ݒ菈��
//-------------------------------------------------------
void CObjectX::SetScale(const D3DXVECTOR3 scale)
{
	m_scale = scale;
}
//-------------------------------------------------------
//�T�C�Y�̐ݒ菈��
//-------------------------------------------------------
void CObjectX::SetSize(const D3DXVECTOR3 size)
{
	m_size = size;
}
//-------------------------------------------------------
//�^�C�v�ݒ�
//-------------------------------------------------------
void CObjectX::SetType(TYPE type)
{
	m_type = type;
}
//-------------------------------------------------------
//�e�N�X�`���^�C�v�̐ݒ菈��
//-------------------------------------------------------
void CObjectX::SetTypeTex(int Type)
{
	m_typetex = Type;
}
//-------------------------------------------------------
//���f���̊��蓖��
//-------------------------------------------------------
void CObjectX::BindModel(int nIdx)
{
	m_nIdxModel = nIdx;
}
//============================================================
//���f���T�C�Y�̍쐬
//============================================================
void CObjectX::SetSizeModel(void)
{
	//�ϐ���錾
	int         nNumVtx;		//���f���̒��_��
	DWORD       dwSizeFVF;		//���f���̒��_�t�H�[�}�b�g�̃T�C�Y
	BYTE        *pVtxBuff;		//���f���̒��_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 vtx;			//���f���̒��_���W
	CModel::Model *pModel = CManager::GetModel()->GetAddress(m_nIdxModel);

	//���f���̒��_�����擾
	nNumVtx = pModel->m_pMesh->GetNumVertices();

	//���f���̒��_�t�H�[�}�b�g�̃T�C�Y���擾
	dwSizeFVF = D3DXGetFVFVertexSize(pModel->m_pMesh->GetFVF());

	//���f���̒��_�o�b�t�@�����b�N
	pModel->m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
	    //���f���̒��_���W����
		vtx = *(D3DXVECTOR3*)pVtxBuff;

		//���_���W (x) �̐ݒ�
		if (vtx.x < m_vtxMin.x)
		{ //����̒��_���W (x) ���A����̒��_���W (x) �����������ꍇ

		    //����̒��_��� (x) ����
			m_vtxMin.x = vtx.x;
		}
		else if (vtx.x > m_vtxMax.x)
		{ //����̒��_���W (x) ���A����̒��_���W (x) �����傫���ꍇ

		    //����̒��_��� (x) ����
			m_vtxMax.x = vtx.x;
		}

		// ���_���W (y) �̐ݒ�
		if (vtx.y < m_vtxMin.y)
		{ //����̒��_���W (y) ���A����̒��_���W (y) �����������ꍇ

		    //����̒��_��� (y) ����
			m_vtxMin.y = vtx.y;
		}
		else if (vtx.y > m_vtxMax.y)
		{ //����̒��_���W (y) ���A����̒��_���W (y) �����傫���ꍇ

		    //����̒��_��� (y) ����
			m_vtxMax.y = vtx.y;
		}

		// ���_���W (z) �̐ݒ�
		if (vtx.z < m_vtxMin.z)
		{ //����̒��_���W (z) ���A����̒��_���W (z) �����������ꍇ

		    //����̒��_��� (z) ����
			m_vtxMin.z = vtx.z;
		}
		else if (vtx.z > m_vtxMax.z)
		{ //����̒��_���W (z) ���A����̒��_���W (z) �����傫���ꍇ

		    //����̒��_��� (z) ����
			m_vtxMax.z = vtx.z;
		}

		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		pVtxBuff += dwSizeFVF;
	}

	//���f���̒��_�o�b�t�@���A�����b�N
	pModel->m_pMesh->UnlockVertexBuffer();

	//���f���T�C�Y�����߂�
	m_size = m_vtxMax - m_vtxMin;
}