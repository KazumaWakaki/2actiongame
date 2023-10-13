//=============================================================================
//
// 3Dモデル処理 [objectX.cpp]
// Author 若木 一真
//
//=============================================================================
#include "objectX.h"
#include "manager.h"
#include "model.h"
#include "player3D.h"

//-------------------------------------------------------
//コンストラクタ
//-------------------------------------------------------
CObjectX::CObjectX()
{
	//モデル情報のクリア
	LPD3DXMESH m_pMesh = NULL;                //メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER m_pBuffMat = NULL;           //マテリアルへのポインタ
	DWORD m_dwNumMat = NULL;                  //マテリアルの数
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    //位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   //移動量
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    //向き
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //拡大率
	m_vtxMin = INIT_VTX_MIN;                  //最小の頂点座標
	m_vtxMax = INIT_VTX_MAX;                  //最大の頂点座標
}
//-------------------------------------------------------
//デストラクタ
//-------------------------------------------------------
CObjectX::~CObjectX()
{

}
//=======================================================
//モデルの初期化処理
//=======================================================
HRESULT CObjectX::Init(void)
{
	//CModel::Model *pModel = CManager::GetModel()->GetAddress(m_nIdxModel);

	//D3DXMATERIAL *pMat;   //マテリアルへのポインタ

	////マテリアルデータへのポインタを取得
	//pMat = (D3DXMATERIAL*)pModel->m_pBuffMat->GetBufferPointer();

	//for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	//{
	//}

	return (S_OK);
}
//=======================================================
//モデルの終了処理
//=======================================================
void CObjectX::Uninit(void)
{
	//メッシュの破棄
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	//マテリアルの破棄
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

	//削除処理
	Release();
}
//=======================================================
//モデルの更新処理
//=======================================================
void CObjectX::Update(void)
{

}
//=======================================================
//モデルの描画処理
//=======================================================
void CObjectX::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();  //デバイスの取得
	D3DXMATRIX mtxScale, mtxRot, mtxTrans;                             //計算用マトリックス
	D3DMATERIAL9 matDef;                                               //現在のマテリアル保存用
	D3DXMATERIAL *pMat;                                                //マテリアルデータへのポインタ

	CModel::Model *pModel = CManager::GetModel()->GetAddress(m_nIdxModel);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//拡大率を反映
	D3DXMatrixScaling(&mtxScale, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)pModel->m_pBuffMat->GetBufferPointer();
	 
	for (int nCntMat = 0; nCntMat < (int)pModel->m_dwNumMat; nCntMat++)
	{
		int m_State = GetState();

			MatCopy[nCntMat] = pMat[nCntMat];

		//プレイヤーの状態
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

		//マテリアルの設定
		pDevice->SetMaterial(&MatCopy[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, CManager::GetTexture()->GetAddress(pModel->pIndxTex[nCntMat]));

		//モデル(パーツ)の描画
		pModel->m_pMesh->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}
//-------------------------------------------------------
//生成処理
//-------------------------------------------------------
CObjectX *CObjectX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 size, TYPE type)
{
	CObjectX *pObjectX;

	//モデルの生成
	pObjectX = new CObjectX;

	//モデルの位置の設定
	pObjectX->SetPosition(pos);

	//モデルの向きの設定
	pObjectX->SetRotation(rot);

	//モデルの拡大率の設定
	pObjectX->SetScale(scale);

	//モデルのサイズ設定
	pObjectX->SetSize(size);

	//初期化処理
	pObjectX->Init();

	//モデルの割り当て
	pObjectX->BindModel(pObjectX->m_nIdxModel);

	return pObjectX;
}
//-------------------------------------------------------
//位置の設定処理
//-------------------------------------------------------
void CObjectX::SetPosition(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//-------------------------------------------------------
//過去の位置の設定処理
//-------------------------------------------------------
void CObjectX::SetPositionOld(const D3DXVECTOR3 posOld)
{
	m_posOld = posOld;
}
//-------------------------------------------------------
//移動量の設定処理
//-------------------------------------------------------
void CObjectX::SetMove(const D3DXVECTOR3 move)
{
	m_move = move;
}
//-------------------------------------------------------
//向きの設定処理
//-------------------------------------------------------
void CObjectX::SetRotation(const D3DXVECTOR3 rot)
{
	m_rot = rot;
}
//-------------------------------------------------------
//向きの設定処理
//-------------------------------------------------------
void CObjectX::SetScale(const D3DXVECTOR3 scale)
{
	m_scale = scale;
}
//-------------------------------------------------------
//サイズの設定処理
//-------------------------------------------------------
void CObjectX::SetSize(const D3DXVECTOR3 size)
{
	m_size = size;
}
//-------------------------------------------------------
//タイプ設定
//-------------------------------------------------------
void CObjectX::SetType(TYPE type)
{
	m_type = type;
}
//-------------------------------------------------------
//テクスチャタイプの設定処理
//-------------------------------------------------------
void CObjectX::SetTypeTex(int Type)
{
	m_typetex = Type;
}
//-------------------------------------------------------
//モデルの割り当て
//-------------------------------------------------------
void CObjectX::BindModel(int nIdx)
{
	m_nIdxModel = nIdx;
}
//============================================================
//モデルサイズの作成
//============================================================
void CObjectX::SetSizeModel(void)
{
	//変数を宣言
	int         nNumVtx;		//モデルの頂点数
	DWORD       dwSizeFVF;		//モデルの頂点フォーマットのサイズ
	BYTE        *pVtxBuff;		//モデルの頂点バッファへのポインタ
	D3DXVECTOR3 vtx;			//モデルの頂点座標
	CModel::Model *pModel = CManager::GetModel()->GetAddress(m_nIdxModel);

	//モデルの頂点数を取得
	nNumVtx = pModel->m_pMesh->GetNumVertices();

	//モデルの頂点フォーマットのサイズを取得
	dwSizeFVF = D3DXGetFVFVertexSize(pModel->m_pMesh->GetFVF());

	//モデルの頂点バッファをロック
	pModel->m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
	    //モデルの頂点座標を代入
		vtx = *(D3DXVECTOR3*)pVtxBuff;

		//頂点座標 (x) の設定
		if (vtx.x < m_vtxMin.x)
		{ //今回の頂点座標 (x) が、現状の頂点座標 (x) よりも小さい場合

		    //今回の頂点情報 (x) を代入
			m_vtxMin.x = vtx.x;
		}
		else if (vtx.x > m_vtxMax.x)
		{ //今回の頂点座標 (x) が、現状の頂点座標 (x) よりも大きい場合

		    //今回の頂点情報 (x) を代入
			m_vtxMax.x = vtx.x;
		}

		// 頂点座標 (y) の設定
		if (vtx.y < m_vtxMin.y)
		{ //今回の頂点座標 (y) が、現状の頂点座標 (y) よりも小さい場合

		    //今回の頂点情報 (y) を代入
			m_vtxMin.y = vtx.y;
		}
		else if (vtx.y > m_vtxMax.y)
		{ //今回の頂点座標 (y) が、現状の頂点座標 (y) よりも大きい場合

		    //今回の頂点情報 (y) を代入
			m_vtxMax.y = vtx.y;
		}

		// 頂点座標 (z) の設定
		if (vtx.z < m_vtxMin.z)
		{ //今回の頂点座標 (z) が、現状の頂点座標 (z) よりも小さい場合

		    //今回の頂点情報 (z) を代入
			m_vtxMin.z = vtx.z;
		}
		else if (vtx.z > m_vtxMax.z)
		{ //今回の頂点座標 (z) が、現状の頂点座標 (z) よりも大きい場合

		    //今回の頂点情報 (z) を代入
			m_vtxMax.z = vtx.z;
		}

		//頂点フォーマットのサイズ分ポインタを進める
		pVtxBuff += dwSizeFVF;
	}

	//モデルの頂点バッファをアンロック
	pModel->m_pMesh->UnlockVertexBuffer();

	//モデルサイズを求める
	m_size = m_vtxMax - m_vtxMin;
}