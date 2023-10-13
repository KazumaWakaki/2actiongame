//=============================================================================
//
//[game.h]
//Author 若木 一真
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "manager.h"

//マクロ定義
#define TIME_END	(120)	//余韻

// 前方宣言
class CScore;

//ゲームクラス
class CGame : public CScene
{
public:
	//ゲームの状態
	typedef enum
	{
		GAMESTATE_NONE = 0,    //何もしていない状態
		GAMESTATE_NORMAL,      //通常状態
		GAMESTATE_RESET,       //リセット状態
		GAMESTATE_END,         //終了状態
		GAMESTATE_MAX
	}GAMESTATE;

	CGame();   //コンストラクタ
	~CGame();  //デストラクタ

	//メンバ関数
	HRESULT Init(void);  //初期化処理
	void Uninit(void);	 //終了処理
	void Update(void);   //更新処理
	void Draw(void);	 //描画処理

	//取得
	GAMESTATE GetGameState(void) { return m_gameState; };
	//CTime *GetTime(void);

	//設定
	static void SetGameState(GAMESTATE state, int nCounter);
	void SetEnablePause(bool Pause);

private:
	GAMESTATE m_gameState;    //ゲームの状態
	int m_nCounterGameState;  //状態管理カウンター
	bool m_bPause;            //ポーズ状態のON/OFF

	//ポインタ
	static CGame *m_apObject;           //オブジェクトクラスのポインタ
	static CSound *m_pSound;			//音のポインタ
	//CTime *m_pTime;                     //タイマーのポインタ
	static CCamera *m_pCamera;			//カメラのポインタ
	static CLight *m_pLight;			//ライトのポインタ
	static CDebugProc *m_pDebugProc;	//デバッグ表示のポインタ
	static CTexture *m_pTexture;		//テクスチャのポインタ
	static CModel *m_pModel;		    //モデルのポインタ
};

#endif