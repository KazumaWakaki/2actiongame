//=============================================================================
//
// [object.h]
// Author 若木 一真
//
//=============================================================================
#ifndef _OBJECT_H_  //このマクロ定義がされてなかったら
#define _OBJECT_H_  //2重インクルード防止のマクロを定義する

#include "main.h"

//マクロ定義
#define MAX_OBJECT  (4096)  //オブジェクトの数
#define PRIORITY       (8)  //オブジェクトの数

//オブジェクトクラス
class CObject
{
public:

	//タイプ種類
	typedef enum
	{
		TYPE_NONE = 0,   //なし
		TYPE_PLAYER,     //プレイヤー
		TYPE_ENEMY,	     //敵
		TYPE_BG,         //背景
		TYPE_BULLET,     //弾
		TYPE_EXPLOSION,  //爆発
		TYPE_EFFECT,     //エフェクト
		TYPE_BLOCK,      //ブロック
		TYPE_ITEM,       //アイテム
		TYPE_BILLBOARD,  //ビルボード
		TYPE_MODEL,      //モデル
		TYPE_LIFE,       //ライフ
		TYPE_ATTACKGAGE,  //アタックゲージ
		TYPE_MAX
	}TYPE;

	//状態管理
	typedef enum
	{
		STATE_APPEAR = 0,     //出現状態(点滅)
		STATE_NORMAL,         //通常状態
		STATE_DAMAGE,         //ダメージ状態
		STATE_WAIT,           //出現待ち
		STATE_DEATH,          //死亡状態
		STATE_MAX
	}STATE;

	CObject(int nPriority = 3);                      //コンストラクタ
	virtual ~CObject();                              //デストラクタ

	//純粋仮想関数
	virtual HRESULT Init(void) = 0;                  //初期化処理
	virtual void Uninit(void) = 0;	                 //終了処理
	virtual void Update(void) = 0;	                 //更新処理
	virtual void Draw(void) = 0;	                 //描画処理

	//設定(仮想関数)
	virtual void SetPosition(D3DXVECTOR3 pos) = 0;        //位置の設定
	virtual void SetPositionOld(D3DXVECTOR3 posOld) = 0;  //過去の位置の設定
	virtual void SetMove(D3DXVECTOR3 move) = 0;           //移動量の設定
	virtual void SetRotation(D3DXVECTOR3 rot) = 0;        //向きの設定
	virtual void SetScale(D3DXVECTOR3 scale) = 0;         //拡大率の設定処理
	virtual void SetSize(D3DXVECTOR3 size) = 0;           //サイズの設定

	//取得(仮想関数)
	virtual D3DXVECTOR3 GetPosition(void) = 0;     //位置の取得
	virtual D3DXVECTOR3 GetPositionOld(void) = 0;  //過去の位置の取得
	virtual D3DXVECTOR3 GetMove(void) = 0;         //移動量の取得
	virtual D3DXVECTOR3 GetRotation(void) = 0;     //向きの取得
	virtual D3DXVECTOR3 GetScale(void) = 0;        //拡大率の取得
	virtual D3DXVECTOR3 GetSize(void) = 0;         //サイズの取得

	//メンバ変数
	static void ReleaseAll(void);  //全削除処理
	static void UpdateAll(void);   //全更新処理
	static void DrawAll(void);	   //全描画処理

	//取得
	TYPE GetType(void) { return m_type; };  //タイプ取得
	static CObject *GetObject(int nPriority, int nIdx);  //オブジェクト取得
	STATE GetState(void) { return m_state; };  //状態の取得

	//設定
	void SetType(const TYPE type);  //タイプ設定
	void SetState(const STATE state, int nCounterState);  //状態管理設定
	void UpdateState(void);  //状態更新

protected:
	D3DXVECTOR3 pos;
	void Release(void);

private:
	static CObject *m_apObject[PRIORITY][MAX_OBJECT];  //オブジェクトクラスのポインタ
	static int m_nNumAll;                              //オブジェクト総数
	int m_nlD;                                         //自分自身のID
	int m_nPriority;                                   //優先順位の位置
	int m_nCounterState;                               //状態管理カウンター
	TYPE m_type;                                       //タイプ種類
	STATE m_state;                                     //状態管理
};

#endif 