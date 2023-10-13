//=============================================================================
//
// [sound.h]
// Author 若木一真
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
//サウンド一覧
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM_GAME = 0,   //ゲームBGM
//	SOUND_LABEL_BGM_TITLE,      //タイトルBGM
//	SOUND_LABEL_BGM_RESULT,     //リザルトBGM
//	SOUND_LABEL_SE_FIRING,	    //発射SE
//	SOUND_LABEL_SE_JAMP,	    //ジャンプSE
//	SOUND_LABEL_SE_DAMAGE,	    //ダメージSE
//	SOUND_LABEL_SE_DEATH,	    //死亡SE
//	SOUND_LABEL_SE_EXPLOSION,   //爆発SE
//	SOUND_LABEL_SE_SELECT,      //選択SE
//	SOUND_LABEL_SE_DECISION,    //決定SE
//	SOUND_LABEL_SE_MELEE,       //近接攻撃SE
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
//サウンド情報の構造体定義
//*****************************************************************************
typedef struct
{
	char *pFilename;	//ファイル名
	int nCntLoop;		//ループカウント
} SOUNDINFO;

//*****************************************************************************
//プロトタイプ宣言
//*****************************************************************************

//スコアクラス
class CSound
{
public:
	CSound();   //コンストラクタ
	~CSound();  //デストラクタ

	//メンバ関数
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);

private:
	IXAudio2 *g_pXAudio2 = NULL;								 //XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *g_pMasteringVoice = NULL;			 //マスターボイス
	IXAudio2SourceVoice *g_apSourceVoice[SOUND_LABEL_MAX] = {};	 //ソースボイス
	BYTE *g_apDataAudio[SOUND_LABEL_MAX] = {};					 //オーディオデータ
	DWORD g_aSizeAudio[SOUND_LABEL_MAX] = {};					 //オーディオデータサイズ
	static SOUNDINFO g_aSoundInfo[SOUND_LABEL_MAX];

};
#endif