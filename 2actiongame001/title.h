//=============================================================================
//
// [title.h]
// Author 若木 一真
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "manager.h"

//タイトルクラス
class CTitle : public CScene
{
public:
	//ポーズメニュー
	typedef enum
	{
		TITLE_START = 0,   //スタート
		TITLE_EXIT,        //やめる
		TITLE_MAX
	}TITLE_SELECT;

	CTitle();   //コンストラクタ
	~CTitle();  //デストラクタ

	//メンバ関数
	HRESULT Init(void);  //初期化処理
	void Uninit(void);	 //終了処理
	void Update(void);   //更新処理
	void Draw(void);	 //描画処理

private:
	int m_TitleSelect;                                          //タイトルセレクト
	int m_TitleCounter;                                         //ゲーム名の点灯タイミング
	//int m_typetex;                                              //テクスチャタイプ
	//int m_nIdxTexture;											//テクスチャ割り当て
};

#endif