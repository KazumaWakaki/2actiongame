//=============================================================================
//
// メイン関数 [main.cpp]
// Author 若木 一真
//
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "input.h"

//マクロ定義
#define CLASS_NAME  "WindowClass"     //ウィンドウクラスの名前
#define WINDOW_NAME "アクションゲーム"  //ウィンドウの名前
#define ID_BUTTON_FINISH (101)        //終了ボタンのID

//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LPDIRECT3DDEVICE9 m_pD3DDevice = NULL;;
LPD3DXFONT g_pFont = NULL;               //フォントへのポインタ
LPDIRECT3DDEVICE9 GetDevice(void);
void DrawFPS(void);

//グローバル変数宣言
int g_nCountFPS = 0;                     //FPSカウンタ

//-------------------------------------------------------
//メイン関数
//-------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR IpCmdLine, int nCmdshow)
{
	DWORD dwCurrentTime;  //現在時刻
	DWORD dwExecLastTime; //最後に処理した時刻
	DWORD dwFrameCount;   //フレームカウント
	DWORD dwFPSLastTime;  //最後にFPSを

	dwCurrentTime = 0;               //初期化する
	dwExecLastTime = timeGetTime();  //現在時刻を取得
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//デバッグ表示用フォントの生成
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);

	CManager *pManager = NULL;

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),             //WNDCLASSEXのメモリサイズ
		CS_CLASSDC,                     //ウィンドウのスタイル
		WindowProc,                     //ウィンドウプロシージャ
		0,                              //0にする
		0,                              //0にする
		hInstance,                      //インスタンスハンドル
		LoadIcon(NULL,IDC_ARROW),	    //タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),     //マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),     //クライアント領域の背景色
		NULL,                           //メニューバー
		CLASS_NAME,                     //ウィンドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION)
	};

	HWND hWnd;  //ウィンドウハンドル
	MSG msg;    //メッセージを格納する変数

	//ウィンドウクラスの発録
	RegisterClassEx(&wcex);

	//ウィンドウを生成
	hWnd = CreateWindowEx
	(
		0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,        //ウィンドウの左上X座標
		CW_USEDEFAULT,        //ウィンドウの左上Y座標
		SCREEN_WIDTH,         //幅
		SCREEN_HEIGHT,        //高さ
		NULL,                 //親ウィンドウのハンドル
		NULL,                 //メニューハンドルまたは子ウィンドウID
		hInstance,            //インスタンスハンドル
		NULL
	);

	//pManagerがNULLの時
	if (pManager == NULL)
	{
		//マネージャの作成
		pManager = new CManager;
	}

	//pManagerがNULLじゃない時
	if (pManager != NULL)
	{
		//初期化処理が失敗した場合
		if (FAILED(pManager->Init(hInstance, hWnd, TRUE)))
		{
			return -1;
		}
	}

	//ウィンドウの表示
	ShowWindow(hWnd, nCmdshow);  //ウィンドウの表示状態を設定
	UpdateWindow(hWnd);          //クライアント領域を更新

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			//windowsの処理
			if (msg.message == WM_QUIT)
			{
				//WM_QUITメッセージを受け取ったらメッセージループをぬける
				break;
			}
			else
			{
				//メッセージの設定
				TranslateMessage(&msg); //仮想キーメッセージを文字へ変換
				DispatchMessage(&msg);
			}
		}

		else
		{
			//DirectXの処理
			dwCurrentTime = timeGetTime();       //現在時刻を取得

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{
				//0.5秒経過
				//FPSを計測
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;                //フレームカウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				//60分の1秒経過
				dwExecLastTime = dwCurrentTime;  //処理開始の時刻[現在時刻]を保存

				//マネージャの更新処理
				pManager->Update(hInstance, hWnd, TRUE);

				//マネージャの描画処理
				pManager->Draw();

				//FPSの表示
				DrawFPS();

				dwFrameCount++;    //フレームカウントを加算
			}
		}
	}

	//マネージャの破棄
	if (pManager != NULL)
	{
		//マネージャの終了処理
		pManager->Uninit();

		delete pManager;

		pManager = NULL;
	}

	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return(int)msg.wParam;
}
//-------------------------------------------------------
//ウィンドウプロシージャ
//-------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;

	switch (uMsg)
	{
	case WM_DESTROY:  //ウィンドウ破棄のメッセージ

		//WM_QUITメッセージを送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:  //キー押下のメッセージ

		switch (wParam)
		{
		case VK_ESCAPE:  //[ESC]キーが押された

			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);  //終了メッセージ

			if (nID == IDYES)
			{
				//ウィンドウを破棄する(WM_DESTROYメッセージを送る)
				DestroyWindow(hWnd);
			}

			else
			{
				return 0;  //0を返さないと終了してしまう
			}

			break;
		}

		break;

	case WM_CLOSE:  //閉じるボタン押下のメッセージ

		nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);

		//はいを選択した場合
		if (nID == IDYES)
		{
			//ウィンドウを破棄する
			DestroyWindow(hWnd);
		}

		else
		{
			return 0;  //0を返さないと終了してしまう
		}

		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
//==================================================================================
//FPSの表示
//==================================================================================
void DrawFPS(void)
{
	//RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	//char aStr[256];

	////文字列に代入
	//wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);

	////テキストの描画
	//g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}
//==================================================================================
//デバイスの取得
//==================================================================================
LPDIRECT3DDEVICE9  GetDevice(void)
{
	return m_pD3DDevice;
}
