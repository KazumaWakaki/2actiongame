//=======================================================
//
// リザルト処理
// Author 若木一真
//
//=======================================================
#include "result.h"
#include "object2D.h"

//-------------------------------------------------------
//コンストラクタ
//-------------------------------------------------------
CResult::CResult()
{

}
//-------------------------------------------------------
//デストラクタ
//-------------------------------------------------------
CResult::~CResult()
{

}
//-------------------------------------------------------
//リザルト画面の初期化処理
//-------------------------------------------------------
HRESULT CResult::Init(void)
{
	//サウンドの取得
	CSound *pSound;
	pSound = CManager::GetSound();

	m_RetryMenu = RETRY_MENU_QUIT;   //ポーズメニュー

	//オブジェクト2Dの生成処理
	CObject2D::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(640.0f, 360.0, 0.0f), CObject2D::TYPE_RESULT);

	//BGMの再生
	//pSound->PlaySound(SOUND_LABEL_BGM_RESULT);

	return S_OK;
}
//-------------------------------------------------------
//リザルトの終了処理
//-------------------------------------------------------
void CResult::Uninit(void)
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
//リザルトの更新処理
//-------------------------------------------------------
void CResult::Update(void)
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

	//Dを押したとき
	if (pInputKeyboard->GetTrigger(DIK_D) == true)
	{
		m_RetryMenu = (m_RetryMenu + 1) % 2;

		//サウンドの再生
		//PlaySound(SOUND_LABEL_SE_SELECT);
	}

	//Aを押したとき
	if (pInputKeyboard->GetTrigger(DIK_A) == true)
	{
		m_RetryMenu = (m_RetryMenu + 1) % 2;

		//サウンドの再生
		//PlaySound(SOUND_LABEL_SE_SELECT);
	}

	if (m_RetryMenu == RETRY_MENU_QUIT)
	{
		//頂点カラーの設定
		//pVtx[m_RetryMenu * 4 + 4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//pVtx[m_RetryMenu * 4 + 5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//pVtx[m_RetryMenu * 4 + 6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//pVtx[m_RetryMenu * 4 + 7].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//pVtx[RETRY_MENU_RETRY * 4 + 4].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		//pVtx[RETRY_MENU_RETRY * 4 + 5].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		//pVtx[RETRY_MENU_RETRY * 4 + 6].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		//pVtx[RETRY_MENU_RETRY * 4 + 7].col = D3DCOLOR_RGBA(100, 100, 100, 255);
	}

	if (m_RetryMenu == RETRY_MENU_RETRY)
	{
		//頂点カラーの設定
		//pVtx[m_RetryMenu * 4 + 4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//pVtx[m_RetryMenu * 4 + 5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//pVtx[m_RetryMenu * 4 + 6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//pVtx[m_RetryMenu * 4 + 7].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//pVtx[RETRY_MENU_QUIT * 4 + 4].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		//pVtx[RETRY_MENU_QUIT * 4 + 5].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		//pVtx[RETRY_MENU_QUIT * 4 + 6].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		//pVtx[RETRY_MENU_QUIT * 4 + 7].col = D3DCOLOR_RGBA(100, 100, 100, 255);
	}

	//if (pInputKeyboard->GetTrigger(DIK_RETURN) == true  //ENTERキーが押された
	//||  pInputKeyboard->GetTrigger(DIK_SPACE) == true)  //SPACEキーが押された
	//{
	//	//決定キー(ENTERキー)が押された
	//	switch (m_RetryMenu)
	//	{
	//	case RETRY_MENU_QUIT:    //タイトルに行く

	//		//モード設定(ゲームに移行)
	//		CManager::SetMode(MODE_GAME);

	//		//InitCamera();

	//		//TITLESetCamera(600.0f, 500.0f);

	//		//サウンドの再生
	//		//PlaySound(SOUND_LABEL_SE_NEXT);

	//		break;

	//	case RETRY_MENU_RETRY:   //ゲームをやり直す

	//		//モード設定(タイトル画面に移行)
	//		CManager::SetMode(MODE_TITLE);

	//		////カメラの初期化処理 
	//		//InitCamera();
	//		// 
	//		//TITLESetCamera(70.0f, 200.0f);

	//		//サウンドの再生
	//		//PlaySound(SOUND_LABEL_SE_NEXT);

	//		break;
	//	}
	//}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true  //ENTERキーが押された
	||  pInputKeyboard->GetTrigger(DIK_SPACE) == true   //SPACEキーが押された 
	||  pInputPad->GetTrigger(CInputPad::BUTTON_A, 0))  //Aボタンが押された時)
	{
		//モード設定(タイトルに移行)
		CManager::SetMode(MODE_TITLE);
		//CManager::GetFade()->Set(CScene::MODE_TITLE);

		//BreakShadow(pPlayer->nldxShadow); //使用していない状態にする

		//SEの再生
		//pSound->PlaySound(SOUND_LABEL_SE_DECISION);
	}
}
//-------------------------------------------------------
//リザルトの描画処理
//-------------------------------------------------------
void CResult::Draw(void)
{
	//シーンの描画処理
	CScene::Draw();
}