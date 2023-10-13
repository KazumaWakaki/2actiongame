//=======================================================
//
// タイトル処理
// Author 若木一真
//
//=======================================================
#include "title.h"
#include "object2D.h"

//マクロ定義
#define MAX_TEX	 (2)   //使用するテクスチャ数

//-------------------------------------------------------
//コンストラクタ
//-------------------------------------------------------
CTitle::CTitle()
{

}
//-------------------------------------------------------
//デストラクタ
//-------------------------------------------------------
CTitle::~CTitle()
{

}
//-------------------------------------------------------
//タイトルの初期化処理
//-------------------------------------------------------
HRESULT CTitle::Init(void)
{
	//サウンドの取得
	CSound *pSound;
	pSound = CManager::GetSound();

	m_TitleSelect = TITLE_START;   //タイトルセレクト

	//オブジェクト2Dの生成処理
	CObject2D::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(640.0f, 360.0f, 0.0f), CObject2D::TYPE_TITLE);

	//BGMの再生
	//pSound->PlaySound(SOUND_LABEL_BGM_TITLE);

	return S_OK;
}
//-------------------------------------------------------
//タイトルの終了処理
//-------------------------------------------------------
void CTitle::Uninit(void)
{
	//シーンの終了処理
	CScene::Uninit();
}
//-------------------------------------------------------
//タイトル画面の更新処理
//-------------------------------------------------------
void CTitle::Update(void)
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

	if (m_TitleCounter <= 50)
	{
		//頂点カラーの設定 

	}

	else
	{
		//頂点カラーの設定

	}

	if (m_TitleCounter >= 110)
	{
		m_TitleCounter = 0;
	}

	m_TitleCounter++;

	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputPad->GetTrigger(CInputPad::BUTTON_A, 0))
	{
		//モード設定(チュートリアルに移行)
		CManager::SetMode(MODE_TUTORIAL);
		//CManager::GetFade()->Set(CScene::MODE_TUTORIAL);

		CScene::Update();

		//SEの再生
		//pSound->PlaySound(SOUND_LABEL_SE_DECISION);
	}
}
//-------------------------------------------------------
//タイトル画面の描画処理
//-------------------------------------------------------
void CTitle::Draw(void)
{
	//シーンの描画処理
	CScene::Draw();
}