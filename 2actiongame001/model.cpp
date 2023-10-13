//=============================================================================
//
// モデル管理 [model.cpp]
// Author 若木 一真
//
//=============================================================================
#include "model.h"
#include "manager.h"
#include "renderer.h"

//静的メンバ変数
CModel::Model CModel::m_apModel[MAX_MODEL] = {};
char CModel::m_FileName[MAX_MODEL][512] = {};
int  CModel::m_nNumAll = 0;

//-------------------------------------------------------
//コンストラクタ
//-------------------------------------------------------
CModel::CModel()
{

}
//-------------------------------------------------------
//デストラクタ
//-------------------------------------------------------
CModel::~CModel()
{

}
//-------------------------------------------------------
//全てのモデルの読み込み
//-------------------------------------------------------
HRESULT CModel::Load(void)
{
	return (S_OK);
}
//-------------------------------------------------------
//全てのモデルの破棄
//-------------------------------------------------------
void CModel::Unload(void)
{
	//MAX_MODEL分回す
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		//メッシュの破棄
		if (m_apModel[nCntModel].m_pMesh != NULL)
		{
			m_apModel[nCntModel].m_pMesh->Release();
			m_apModel[nCntModel].m_pMesh = NULL;
		}

		//マテリアルの破棄
		if (m_apModel[nCntModel].m_pBuffMat != NULL)
		{
			m_apModel[nCntModel].m_pBuffMat->Release();
			m_apModel[nCntModel].m_pBuffMat = NULL;
		}
	}
}
//-------------------------------------------------------
//モデルを設定する
//-------------------------------------------------------
int CModel::Regist(const char *pFilename)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	int nIdx;

	nIdx = m_nNumAll + 1;  //保存

						   //m_nNumAll分回す
	for (int nCntModel = 0; nCntModel < m_nNumAll; nCntModel++)
	{
		if (strcmp(&m_FileName[nCntModel][0], pFilename) == 0)
		{
			nIdx = nCntModel;

			return nIdx;
		}
	}

	//Xファイルの読み込み
	D3DXLoadMeshFromX(pFilename,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_apModel[nIdx].m_pBuffMat,
		NULL,
		&m_apModel[nIdx].m_dwNumMat,
		&m_apModel[nIdx].m_pMesh);

	CTexture *pTexture = CManager::GetTexture();

	D3DXMATERIAL *pMat;  //マテリアルへのポインタ

	m_apModel[nIdx].pIndxTex = new int[(int)m_apModel[nIdx].m_dwNumMat];

	//マテリアル情報に対するポインタを取得
	pMat = (D3DXMATERIAL*)m_apModel[nIdx].m_pBuffMat->GetBufferPointer();

	//マテリアルの分だけ回す
	for (int nCntMat = 0; nCntMat < (int)m_apModel[nIdx].m_dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//テクスチャを保存する
			m_apModel[nIdx].pIndxTex[nCntMat] = pTexture->Regist(pMat[nCntMat].pTextureFilename);
		}
		else
		{
			m_apModel[nIdx].pIndxTex[nCntMat] = -1;
		}
	}

	strcpy(&m_FileName[nIdx][0], pFilename);

	m_nNumAll++;

	return nIdx;
}
//-------------------------------------------------------
//アドレスを返す
//-------------------------------------------------------
CModel::Model *CModel::GetAddress(int nIdx)
{
	return &m_apModel[nIdx];
}