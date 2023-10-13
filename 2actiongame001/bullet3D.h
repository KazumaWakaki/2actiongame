//=============================================================================
//
//[bullet3D.h]
//Author 若木 一真
//
//=============================================================================
#ifndef _BULLET3D_H_  //このマクロ定義がされてなかったら
#define _BULLET3D_H_  //2重インクルード防止のマクロを定義する

#include "objectX.h"
#include "player3D.h"

//マクロ定義
#define MAX_BULLET	    (128)  //弾の最大数

//前方宣言
class CPlayer3D;

//弾クラス
class CBullet3D : public CObjectX
{
public:
	//弾の種類
	typedef enum
	{
		BULLETTYPE_PLAYER = 0,  //プレイヤー
		BULLETTYPE_ENEMY,       //敵
		BULLETTYPE_MAX
	}BULLETTYPE;

	CBullet3D();   //コンストラクタ
	~CBullet3D();  //デストラクタ

	//メンバ関数
	HRESULT Init(void);  //初期化処理
	void Uninit(void);	 //終了処理
	void Update(void);	 //更新処理
	void Draw(void);	 //描画処理
	static CBullet3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR3 scale, int type);  //弾生成

	//取得
	int GetBulletType(void) { return m_type; };  //弾の種類の取得

	//設定
	void SetTypeBullet(int Type);  //弾の種類タイプの設定

private:
	//メンバ関数
	bool CollisionBlock(D3DXVECTOR3 pos);   //ブロックとの当たり判定

	//メンバ関数
	D3DXVECTOR3 m_move;  //移動量
	int m_nLife;	     //寿命
	int m_nIdxModel[BULLETTYPE_MAX];     //モデル割り当て
	int m_type;          //弾のタイプ
	int m_nID;           //番号
	int m_nCntHit;         //ダメージ状態のカウント
	static CBullet3D *m_apObject[MAX_BULLET];  //オブジェクトクラスのポインタ
};

#endif