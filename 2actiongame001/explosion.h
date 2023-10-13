//=============================================================================
//
// [explosion.h]
// Author 若木 一真
//
//=============================================================================
#ifndef _EXPLOSION_H_  //このマクロ定義がされてなかったら
#define _EXPLOSION_H_  //2重インクルード防止のマクロを定義する

#include "billboard.h"

//爆発クラス
class CExplosion : public CBillboard
{
public:
	CExplosion();   //コンストラクタ
	~CExplosion();  //デストラクタ

	//メンバ関数
	HRESULT Init(void);                          //初期化処理
	void Uninit(void);	                         //終了処理
	void Update(void);	                         //更新処理
	void Draw(void);	                         //描画処理
	static CExplosion *Create(D3DXVECTOR3 pos);  //爆発生成

	//メンバ関数
	void Anim(void);

private:
	int m_nIdxTexture;  //テクスチャ
	int m_nCounterAnim;	//アニメーションカウンター
	int m_nPatternAnim;	//アニメーションパターンNo.
};

#endif