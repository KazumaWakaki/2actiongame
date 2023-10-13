//=============================================================================
//
// [texture.h]
// Author 若木 一真
//
//=============================================================================
#ifndef _TEXTURE_H_  //このマクロ定義がされてなかったら
#define _TEXTURE_H_  //2重インクルード防止のマクロを定義する

#include "main.h"

//マクロ定義
#define MAX_TEXTURE  (256)  //テクスチャの最大数

//テクスチャクラス
class CTexture
{
public:
	CTexture();   //コンストラクタ
	~CTexture();  //デストラクタ

	//テクスチャ処理関数
	static HRESULT Load(void);  //テクスチャの生成(読み込み)
	static void Unload(void);   //テクスチャの破棄

	//メンバ関数
	int Regist(const char *pFilename);        //テクスチャを設定する
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);  //アドレスを返す

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEXTURE];  //テクスチャ配列
	static char m_FileName[MAX_TEXTURE][512];            //テクスチャの名前確認用
	static int m_nNumAll;                                //総数
};

#endif