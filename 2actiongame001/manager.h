//=============================================================================
//
// [manager.h]
// Author 若木 一真
//
//=============================================================================
#ifndef _MANAGER_H_  //このマクロ定義がされてなかったら
#define _MANAGER_H_  //2重インクルード防止のマクロを定義する

#include "main.h"
#include "renderer.h"
#include "input.h"
#include "sound.h"
#include "camera.h"
#include "light.h"
#include "texture.h"
#include "model.h"
#include "object.h"
#include "debugproc.h"

//前方宣言
class CDebugProc;

//シーンクラス
class CScene : CObject
{
public:
	typedef enum
	{
		MODE_TITLE = 0,   //タイトル画面
		MODE_TUTORIAL,    //チュートリアル画面
		MODE_GAME,        //ゲーム画面
		MODE_RESULT,      //リザルト画面
		MODE_MAX
	}MODE;

	CScene();   //コンストラクタ
	~CScene();  //デストラクタ

	//メンバ関数
	HRESULT Init(void);  //初期化処理
	void Uninit(void);	 //終了処理
	void Update(void);   //更新処理
	void Draw(void);	 //描画処理
	static CScene *Create(MODE mode);

	//取得
	D3DXVECTOR3 GetPosition(void) { return m_pos; };        //位置の取得
	D3DXVECTOR3 GetPositionOld(void) { return m_posOld; };  //過去の位置の取得
	D3DXVECTOR3 GetMove(void) { return m_move; };           //移動量の取得
	D3DXVECTOR3 GetRotation(void) { return m_rot; };        //向きの取得
	D3DXVECTOR3 GetScale(void) { return m_scale; };         //拡大率の取得
	D3DXVECTOR3 GetSize(void) { return m_size; };           //サイズの取得

	//設定
	void SetPosition(D3DXVECTOR3 pos);            //位置の設定処理
	void SetPositionOld(D3DXVECTOR3 posOld);      //過去の位置の設定処理
	void SetMove(D3DXVECTOR3 move);               //移動量の設定処理
	void SetRotation(D3DXVECTOR3 rot);            //向きの設定処理
	void SetScale(D3DXVECTOR3 scale);             //拡大率の設定処理
	void SetSize(D3DXVECTOR3 size);               //サイズの設定処理
	void SetMode(MODE mode) { m_mode = mode; }

private:
	MODE m_mode;          //モード
	D3DXVECTOR3 m_pos;    //位置
	D3DXVECTOR3 m_posOld; //過去の位置
	D3DXVECTOR3 m_move;   //移動量
	D3DXVECTOR3 m_rot;    //回転量
	D3DXVECTOR3 m_scale;  //拡大率
	D3DXVECTOR3 m_size;   //サイズ量
	float m_fWidth;		  //幅
	float m_fHeight;	  //高さ
};

//マネージャクラス
class CManager
{
public:
	CManager();   //コンストラクタ
	~CManager();  //デストラクタ

	//メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);  //初期化処理
	void Uninit(void);  //終了処理
	HRESULT Update(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);  //更新処理
	void Draw(void);  //描画処理

	//取得
	static CRenderer *GetRenderer(void) { return m_pRenderer; };                 //レンダラーの生成処理
	static CInputKeyboard *GetInputKeyboard(void) { return m_pInputKeyboard; };  //キーボードの生成処理
	static CInputPad *GetInputPad(void) { return m_pInputPad; };                 //ゲームパッドの生成処理
	static CSound *CManager::GetSound(void) { return m_pSound; };                //サウンドの生成処理
	static CCamera *CManager::GetCamera(void) { return m_pCamera; };             //カメラの生成処理
	static CLight *CManager::GetLight(void) { return m_pLight; };                //ライトの生成処理
	static CDebugProc *GetDebugProc(void) { return m_pDebugProc; };	             //デバッグ表示の取得
	static CTexture *GetTexture(void) { return m_pTexture; };	                 //テクスチャの取得
	static CModel *GetModel(void) { return m_pModel; };	                         //モデルの取得

	//シーン
	static void SetMode(CScene::MODE mode);
	static CScene *GetScene(void) { return m_pScene; }
	static void UpdateFade(void);

private:
	static CRenderer *m_pRenderer;  //レンダラーのポインタ
	static CInputKeyboard *m_pInputKeyboard;  //キーボードのポインタ
	static CInputPad *m_pInputPad;  //ゲームパッドのポインタ
	static CSound *m_pSound;  //音のポインタ
	static CCamera *m_pCamera;  //カメラのポインタ
	static CLight *m_pLight;  //ライトのポインタ
	static CDebugProc *m_pDebugProc;  //デバッグ表示のポインタ
	static CTexture *m_pTexture;  //テクスチャのポインタ
	static CModel *m_pModel;  //モデルのポインタ
	static CScene *m_pScene;  //シーンのポインタ
};
#endif