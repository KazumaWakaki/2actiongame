//=============================================================================
//
// 入力処理 [input.cpp]
// Author 若木 一真
//
//=============================================================================
#include "input.h"

//静的メンバ変数
LPDIRECTINPUT8 CInput::m_pInput = NULL;  //DirectInputオブジェクトへのポインタ

//------------------------------------------------------------------------------------------------------
//
//入力処理
//
//------------------------------------------------------------------------------------------------------
//=======================================================
//コンストラクタ
//=======================================================
CInput::CInput()
{

}
//=======================================================
//デストラクタ
//=======================================================
CInput::~CInput()
{

}
//=======================================================
//初期化処理
//=======================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの生成
	if (m_pInput == NULL)
	{
		DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL);
	}

	return S_OK;
}
//=======================================================
//終了処理
//=======================================================
void CInput::Uninit(void)
{
	//入力デバイス(キーボード)の破棄
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();   //キーボードへのアクセス権を放棄
		m_pDevice->Release();  
		m_pDevice = NULL;
	}

	//DirectInputオブジェクトの破棄
	if (m_pInput!= NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}
//------------------------------------------------------------------------------------------------------
//
//キーボード処理
//
//------------------------------------------------------------------------------------------------------
//=======================================================
//キーボードのコンストラクタ
//=======================================================
CInputKeyboard::CInputKeyboard()
{
	for (int nCount = 0; nCount < NUM_KEY_MAX; nCount++)
	{
		m_aKeyState[nCount] = NULL;
		m_aKeyStateTrigger[nCount] = NULL;
	}
}
//=======================================================
//キーボードのデストラクタ
//=======================================================
CInputKeyboard::~CInputKeyboard()
{

}
//=======================================================
//キーボードの初期化処理
//=======================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	//初期化処理
	CInput::Init(hInstance, hWnd);

	//入力デバイス(キーボード)の生成
	m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL);

	//データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードのアクセス権を獲得
	m_pDevice->Acquire();

	return S_OK;
}
//=======================================================
//キーボードの終了処理
//=======================================================
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}
//=======================================================
//キーボードの更新処理
//=======================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];

	//入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];  //キーボードのトリガー情報を保存
			m_aKeyState[nCntKey] = aKeyState[nCntKey];  //キーボードのプレス情報を保存
		}
	}

	else
	{
		m_pDevice->Acquire();  //キーボードへのアクセス権を獲得
	}
}
//=======================================================
//キーボードのプレス情報を取得
//=======================================================
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}
//=======================================================
//キーボードのトリガー情報を取得
//=======================================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}
//=======================================================
//キーボードのリピート情報を取得
//=======================================================
bool CInputKeyboard::GetRipeat(int nKey)
{
	return (m_aKeyStateRipeat[nKey] & 0x80) ? true : false;
}
//=======================================================
//キーボードのリリース情報を取得
//=======================================================
bool CInputKeyboard::GetRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}
//------------------------------------------------------------------------------------------------------
//
//ゲームパッド処理
//
//------------------------------------------------------------------------------------------------------
//=======================================================
//コンストラクタ
//=======================================================
CInputPad::CInputPad()
{

}
//=======================================================
//デストラクタ
//=======================================================
CInputPad::~CInputPad()
{

}
//=======================================================
//ゲームパッド初期化処理
//=======================================================
HRESULT CInputPad::Init(void)
{
	//変数宣言
	int nCntPad;

	//XInputのステート(使う状態)
	XInputEnable(true);

	//メモリの初期化(プレイヤー分)
	for (nCntPad = 0; nCntPad < NUM_PLAYER; nCntPad++)
	{
		memset(&m_aGamePadState[nCntPad], 0, sizeof(XINPUT_STATE));
		memset(&m_aGamePadStateTrigger[nCntPad], 0, sizeof(XINPUT_STATE));
		memset(&m_aGamePadStateRelease[nCntPad], 0, sizeof(XINPUT_STATE));
		memset(&m_aGamePadStateRepeat[nCntPad], 0, sizeof(XINPUT_STATE));
	}

	return S_OK;
}
//=======================================================
//ゲームパッドの終了処理
//=======================================================
void CInputPad::Uninit(void)
{
	//XInputのステート(使わない状態)
	XInputEnable(false);
}
//=======================================================
//ゲームパッドの更新処理
//=======================================================
void CInputPad::Update(void)
{
	//変数宣言
	int nCntPad;

	XINPUT_STATE aGamePadState;  //ゲームパッドの入力情報

	for (nCntPad = 0; nCntPad < NUM_PLAYER; nCntPad++)
	{
		//入力デバイスからデータを取得
		if (XInputGetState(nCntPad, &aGamePadState) == ERROR_SUCCESS)
		{
			//ゲームパッドのトリガー情報を保存
			m_aGamePadStateTrigger[nCntPad].Gamepad.wButtons =
				(m_aGamePadState[nCntPad].Gamepad.wButtons ^ aGamePadState.Gamepad.wButtons) & aGamePadState.Gamepad.wButtons;

			//リピート情報
			m_aGamePadStateRepeat[nCntPad].Gamepad.wButtons =
				(m_aGamePadState[nCntPad].Gamepad.wButtons & aGamePadState.Gamepad.wButtons);

			//リリース情報
			m_aGamePadStateRelease[nCntPad].Gamepad.wButtons =
				(m_aGamePadState[nCntPad].Gamepad.wButtons | aGamePadState.Gamepad.wButtons) ^ aGamePadState.Gamepad.wButtons;

			//ゲームパッドのプレス情報を保存
			m_aGamePadState[nCntPad] = aGamePadState;
		}
	}
}
//=======================================================
//ジョイスティック情報取得
//=======================================================
SHORT CInputPad::GetJoyStickLX(int nPlayer)
{
	//情報を返す
	return m_aGamePadState[nPlayer].Gamepad.sThumbLX;
}
//=======================================================
//ジョイスティック情報取得
//=======================================================
SHORT CInputPad::GetJoyStickLY(int nPlayer)
{
	//情報を返す
	return m_aGamePadState[nPlayer].Gamepad.sThumbLY;
}
//=======================================================
//ジョイスティック情報取得
//=======================================================
SHORT CInputPad::GetJoyStickRX(int nPlayer)
{
	//情報を返す
	return m_aGamePadState[nPlayer].Gamepad.sThumbRX;
}
//=======================================================
//ジョイスティック情報取得
//=======================================================
SHORT CInputPad::GetJoyStickRY(int nPlayer)
{
	//情報を返す
	return m_aGamePadState[nPlayer].Gamepad.sThumbRY;
}
//=======================================================
//ゲームパッドのプレス情報を取得
//=======================================================
bool CInputPad::GetPress(JOYKEY nKey, int nPlayer)
{
	return (m_aGamePadState[nPlayer].Gamepad.wButtons & 0x01 << nKey) ? true : false;
}
//=======================================================
//ゲームパッドのトリガー情報を取得
//=======================================================
bool CInputPad::GetTrigger(JOYKEY nKey, int nPlayer)
{
	return (m_aGamePadStateTrigger[nPlayer].Gamepad.wButtons & 0x01 << nKey) ? true : false;
}
//=======================================================
//ゲームパッドのリリース情報を取得
//=======================================================
bool CInputPad::GetRelease(JOYKEY nKey, int nPlayer)
{
	return (m_aGamePadStateRelease[nPlayer].Gamepad.wButtons & 0x01 << nKey) ? true : false;
}
//=======================================================
//ゲームパッドのリピート情報取得
//=======================================================
bool CInputPad::GetRepeat(JOYKEY nKey, int nPlayer)
{
	//三項演算子
	return(m_aGamePadStateRepeat[nPlayer].Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}