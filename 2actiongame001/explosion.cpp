//=============================================================================
//
// 爆発処理 [explosion.cpp]
// Author 若木 一真
//
//=============================================================================
#include "explosion.h"
#include "manager.h"

//マクロ定義
#define ANIMTIMER		(4)      //アニメーション速度
#define MAX_ANIMPATTERN	(8)	     //アニメーションの最大パターン数
#define MAX_HEIFGHTPATTERN	(8)  //アニメーションの最大横パターン数

//-------------------------------------------------------
//コンストラクタ
//-------------------------------------------------------
CExplosion::CExplosion()
{
	SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //位置の初期化
	SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));      //サイズの初期化
}
//-------------------------------------------------------
//デストラクタ
//-------------------------------------------------------
CExplosion::~CExplosion()
{

}
//-------------------------------------------------------
//初期化処理
//-------------------------------------------------------
HRESULT CExplosion::Init()
{
	CTexture *pTexture = CManager::GetTexture();

	m_nIdxTexture = pTexture->Regist("data\\texture\\explosion000.png");

	SetSize(D3DXVECTOR3(10.0f, 10.0f, 10.0f));

	//オブジェクトビルボードの初期化処理
	CBillboard::Init();

	return (S_OK);
}
//-------------------------------------------------------
//終了処理
//-------------------------------------------------------
void CExplosion::Uninit()
{
	//オブジェクトビルボードの終了処理
	CBillboard::Uninit();
}
//-------------------------------------------------------
//更新処理
//-------------------------------------------------------
void CExplosion::Update()
{
	//頂点情報設定
	SetVtx(m_nPatternAnim, MAX_HEIFGHTPATTERN, MAX_ANIMPATTERN / MAX_HEIFGHTPATTERN);

	//アニメーション処理
	Anim();
}
//-------------------------------------------------------
//描画処理
//-------------------------------------------------------
void CExplosion::Draw()
{
	//オブジェクトビルボードの描画(アニメーション)処理
	CBillboard::Draw();
}
//-------------------------------------------------------
//生成処理
//-------------------------------------------------------
CExplosion *CExplosion::Create(D3DXVECTOR3 pos)
{
	CExplosion *pExplosion = NULL;

	//爆発の生成
	pExplosion = new CExplosion;

	if (pExplosion != NULL)
	{
		//初期化処理
		pExplosion->Init();

		//種類の設定
		pExplosion->SetType(TYPE_EXPLOSION);

		//爆発の位置の設定
		pExplosion->SetPosition(pos);

		//テクスチャ設定
		pExplosion->SetVtx(pExplosion->m_nPatternAnim, MAX_HEIFGHTPATTERN, MAX_ANIMPATTERN / MAX_HEIFGHTPATTERN);

		//テクスチャの割り当て
		pExplosion->BindTexture(pExplosion->m_nIdxTexture);
	}

	else
	{//生成に失敗した場合
		return NULL;
	}

	return pExplosion;
}
//-------------------------------------------------------
//7操作処理
//-------------------------------------------------------
void CExplosion::Anim(void)
{
	m_nCounterAnim++;  //カウンターを加算

	//アニメーションタイマーの値を超えた場合
	if (m_nCounterAnim % ANIMTIMER == 0)
	{

		m_nCounterAnim = 0;

		m_nPatternAnim++;  //パターンNo.を更新

		//最後までアニメーションした場合
		if (m_nPatternAnim >= MAX_ANIMPATTERN)
		{
			Uninit();
		}
	}
}
