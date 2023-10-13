//=======================================================
//
// ゲーム処理 [game.cpp]
// Author 若木一真
//
//=======================================================
#include "game.h"
#include "modelset.h"
#include "player3D.h"
#include "enemy3D.h"
#include "block3D.h"
#include "wall.h"

//マクロ定義
#define WALL_MAX  (7)  //背景壁の数値
#define START_TIME	(420)	//制限時間

//静的メンバ変数
CGame *CGame::m_apObject = NULL;

//-------------------------------------------------------
//コンストラクタ
//-------------------------------------------------------
CGame::CGame()
{
	if (m_apObject == NULL)
	{
		m_apObject = this;
	}

	//m_pTime = NULL;
}
//-------------------------------------------------------
//デストラクタ
//-------------------------------------------------------
CGame::~CGame()
{

}
//-------------------------------------------------------
//ゲーム画面の初期化処理
//-------------------------------------------------------
HRESULT CGame::Init(void)
{
	//サウンドの取得
	CSound *pSound;
	pSound = CManager::GetSound();

	//シーンの初期化処理
	CScene::Init();

	//---------------------------------------------------------------
	//壁の生成
	//---------------------------------------------------------------
	for (int nCntWall = 0; nCntWall <= WALL_MAX; nCntWall++)
	{
		CWall::Create(D3DXVECTOR3(30.0f + 620.0f * nCntWall, 150.0f, 200.0f), D3DXVECTOR3(0.0f, 0, 0.0f), D3DXVECTOR3(640.0f, 360.0f, 0.0f), CWall::TYPE_HAIKEI001);
	}

	//---------------------------------------------------------------
	//ブロックの配置
	//---------------------------------------------------------------
	CBlock3D::Create(D3DXVECTOR3(1000.0f, -400.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(800.0f, 20.0f, 2.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //床
	CBlock3D::Create(D3DXVECTOR3(-770.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(20.0f, 40.0f, 2.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));      //左壁
	CBlock3D::Create(D3DXVECTOR3(-200.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 2.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));        //
	CBlock3D::Create(D3DXVECTOR3(0.0f, 200.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 2.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));        //
	CBlock3D::Create(D3DXVECTOR3(700.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(20.0f, 2.0f, 2.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));        //1個目の段差

	CBlock3D::Create(D3DXVECTOR3(1000.0f, -400.0f, -2000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(800.0f, 20.0f, 2.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //床
	CBlock3D::Create(D3DXVECTOR3(-770.0f, 0.0f, -2000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(20.0f, 40.0f, 2.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));      //左壁
	CBlock3D::Create(D3DXVECTOR3(0.0f, 120.0f, -2000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 2.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));        //
	CBlock3D::Create(D3DXVECTOR3(700.0f, 0.0f, -2000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(20.0f, 2.0f, 2.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));        //1個目の段差

	//---------------------------------------------------------------
	//モデルの生成
	//---------------------------------------------------------------
	CModelSet::Create(D3DXVECTOR3(1800.0f, 0.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.3f, 0.3f, 0.3f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelSet::TYPE_GATE_1);  //ゲート1個目
	CModelSet::Create(D3DXVECTOR3(700.0f, 40.0f, -1800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.3f, 0.3f, 0.3f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelSet::TYPE_GATE_2);  //ゲート2個目

	//---------------------------------------------------------------
	//敵3Dの生成
	//---------------------------------------------------------------
	CEnemy3D::Create(D3DXVECTOR3(400.0f, 0.0f, -5.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXVECTOR3(1.0f, 1.2f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy3D::TYPE_OOKAMI, 200);
	CEnemy3D::Create(D3DXVECTOR3(1200.0f, 0.0f, -5.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXVECTOR3(1.0f, 1.2f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy3D::TYPE_OOKAMI, 200);

	//---------------------------------------------------------------
	//プレイヤー3Dの生成
	//---------------------------------------------------------------
	CPlayer3D::Create(D3DXVECTOR3(-400.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f), D3DXVECTOR3(0.3f, 0.3f, 0.3f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//BGMの再生
	//pSound->PlaySound(SOUND_LABEL_BGM_GAME);

	return (S_OK);
}
//-------------------------------------------------------
//ゲーム画面の終了処理
//-------------------------------------------------------
void CGame::Uninit(void)
{
	//サウンドの取得
	CSound *pSound;
	pSound = CManager::GetSound();

	//BGMの再生
	pSound->StopSound();

	//シーンの終了処理
	CScene::Uninit();

	if (m_apObject != NULL)
	{
		m_apObject = NULL;
	}
}
//-------------------------------------------------------
//ゲーム画面の更新処理
//-------------------------------------------------------
void CGame::Update(void)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	if (pInputKeyboard->GetTrigger(DIK_R) == true)  //ENTERキーが押された
	{
		//モード設定(リザルトに移行)
		CManager::SetMode(MODE_RESULT);
		//CManager::GetFade()->Set(CScene::MODE_RESULT);

		////サウンドの再生
		//PlaySound(SOUND_LABEL_SE_NEXT);
	}

	switch (m_gameState)
	{
	case GAMESTATE_NORMAL:  //通常状態
		break;

	case GAMESTATE_RESET:  //リセット状態

		m_nCounterGameState++;

		if (m_nCounterGameState >= 10)
		{
			m_nCounterGameState = 0;
			m_gameState = GAMESTATE_NORMAL;  //通常状態に設定
		}

		break;

	case GAMESTATE_END:  //終了状態

		m_nCounterGameState--;

		if (m_nCounterGameState <= 0)
		{
			m_gameState = GAMESTATE_NONE;  //何もしていない状態に設定

			//モード設定(リザルトに移行)
			CManager::SetMode(MODE_RESULT);
			//CManager::GetFade()->Set(CScene::MODE_RESULT);

			////モード設定(リザルト画面に移行)
			//SetFade(MODE_RESULT);
		}

		break;
	}
}
//-------------------------------------------------------
//ゲーム画面の描画処理
//-------------------------------------------------------
void CGame::Draw(void)
{
	//シーンの描画処理
	CScene::Draw();
}
//-------------------------------------------------------
//ゲームの状態の設定
//-------------------------------------------------------
void CGame::SetGameState(GAMESTATE state, int nCounter)
{
	if (m_apObject != NULL)
	{
		m_apObject->m_gameState = state;
		m_apObject->m_nCounterGameState = nCounter;
	}
}
//-------------------------------------------------------
//ゲームのポーズ状態の取得
//-------------------------------------------------------
void CGame::SetEnablePause(bool Pause)
{
	m_bPause = Pause;
}
//-------------------------------------------------------
// タイマーの取得
//-------------------------------------------------------
//CTime *CGame::GetTime(void)
//{
//	return m_pTime;
//}