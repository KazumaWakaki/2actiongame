//=============================================================================
//
// [model.h]
// Author 若木 一真
//
//=============================================================================
#ifndef _MODEL_H_  //このマクロ定義がされてなかったら
#define _MODEL_H_  //2重インクルード防止のマクロを定義する

#include "main.h"

//マクロ定義
#define MAX_MODEL  (128)  //モデルの最大数

//モデルクラス
class CModel
{
public:
	//モデル構造体の定義
	typedef struct
	{
		LPD3DXMESH m_pMesh;       //メッシュ(頂点情報)へのポインタ
		LPD3DXBUFFER m_pBuffMat;  //マテリアルへのポインタ
		DWORD m_dwNumMat;         //マテリアルの数
		int *pIndxTex;            //テクスチャ保存用
	}Model;

	CModel();   //コンストラクタ
	~CModel();  //デストラクタ

	//モデル処理関数
	static HRESULT Load(void);  //モデルの生成(読み込み)
	static void Unload(void);   //モデルの破棄

	//メンバ関数
	int Regist(const char *pFilename);  //モデルを設定する
	Model *GetAddress(int nIdx);         //メッシュのアドレスを返す

private:
	static Model m_apModel[MAX_MODEL];
	static char m_FileName[MAX_MODEL][512];  //モデルの名前確認用
	static int m_nNumAll;                    //総数
};

#endif