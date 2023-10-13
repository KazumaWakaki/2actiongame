//=============================================================================
//
// [result.h]
// Author 若木 一真
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "manager.h"

//マクロ定義
#define MAX_TEX	 (4)	    //使用するテクスチャ数
#define RES_SCO	 (1)	    //リザルトに数値を描画する回数
#define RES_TIME (600)		//ランキング画面に遷移する時間

//リザルトクラス
class CResult : public CScene
{
public:
	//ポーズメニュー
	typedef enum
	{
		RETRY_MENU_QUIT = 0,   //タイトルにいく
		RETRY_MENU_RETRY,      //ゲームをやり直す
		RETRY_MENU_MAX
	}RETRY_MENU;

	//構造体を定義
	typedef struct
	{
		D3DXVECTOR3 pos;  //位置
		int nScore;		  //値
		int nDigit;		  //桁
		int nSpace;		  //間
		int nWidth;		  //横幅
		int nHeight;	  //縦幅
		int nTexture;	  //テクスチャ
	}Result;

	CResult();   //コンストラクタ
	~CResult();  //デストラクタ

	//メンバ関数
	HRESULT Init(void);  //初期化処理
	void Uninit(void);	 //終了処理
	void Update(void);   //更新処理
	void Draw(void);	 //描画処理

private:
	Result m_aResult[RES_SCO];	//リザルトの情報
	int m_nResultCounter;		//ランキングに遷移するタイミングカウンター
	int m_nTotalScore;			//トータルスコア
	int m_RetryMenu;            //リトライメニュー
};

#endif