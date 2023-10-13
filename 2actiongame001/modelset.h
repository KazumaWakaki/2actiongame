//=============================================================================
//
// [modelset.h]
// Author 若木 一真
//
//=============================================================================
#ifndef _MODELSET_H_  //このマクロ定義がされてなかったら
#define _MODELSET_H_  //2重インクルード防止のマクロを定義する

#include "objectX.h"
#include "model.h"

class CPlayer3D;

//モデル設定クラス
class CModelSet : public CObjectX
{
public:
	//モデルタイプ種類
	typedef enum
	{
		TYPE_GATE_1 = 0,  //ゲート1
		TYPE_GATE_2,  //ゲート2
		TYPE_GATE_3,  //ゲート3
		TYPE_KOIN,  //コイン
		TYPE_MAX
	}TYPE;

	CModelSet();   //コンストラクタ
	~CModelSet();  //デストラクタ

	//メンバ関数
	virtual HRESULT Init(void);  //初期化処理
	virtual void Uninit(void);	 //終了処理
	virtual void Update(void);  //更新処理
	virtual void Draw(void);  //描画処理
	static CModelSet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 size, int SetTypeTex);  //生成処理

	//当たり判定処理
	static bool ModelCollision(CPlayer3D *pPlayer);  //プレイヤーとの当たり判定処理

private:
	int m_nID;  //番号
	int m_nIdxTexture[TYPE_MAX];   //テクスチャ保存
	int m_nIdxModel[TYPE_MAX];     //モデル割り当て
	static CModelSet *m_apObject[MAX_MODEL];  //オブジェクトクラスのポインタ
};

#endif