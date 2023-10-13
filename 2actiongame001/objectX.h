//=============================================================================
//
//[objectX.h]
//Author 若木 一真
//
//=============================================================================
#ifndef _OBJECTX_H_  //このマクロ定義がされてなかったら
#define _OBJECTX_H_  //2重インクルード防止のマクロを定義する

#include "object.h"

//マクロ定義
#define INIT_VTX_MIN (D3DXVECTOR3( 9999.0f,  9999.0f,  9999.0f))  //モデルの最小の頂点座標の初期値
#define INIT_VTX_MAX (D3DXVECTOR3(-9999.0f, -9999.0f, -9999.0f))  //モデルの最大の頂点座標の初期値

//オブジェクト3Dクラス
class CObjectX : public CObject
{
public:

	CObjectX();   //コンストラクタ
	~CObjectX();  //デストラクタ

	//メンバ関数
	virtual HRESULT Init(void);    //初期化処理
	virtual void Uninit(void);	   //終了処理
	virtual void Update(void);	   //更新処理
	virtual void Draw(void);	   //描画処理
	static CObjectX *CObjectX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 size, TYPE type);  //生成処理

	//設定
	void SetPosition(D3DXVECTOR3 pos);        //位置の設定処理
	void SetPositionOld(D3DXVECTOR3 posOld);  //位置の設定処理
	void SetMove(D3DXVECTOR3 move);           //移動量の設定処理
	void SetRotation(D3DXVECTOR3 rot);        //向きの設定処理
	void SetScale(D3DXVECTOR3 scale);         //拡大率の設定処理
	void SetSize(D3DXVECTOR3 size);           //サイズの設定処理
	void SetType(const TYPE type);	          //タイプ設定
	void SetTypeTex(int Type);                //テクスチャタイプの設定処理
	void BindModel(int nIdx);                 //モデルの割り当て
	void SetSizeModel(void);                  //モデルサイズの作成

	//取得
	D3DXVECTOR3 GetPosition(void) { return m_pos; };        //位置の取得
	D3DXVECTOR3 GetPositionOld(void) { return m_posOld; };  //過去の位置の取得
	D3DXVECTOR3 GetMove(void) { return m_move; };           //移動量の取得
	D3DXVECTOR3 GetRotation(void) { return m_rot; };        //向きの取得
	D3DXVECTOR3 GetScale(void) { return m_scale; };         //拡大率の取得
	D3DXVECTOR3 GetSize(void) { return m_size; };           //サイズの取得
	int GetTypeTex(void) { return m_typetex; };             //テクスチャタイプの取得

protected:

	int m_nIdxModel;  //モデル

private:
	LPD3DXMESH m_pMesh;                      //メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER m_pBuffMat;                 //マテリアルへのポインタ
	DWORD m_dwNumMat;                        //マテリアルの数
	D3DXVECTOR3 m_pos;                       //位置
	D3DXVECTOR3 m_posOld;                    //過去の位置
	D3DXVECTOR3 m_move;                      //移動量
	D3DXVECTOR3 m_rot;                       //向き
	D3DXVECTOR3 m_scale;                     //拡大率
	D3DXVECTOR3 m_vtxMin;                    //最小の頂点座標
	D3DXVECTOR3 m_vtxMax;                    //最大の頂点座標
	D3DXVECTOR3 m_size;                      //サイズ量
	D3DXMATRIX  m_mtxWorld;                  //ワールドマトリックス
	D3DXMATERIAL MatCopy[32];                //マテリアル保存用
	LPDIRECT3DTEXTURE9 m_apTexture[8] = {};  //テクスチャへのポインタ
	TYPE m_type;  //タイプ種類
	int m_typetex;  //テクスチャタイプ
	float m_fWidth;  //幅
	float m_fHeight;	  //高さ
};

#endif