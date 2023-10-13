//=============================================================================
//
// [renderer.h]
// Author 若木 一真
//
//=============================================================================
#ifndef _RENDERER_H_  //このマクロ定義がされてなかったら
#define _RENDERER_H_  //2重インクルード防止のマクロを定義する

#include "main.h"

//レンダラークラス
class CRenderer
{
public:
	CRenderer();  //コンストラクタ
	~CRenderer(); //デストラクタ

	HRESULT Init(HWND hWnd, bool bWindow);  //初期化処理
	void Uninit(void);						//終了処理
	void Update(void);						//更新処理
	void Draw(void);						//描画処理
	LPDIRECT3DDEVICE9 GetDevice(void);      //デバイスの取得

private:

	LPDIRECT3D9 m_pD3D;              //Direct3Dオブジェクトの生成
	LPDIRECT3DDEVICE9 m_pD3DDevice;  //デバイスの宣言
};

#endif