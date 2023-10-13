//=============================================================================
//
// ビルボード処理 [billboard.cpp]
// Author 若木 一真
//
//=============================================================================
#include "billboard.h"
#include "manager.h"

//-------------------------------------------------------
//コンストラクタ
//-------------------------------------------------------
CBillboard::CBillboard()
{
	//変数のクリア
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//-------------------------------------------------------
//デストラクタ
//-------------------------------------------------------
CBillboard::~CBillboard()
{

}
//=======================================================
//ビルボードの初期化処理
//=======================================================
HRESULT CBillboard::Init(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//ビルボード情報の初期化
	//m_pos = D3DXVECTOR3(-200.0f, 0.0f, 0.0f);  //位置

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点情報の生成
	SetVtx();

	//種類の設定
	SetType(TYPE_BILLBOARD);

	return (S_OK);
}
//=======================================================
//ビルボードの終了処理
//=======================================================
void CBillboard::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// 廃棄
	Release();
}
//=======================================================
//ビルボードの更新処理
//=======================================================
void CBillboard::Update(void)
{

}
//=======================================================
//ビルボードの描画処理
//=======================================================
void CBillboard::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();  //デバイスの取得
	D3DXMATRIX mtxTrans;                                               //計算用マトリックス
	D3DXMATRIX mtxView;                                                //ビューマトリックス取得用

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//ビューマトリックスを取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ポリゴンをカメラに対して正面に向ける
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);  //逆行列を求める
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, CManager::GetTexture()->GetAddress(m_nIdxTexture));

	//ビルボードの描画  四角形
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
//-------------------------------------------------------
//生成処理
//-------------------------------------------------------
CBillboard *CBillboard::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CBillboard *pBillboard;

	//ビルボードの生成
	pBillboard = new CBillboard;

	if (pBillboard != NULL)
	{
		//初期化処理
		pBillboard->Init();

		//ビルボードの位置の設定
		pBillboard->SetPosition(pos);

		//ビルボードの向きの設定
		pBillboard->SetRotation(rot);

		//ビルボードのサイズ設定
		pBillboard->SetSize(size);
	}

	else
	{//生成に失敗した場合
		return NULL;
	}

	return pBillboard;
}
//-------------------------------------------------------
//頂点情報の生成
//-------------------------------------------------------
void CBillboard::SetVtx(void)
{
	VERTEX_3D *pVtx;  //頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-50.0f, +50.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+50.0f, +50.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-50.0f, -50.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+50.0f, -50.0f, 0.0f);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------
//頂点情報の生成(ライフ)
//-------------------------------------------------------
void CBillboard::SetVtxLife(void)
{
	VERTEX_3D *pVtx;  //頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(- m_size.x, + m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+ m_size.x, + m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(- m_size.x, - m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+ m_size.x, - m_size.y, 0.0f);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------
//テクスチャ座標設定
//-------------------------------------------------------
void CBillboard::SetVtx(const int nPatternAnim, const int nTexWidth, const int nTexHeight)
{
	VERTEX_3D *pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//頂点座標の設定
	pVtx[0].tex = D3DXVECTOR2(1.0f / nTexWidth * (float)nPatternAnim, (1.0f / nTexHeight * (float)(nPatternAnim / nTexWidth)));
	pVtx[1].tex = D3DXVECTOR2(1.0f / nTexWidth * (float)(nPatternAnim + 1), (1.0f / nTexHeight * (float)(nPatternAnim / nTexWidth)));
	pVtx[2].tex = D3DXVECTOR2(1.0f / nTexWidth * (float)nPatternAnim, (1.0f / nTexHeight * (float)(nPatternAnim / nTexWidth + 1)));
	pVtx[3].tex = D3DXVECTOR2(1.0f / nTexWidth * (float)(nPatternAnim + 1), (1.0f / nTexHeight * (float)(nPatternAnim / nTexWidth + 1)));

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------
//位置の設定処理
//-------------------------------------------------------
void CBillboard::SetPosition(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//-------------------------------------------------------
//過去の位置の設定処理
//-------------------------------------------------------
void CBillboard::SetPositionOld(const D3DXVECTOR3 posOld)
{
	m_posOld = posOld;
}
//-------------------------------------------------------
//移動量の設定処理
//-------------------------------------------------------
void CBillboard::SetMove(const D3DXVECTOR3 move)
{
	m_move = move;
}
//-------------------------------------------------------
//向きの設定処理
//-------------------------------------------------------
void CBillboard::SetRotation(const D3DXVECTOR3 rot)
{
	m_rot = rot;
}
//-------------------------------------------------------
//拡大率の設定処理
//-------------------------------------------------------
void CBillboard::SetScale(const D3DXVECTOR3 scale)
{
	m_scale = scale;
}
//-------------------------------------------------------
//サイズの設定処理
//-------------------------------------------------------
void CBillboard::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}
//-------------------------------------------------------
//テクスチャタイプの設定処理
//-------------------------------------------------------
void CBillboard::SetTypeTex(int Type)
{
	m_typetex = Type;
}
//==========================================================
//テクスチャ設定
//==========================================================
void CBillboard::BindTexture(int nIdx)
{
	m_nIdxTexture = nIdx;
}