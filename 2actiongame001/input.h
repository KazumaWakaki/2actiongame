//=============================================================================
//
// [input.h]
// Author 若木 一真
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include"main.h"
#include"Xinput.h"
#pragma comment(lib,"xinput.lib")

//マクロ定義
#define NUM_KEY_MAX (256)  //キーの最大値
#define NUM_PLAYER    (4)  //プレイヤー数

//入力クラス
class CInput
{
public:
	CInput();
	virtual ~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected:
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;
};

//キーボードクラス
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRipeat(int nKey);
	bool GetRelease(int nKey);

private:
	BYTE m_aKeyState[NUM_KEY_MAX];              //キーボードプレス情報
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];   //キーボードトリガー情報
	BYTE m_aKeyStateRipeat[NUM_KEY_MAX];    //キーボードリピートの情報
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];  //キーボードリリースの情報
};

//パッド(xinput)
class CInputPad : public CInput
{
public:
	//押されたボタンの種類
	typedef enum //20以内
	{
		BUTTON_0 = 0,	 //十字↑ 
		BUTTON_1,		     //十字↓
		BUTTON_2,		     //十字←
		BUTTON_3,		     //十字→
		BUTTON_START,	 //start
		BUTTON_BACK,	 //back
		BUTTON_LS,		 //左スティック押し込み
		BUTTON_RS,		 //右スティック押し込み
		BUTTON_LB,		 //LB/5
		BUTTON_RB,		 //RB/6
		BUTTON_10,		 //?
		BUTTON_11,		 //?
		BUTTON_A,		     //A/3 
		BUTTON_B,		     //B/4
		BUTTON_X,		     //X/1
		BUTTON_Y,		     //Y/2
		BUTTON_16,		 //?
		BUTTON_17,		 //?
		BUTTON_18,		 //?
		BUTTON_19,		 //?
		BUTTON_20,		 //?
		BUTTON_MAX
	} JOYKEY;

	CInputPad();
	~CInputPad();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	bool GetPress(JOYKEY nKey, int nPlayer);
	bool GetTrigger(JOYKEY nKey, int nPlayer);
	bool GetRelease(JOYKEY nKey, int nPlayer);
	bool GetRepeat(JOYKEY nKey, int nPlayer);
	SHORT GetJoyStickLX(int nPlayer);
	SHORT GetJoyStickLY(int nPlayer);
	SHORT GetJoyStickRX(int nPlayer);
	SHORT GetJoyStickRY(int nPlayer);

private:
	XINPUT_STATE m_aGamePadState[NUM_PLAYER];			//ゲームパッドプレス情報
	XINPUT_STATE m_aGamePadStateTrigger[NUM_PLAYER];	//ゲームパッドトリガー情報
	XINPUT_STATE m_aGamePadStateRelease[NUM_PLAYER];	//ゲームパッドリリース情報
	XINPUT_STATE m_aGamePadStateRepeat[NUM_PLAYER];		//ゲームパッドリピート情報
};

#endif