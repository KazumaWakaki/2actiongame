//=======================================================
//
// チュートリアル処理
// Author 若木一真
//
//=======================================================
#include "tutorial.h"
#include "object2D.h"

//マクロ定義
#define MAX_TEX	 (2)   //使用するテクスチャ数

//-------------------------------------------------------
//コンストラクタ
//-------------------------------------------------------
CTutorial::CTutorial()
{

}
//-------------------------------------------------------
//デストラクタ
//-------------------------------------------------------
CTutorial::~CTutorial()
{

}
//-------------------------------------------------------
//タイトルの初期化処理
//-------------------------------------------------------
HRESULT CTutorial::Init(void)
{
	//オブジェクト2Dの生成処理
	CObject2D::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(640.0f, 360.0f, 0.0f), CObject2D::TYPE_TUTORIAL);

	return S_OK;
}
//-------------------------------------------------------
//タイトルの終了処理
//-------------------------------------------------------
void CTutorial::Uninit(void)
{
	//サウンドの取得
	CSound *pSound;
	pSound = CManager::GetSound();

	//BGMの再生
	pSound->StopSound();

	//シーンの終了処理
	CScene::Uninit();
}
//-------------------------------------------------------
//タイトル画面の更新処理
//-------------------------------------------------------
void CTutorial::Update(void)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//ゲームパッドの取得
	CInputPad *pInputPad;
	pInputPad = CManager::GetInputPad();

	//サウンドの取得
	CSound *pSound;
	pSound = CManager::GetSound();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputPad->GetTrigger(CInputPad::BUTTON_A, 0))
	{
		//モード設定(ゲームに移行)
		CManager::SetMode(MODE_GAME);

		//SEの再生
		//pSound->PlaySound(SOUND_LABEL_SE_DECISION);
	}
}
//-------------------------------------------------------
//タイトル画面の描画処理
//-------------------------------------------------------
void CTutorial::Draw(void)
{
	//シーンの描画処理
	CScene::Draw();
}