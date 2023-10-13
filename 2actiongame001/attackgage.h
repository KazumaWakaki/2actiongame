//=============================================================================
//
// [attackgage.h]
// Author 若木 一真
//
//=============================================================================
#ifndef _ATTACKGAGE_H_  //このマクロ定義がされなかったら
#define _ATTACKGAGE_H_  //2重インクルード防止のマクロ定義

#include "object2D.h"

class CPlayer3D;

//アタックゲージクラス
class CAttackGage : public CObject2D
{
public:
	//テクスチャタイプ種類
	typedef enum
	{
		TYPE_ATTACKGAUGE = 0,  //アタックゲージ
		TYPE_ATTACKFRAME,  //アタックゲージ枠
		TYPE_MAX
	}TEXTYPE;

	//ゲージの段階分け
	typedef enum
	{
		TYPE_GAUGE_1 = 0,  //アタックゲージ1
		TYPE_GAUGE_2,  //アタックゲージ2
		TYPE_GAUGE_3,  //アタックゲージ3
		TYPE_GAUGE_4,  //アタックゲージ4
		TYPE_GAUGE_5,  //アタックゲージ5
		TYPE_GAUGE_MAX
	}GAGETYPE;

	CAttackGage();   //コンストラクタ
	~CAttackGage();  //デストラクタ

	//メンバ関数
	HRESULT Init(void);  //初期化処理
	void Uninit(void);  //終了処理
	void Update(void);  //更新処理
	void Draw(void);  //描画処理
	static CAttackGage *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 scale, int SetTypeTex);  //アタックゲージ生成

	//取得
	int GetGage(void) { return m_Gage; };  //ゲージの段階取得

	//設定
	void SetAttackGage(int Gage);

private:
	int m_nID;  //番号
	int m_nLife;  //寿命
	int m_nIdxTexture[TYPE_MAX];  //テクスチャ
	int m_Gage;  //ゲージの段階管理
	static CAttackGage *m_apObject;  //オブジェクトクラスのポインタ
};

#endif