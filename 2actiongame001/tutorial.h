//=============================================================================
//
// [tutorial.h]
// Author 若木 一真
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "manager.h"

//タイトルクラス
class CTutorial : public CScene
{
public:
	CTutorial();   //コンストラクタ
	~CTutorial();  //デストラクタ

	//メンバ関数
	HRESULT Init(void);  //初期化処理
	void Uninit(void);	 //終了処理
	void Update(void);   //更新処理
	void Draw(void);	 //描画処理

private:

};

#endif