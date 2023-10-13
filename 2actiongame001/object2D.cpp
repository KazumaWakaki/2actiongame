//=============================================================================
//
// 2Dオブジェクト生成処理 [object2D.cpp]
// Author 若木 一真
//
//=============================================================================
#include "object2D.h"
#include "manager.h"

//マクロ定義
#define AMIMEMAX        (8)  //アニメーション速度
#define POSITION_X (130.0f)  //頂点座標X
#define POSITION_Y (100.0f)  //頂点座標Y

//-------------------------------------------------------
//コンストラクタ
//-------------------------------------------------------
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
	//変数のクリア
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
}
//-------------------------------------------------------
//デストラクタ
//-------------------------------------------------------
CObject2D::~CObject2D()
{

}
//-------------------------------------------------------
//初期化処理
//-------------------------------------------------------
HRESULT CObject2D::Init()
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	CTexture *pTexture = CManager::GetTexture();

	m_nIdxTexture[TYPE_TITLE] = pTexture->Regist("data\\texture\\impact’Ninja.jpg");
	m_nIdxTexture[TYPE_TUTORIAL] = pTexture->Regist("data\\texture\\tutorial001.jpg");
	m_nIdxTexture[TYPE_RESULT] = pTexture->Regist("data\\texture\\result002.jpg");
	m_nIdxTexture[TYPE_ENTER] = pTexture->Regist("data\\texture\\Result002.png");
	m_nIdxTexture[TYPE_NUMBER] = pTexture->Regist("data\\texture\\nunber001.png");

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
	                            D3DUSAGE_WRITEONLY,
	                            FVF_VERTEX_2D,
	                            D3DPOOL_MANAGED,
	                            &m_pVtxBuff,
	                            NULL);

	//生成に失敗した場合
	if (m_pVtxBuff == NULL)
	{
		return E_FAIL;
	}

	//頂点情報設定
	SetVtx();

	return (S_OK);
}
//-------------------------------------------------------
//終了処理
//-------------------------------------------------------
void CObject2D::Uninit()
{
	//頂上バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//削除処理
	Release();
}
//-------------------------------------------------------
//更新処理
//-------------------------------------------------------
void CObject2D::Update()
{
	//頂点情報設定
	SetVtx();
}
//-------------------------------------------------------
//描画処理
//-------------------------------------------------------
void CObject2D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, CManager::GetTexture()->GetAddress(m_nIdxTexture[GetTypeTex()]));

	//オブジェクトの描画  四角形
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,  //プリミティブの種類
	                       0,
	                       2);                   //頂点情報構造体のサイズ
}
//-------------------------------------------------------
//描画処理(エフェクト)
//-------------------------------------------------------
void CObject2D::DrawEffect()
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));


	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, CManager::GetTexture()->GetAddress(m_nIdxTexture[GetTypeTex()]));

	//αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//オブジェクトの描画  四角形
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,  //プリミティブの種類
		0,
		2);  //頂点情報構造体のサイズ}

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
//-------------------------------------------------------
//生成処理
//-------------------------------------------------------
CObject2D *CObject2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int SetTypeTex)
{
	CObject2D *pObject2D = NULL;

	//オブジェクト2Dの生成
	pObject2D = new CObject2D;

	//pObject2DがNULLじゃない時
	if (pObject2D != NULL)
	{
		//初期化処理
		pObject2D->Init();
	}

	else
	{//生成に失敗した場合
		return NULL;
	}

	//位置の設定
	pObject2D->SetPosition(pos);

	//向きの設定
	pObject2D->SetRotation(rot);

	//サイズ設定
	pObject2D->SetSize(size);

	//オブジェクト2Dのテクスチャタイプ
	pObject2D->SetTypeTex(SetTypeTex);

	//nCount分回す
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		//nCountと選択されたテクスチャタイプが一致した時
		if (nCount == SetTypeTex)
		{
			//テクスチャの割り当て
			pObject2D->BindTexture(pObject2D->m_nIdxTexture[nCount]);
		}
	}

	return pObject2D;
}
//-------------------------------------------------------
//頂点情報の生成
//-------------------------------------------------------
void CObject2D::SetVtx(void)
{
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------
//頂点情報の生成
//-------------------------------------------------------
void CObject2D::SetVtxUI(void)
{
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_scale.x, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_scale.x, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------
//頂点情報の生成(背景)
//-------------------------------------------------------
void CObject2D::SetVtxBG(float g_aTexV, float g_aTexU)
{
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(g_aTexU, g_aTexV);
	pVtx[1].tex = D3DXVECTOR2(g_aTexU + 1.0f, g_aTexV);
	pVtx[2].tex = D3DXVECTOR2(g_aTexU, g_aTexV + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(g_aTexU + 1.0f, g_aTexV + 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------
//頂点情報の生成(エフェクト)
//-------------------------------------------------------
void CObject2D::SetVtxEffect(void)
{
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f );
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f );
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f );
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f );

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------
//頂点情報の生成(アニメーション)
//-------------------------------------------------------
void CObject2D::SetVtx(const int nPatternAnim, const int nTexWidth, const int nTexHeight)
{
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].tex = D3DXVECTOR2(1.0f / nTexWidth * (float)nPatternAnim, (1.0f / nTexHeight * (float)(nPatternAnim / nTexWidth)));
	pVtx[1].tex = D3DXVECTOR2(1.0f / nTexWidth * (float)(nPatternAnim + 1), (1.0f / nTexHeight * (float)(nPatternAnim / nTexWidth)));
	pVtx[2].tex = D3DXVECTOR2(1.0f / nTexWidth * (float)nPatternAnim, (1.0f / nTexHeight * (float)(nPatternAnim / nTexWidth + 1)));
	pVtx[3].tex = D3DXVECTOR2(1.0f / nTexWidth * (float)(nPatternAnim + 1), (1.0f / nTexHeight * (float)(nPatternAnim / nTexWidth + 1)));

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------
//頂点情報の生成
//-------------------------------------------------------
void CObject2D::SetVtxLife(int posR)
{
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(posR + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(posR + m_size.x, m_pos.y + m_size.y, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------
//位置の設定処理
//-------------------------------------------------------
void CObject2D::SetPosition(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//-------------------------------------------------------
//過去の位置の設定処理
//-------------------------------------------------------
void CObject2D::SetPositionOld(const D3DXVECTOR3 posOld)
{
	m_posOld = posOld;
}
//-------------------------------------------------------
//移動量の設定処理
//-------------------------------------------------------
void CObject2D::SetMove(const D3DXVECTOR3 move)
{
	m_move = move;
}
//-------------------------------------------------------
//向きの設定処理
//-------------------------------------------------------
void CObject2D::SetRotation(const D3DXVECTOR3 rot)
{
	m_rot = rot;
}
//-------------------------------------------------------
//拡大率の設定処理
//-------------------------------------------------------
void CObject2D::SetScale(const D3DXVECTOR3 scale)
{
	m_scale = scale;
}
//-------------------------------------------------------
//サイズの設定処理
//-------------------------------------------------------
void CObject2D::SetSize(const D3DXVECTOR3 size)
{
	m_size = size;
}
//-------------------------------------------------------
//テクスチャタイプの設定処理
//-------------------------------------------------------
void CObject2D::SetTypeTex(int Type)
{
	m_typetex = Type;
}
//-------------------------------------------------------
//頂点情報の色変更
//-------------------------------------------------------
void CObject2D::SetCol(const D3DXCOLOR col)
{
	VERTEX_2D *pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点カラーの設定
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------
//テクスチャの割り当て
//-------------------------------------------------------
void CObject2D::BindTexture(int nIdx)
{
	m_nIdxTexture[GetTypeTex()] = nIdx;
}