//=============================================================================
//
// エフェクト処理 [effect.cpp]
// Author 若木 一真
//
//=============================================================================
#include "effect.h"
#include "manager.h"

//マクロ定義
#define EXPLOSIONAMIME (5)         //アニメーション速度
#define EXPLOSIONPATTERNAMIME (8)  //アニメーションパターン数
#define TEXSIZE_X	(20.0f)        //テクスチャのサイズX
#define TEXSIZE_Y	(20.0f)        //テクスチャのサイズY
#define TEXSIZE_Z	(20.0f)        //テクスチャのサイズZ
#define LIFE	    (20)           //寿命

//-------------------------------------------------------
//コンストラクタ
//-------------------------------------------------------
CEffect::CEffect()
{
	SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //位置の初期化
	SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));      //サイズの初期化
}
//-------------------------------------------------------
//デストラクタ
//-------------------------------------------------------
CEffect::~CEffect()
{

}
//-------------------------------------------------------
//初期化処理
//-------------------------------------------------------
HRESULT CEffect::Init()
{
	CTexture *pTexture = CManager::GetTexture();

	m_nIdxTexture = pTexture->Regist("data\\texture\\kizuato001.png");

	//サイズ初期化
	SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//オブジェクトビルボードの初期化処理
	CBillboard::Init();

	//種類の設定
	SetType(TYPE_EFFECT);

	return (S_OK);
}
//-------------------------------------------------------
//終了処理
//-------------------------------------------------------
void CEffect::Uninit()
{
	//オブジェクトビルボードの終了処理
	CBillboard::Uninit();
}
//-------------------------------------------------------
//更新処理
//-------------------------------------------------------
void CEffect::Update()
{
	D3DXVECTOR3 m_pos = GetPosition();  //位置の取得

	CBillboard::SetVtx();

	//位置の設定
	SetPosition(m_pos);

	m_nLife++;

	//弾が消えるまでのカウント
	if (m_nLife >= LIFE)
	{
		//削除処理
		Uninit();

		m_nLife = 0;  //0に戻す
	}

	//-------------------------------------------------------
	//デバック表示
	//-------------------------------------------------------
	CManager::GetDebugProc()->Print("エフェクト位置 [%f, %f, %f]\n", m_pos.x, m_pos.y, m_pos.z);
}
//-------------------------------------------------------
//描画処理
//-------------------------------------------------------
void CEffect::Draw()
{
	//オブジェクトビルボードの描画処理
	CBillboard::Draw();
}
//-------------------------------------------------------
//生成処理
//-------------------------------------------------------
CEffect *CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CEffect *pEffect;

	//エフェクトの生成
	pEffect = new CEffect;

	//pEffectがNULLじゃなかった時
	if (pEffect != NULL)
	{
		//エフェクトの初期化処理
		pEffect->Init();

		//エフェクトの位置の設定
		pEffect->SetPosition(pos);

		//エフェクトのサイズ
		pEffect->SetSize(size);

		//色の設定
		//pEffect->SetCol(col);

		//テクスチャの割り当て
		pEffect->BindTexture(pEffect->m_nIdxTexture);
	}

	else
	{//生成に失敗した場合
		return NULL;
	}

	return pEffect;
}