//=============================================================================
//
// [wall.h]
// Author 若木 一真
//
//=============================================================================
#ifndef _WALL_H_  //このマクロ定義がされてなかったら
#define _WALL_H_  //2重インクルード防止のマクロを定義する

#include "object3D.h"

//3D壁クラス
class CWall : public CObject3D
{
public:
	//テクスチャタイプ種類
	typedef enum
	{
		TYPE_BLOCK003 = 0,  //ブロック
		TYPE_HAIKEI001,     //林の背景
		TYPE_MAX
	}TYPE;

	CWall(int nPriority = 3);
	~CWall();  //デストラクタ

	//メンバ関数
	virtual HRESULT Init(void);  //初期化処理
	virtual void Uninit(void);	    //終了処理
	virtual void Update(void);	//更新処理
	virtual void Draw(void);	    //描画処理
	static CWall *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int SetTypeTex);  //生成処理

private:
	LPDIRECT3DTEXTURE9 m_pTexture;  //テクスチャへのポインタ
	D3DXVECTOR3 m_pos;              //位置
	D3DXVECTOR3 m_rot;              //回転量
	D3DXVECTOR3 m_size;             //サイズ量
	int m_typetex;                  //テクスチャタイプ
	int m_nIdxTexture[TYPE_MAX];    //テクスチャ
};

#endif