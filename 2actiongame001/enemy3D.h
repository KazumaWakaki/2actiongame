//=============================================================================
//
// [enemy3D.h]
// Author 若木 一真
//
//=============================================================================
#ifndef _ENEMY3D_H_  //このマクロ定義がされてなかったら
#define _ENEMY3D_H_  //2重インクルード防止のマクロを定義する

#include "objectX.h"

//マクロ定義
#define ENEMYSPEED   (3.0f)    //移動時のスピード
#define ENEMYSPEEDUP (0.15f)   //移動量更新時のスピード
#define ENEMY_COLLISION  (50)  //敵の当たり判定
#define MAX_ENEMY         (20)  //敵の最大数

class CBullet3D;
class CPlayer3D;

//敵クラス
class CEnemy3D : public CObjectX
{
public:
	//テクスチャタイプ種類
	typedef enum
	{
		TYPE_KOUMORI = 0,  //コウモリ
		TYPE_OOKAMI,           //狼
		TYPE_MAX
	}TYPE;

	//状態管理
	typedef enum
	{
		ENEMYSTATE_NORMAL = 0,     //通常状態
		ENEMYSTATE_DAMAGE,         //ダメージ状態
		ENEMYSTATE_MAX
	}ENEMYSTATE;

	//移動管理
	typedef enum
	{
		ENEMYMOVE_RIGHT = 0,  //右に移動する
		ENEMYMOVE_LEFT,       //左に移動する
		ENEMYMOVE_AUTO,       //自動で動く
		ENEMYMOVE_MAX
	}ENEMYMOVE;

	CEnemy3D();   //コンストラクタ
	~CEnemy3D();  //デストラクタ

	//メンバ関数
	HRESULT Init(void);  //初期化処理
	void Uninit(void);   //終了処理
	void Update(void);   //更新処理
	void Draw(void);	 //描画処理
	static CEnemy3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 size, int SetTypeTex, int Life);  //生成処理
	static void PlayerAttack(CPlayer3D *pPlayer);  //プレイヤー近接攻撃判定
	static void MoveEnemy(CPlayer3D *pPlayer);  //敵の移動
	void UpdateEnemyState(void);  //敵の状態
	void MoveEnemy(void);  //敵の移動

	//取得
	//int GetnID(void) { return m_nID; };  //番号の取得

	//設定
	void SetLife(int Life);  //体力の設定
	void SetEnemyState(ENEMYSTATE state, int nCounterState);  //状態の設定
	void SetEnemyMoveState(ENEMYMOVE statemove);

	//当たり判定処理
	static void HitEnemy(int nDamage, int nCnt);  //敵のヒット処理
	static bool CollisionBullet(CBullet3D *pBullet);  //弾との当たり判定
	static bool AttackCollision(CPlayer3D *pPlayer);  //突進攻撃の敵との当たり判定

private:
	int m_nIdxModel[TYPE_MAX];  //モデル割り当て
	int m_Life;  //体力
	int m_nID;  //番号
	int m_nCntHit;  //ダメージ状態のカウント
	int m_nCounterState;  //状態管理カウンター
	int m_nCounterMove;  //移動カウンター
	int m_nCounterBullet;  //弾のカウンター
	ENEMYSTATE m_state;  //状態管理
	ENEMYMOVE m_movestate;  //移動管理
	static CEnemy3D *m_apObject[MAX_ENEMY];  //オブジェクトクラスのポインタ
};

#endif