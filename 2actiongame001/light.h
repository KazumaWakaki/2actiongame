//=============================================================================
//
// [light.h]
// Author 若木 一真
//
//=============================================================================
#ifndef _LIGHT_H_                  //このマクロ定義がされてなかったら
#define _LIGHT_H_                  //2重インクルード防止のマクロを定義する

#include "main.h"

//マクロ定義
#define MAX_LIGHT  (3)  //ライトの最大数

//レンダラークラス
class CLight
{
public:
	CLight();  //コンストラクタ
	~CLight(); //デストラクタ

	//メンバ関数
	HRESULT Init(void);  //初期化処理
	void Uninit(void);   //終了処理
	void Update(void);   //更新処理

private:
	D3DLIGHT9 m_aLight[MAX_LIGHT];  //ライト情報
	int m_nCurrentLight;
};

#endif
