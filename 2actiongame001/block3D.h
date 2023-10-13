//=============================================================================
//
//[block3D.h]
//Author 若木 一真
//
//=============================================================================
#ifndef _BLOCK3D_H_  //このマクロ定義がされてなかったら
#define _BLOCK3D_H_  //2重インクルード防止のマクロを定義する

#include "objectX.h"

//マクロ定義
#define BLOCKSPEED   (3.0f)    //移動時のスピード
#define BLOCKSPEEDUP (0.15f)   //移動量更新時のスピード
#define MAX_BLOCK (128)   //ブロックの最大数

class CPlayer3D;
class CEnemy3D;

//ブロック3Dクラス
class CBlock3D : public CObjectX
{
public:
	CBlock3D();   //コンストラクタ
	~CBlock3D();  //デストラクタ

	//メンバ関数
	virtual HRESULT Init(void);                                                   //初期化処理
	virtual void Uninit(void);	                                                  //終了処理
	virtual void Update(void);	                                                  //更新処理
	virtual void Draw(void);	                                                  //描画処理
	static CBlock3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 size);  //生成処理

	//当たり判定
	static bool CollisionPlayer(CPlayer3D *pPlayer);  //プレイヤーとの当たり判定
	static bool CollisionEnemy(CEnemy3D *pEnemy);   //敵との当たり判定

private:
	int m_nID;  //番号
	int m_nIdxTexture;   //テクスチャ保存
	int m_nIdxModel;     //モデル割り当て
	static CBlock3D *m_apObject[MAX_BLOCK];  //オブジェクトクラスのポインタ
};

#endif