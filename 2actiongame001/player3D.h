//=============================================================================
//
// [player3D.h]
// Author 若木 一真
//
//=============================================================================
#ifndef _PLAYER3D_H_  //このマクロ定義がされてなかったら
#define _PLAYER3D_H_  //2重インクルード防止のマクロを定義する

#include "objectX.h"
#include "enemy3D.h"

class CBullet3D;
class CAttackGage;

//プレイヤー3Dクラス
class CPlayer3D : public CObjectX
{
public:
	//ジャンプ状態
	typedef enum
	{
		PLAYERJUMP_GROUND = 0,  //地面
		PLAYERJUMP_SKY,  //ジャンプ状態
		PLAYERJUMP_GETOFF,  //降下状態
		PLAYERJUMP_MAX
	}PLAYERJAMP;

	//攻撃状態
	typedef enum
	{
		ATTACKSTATE_NONE = 0,     //何もしていない
		ATTACKSTATE_MELEEATTACK,  //近接攻撃状態
		ATTACKSTATE_RUSHATTACK,  //突進攻撃状態
		ATTACKSTATE_MAX
	}ATTACKSTATE;

	//戦闘状態
	typedef enum
	{
		BATTLESTATE_PROXIMITY = 0,  //近接状態
		BATTLESTATE_LONG,  //遠距離状態
		BATTLESTATE_MAX
	}BATTLESTATE;

	//ワープ可能状態
	typedef enum
	{
		WARPSTATE_FALSE = 0,  //ワープ出来ない状態
		WARPSTATE_TURE,  //ワープ出来る状態
		WARPSTATE_MAX
	}WARPSTATE;

	CPlayer3D();   //コンストラクタ
	~CPlayer3D();  //デストラクタ

	//メンバ関数
	virtual HRESULT Init(void);  //初期化処理
	virtual void Uninit(void);	 //終了処理
	virtual void Update(void);  //更新処理
	virtual void Draw(void);	 //描画処理
	static CPlayer3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 size);  //生成処理
	void AttackState(void);  //攻撃状態

	//取得
	int GetLife(void) { return m_Life; };  //体力の取得
	int GetAttackGage(void) { return m_AttackGage; };  //アタックゲージの取得
	int GetAttackState(void) { return m_AttackState; };  //攻撃状態の取得
	D3DXVECTOR3 GetStartPos(void) { return m_StartPos; };  //戦闘状態の取得

	//設定
	void SetPlayerJump(PLAYERJAMP Jamp);  //ジャンプ状態の設定処理
	void SetLife(int Life);  //体力の設定
	void SetAttack(bool Attack);  //攻撃状態の設定
	void SetAttackState(ATTACKSTATE AttackState);  //戦闘状態の設定
	void SetAttackGage(int AttackGage);  //アタックゲージの設定

	//当たり判定
	static void HitPlayer(int nDamage);  //プレイヤーのヒット処理
	static bool CollisionEnemy(CEnemy3D *pEnemy);  //敵との当たり判定
	static bool CollisionBullet(CBullet3D *pBullet);  //弾との当たり判定

	static void AttackGageMove(CAttackGage *pAttackGage);  //アタックゲージ設定処理

private:
	int m_nIdxTexture;  //テクスチャ保存
	int m_nIdxMode;  //モデル割り当て
	int m_nCnt;  //インクリメントのカウント
	int m_nCntDown;  //ジャンプのカウント
	int m_nCntBullet;  //弾発射のカウント
	int m_nCntAttack;  //アタックカウント
	int m_Life;  //体力
	int m_BoostGage;  //ブーストゲージ
	int m_State;  //状態管理
	int m_nCntState;  //状態のカウント
	int m_AttackGage;  //アタックゲージ
	bool m_Attack;  //攻撃状態切り替え
	PLAYERJAMP m_jump;  //プレイヤーのジャンプ
	ATTACKSTATE m_AttackState;  //攻撃状態
	BATTLESTATE m_BattleState;  //戦闘状態
	WARPSTATE m_WarpState;  //ワープ可能状態
	D3DXVECTOR3 m_StartPos;  //スタート位置
	D3DXVECTOR3 m_vtxMin;  //最小の頂点座標
	D3DXVECTOR3 m_vtxMax;  //最大の頂点座標
	static CPlayer3D *m_apObject;  //オブジェクトクラスのポインタ
};

#endif