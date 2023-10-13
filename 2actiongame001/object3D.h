//=============================================================================
//
//[object3D.h]
//Author 若木 一真
//
//=============================================================================
#ifndef _OBJECT3D_H_  //このマクロ定義がされてなかったら
#define _OBJECT3D_H_  //2重インクルード防止のマクロを定義する

#include "object.h"

//マクロ定義
#define COUNTAMIME (8)       //アニメーション速度
#define PATTERNAMIME (8)     //アニメーションパターン数
#define PATTERNTEX (0.125f)  //テクスチャのパターン数

//オブジェクト3Dクラス
class CObject3D : public CObject
{
public:
	CObject3D(int nPriority = 3);
	~CObject3D();  //デストラクタ

	//メンバ関数
	static CObject3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);  //生成処理
	virtual HRESULT Init(void);                                                    //初期化処理
	virtual void Uninit(void);	                                                   //終了処理
	virtual void Update(void);	                                                   //更新処理
	virtual void Draw(void);	                                                   //描画処理
	virtual void DrawAnim(void);	                                               //描画処理(アニメーション)
	virtual void DrawEffect(void);                                                 //描画処理(エフェクト)
	void BindTexture(int nIdx);                                                    //テクスチャの割り当て

	//設定
	void SetPosition(D3DXVECTOR3 pos);            //位置の設定処理
	void SetPositionOld(D3DXVECTOR3 posOld);      //位置の設定処理
	void SetMove(D3DXVECTOR3 move);               //移動量の設定処理
	void SetRotation(D3DXVECTOR3 rot);            //向きの設定処理
	void SetScale(D3DXVECTOR3 scale);             //拡大率の設定処理
	void SetSize(D3DXVECTOR3 size);               //サイズの設定処理
	//void SetSize2D(float fWidth, float fHeight);  //サイズ2Dの設定処理
	void SetTypeTex(int Type);                    //テクスチャタイプの設定処理
	void SetCol(const D3DXCOLOR col);             //色設定

	//取得
	D3DXVECTOR3 GetPosition(void) { return m_pos; };        //位置の取得
	D3DXVECTOR3 GetPositionOld(void) { return m_posOld; };  //過去の位置の取得
	D3DXVECTOR3 GetMove(void) { return m_move; };           //移動量の取得
	D3DXVECTOR3 GetRotation(void) { return m_rot; };        //向きの取得
	D3DXVECTOR3 GetScale(void) { return m_scale; };         //拡大率の取得
	D3DXVECTOR3 GetSize(void) { return m_size; };           //サイズの取得
	D3DXCOLOR GetCol(void) { return m_Col; };               //色の取得
	int GetTypeTex(void) { return m_typetex; };             //テクスチャタイプの取得

	//頂点情報の生成
	void SetVtxWidth(void);                 //頂点情報の生成(横)
	void SetVtxHeight(void);                //頂点情報の生成(縦)
	void SetVtx(const int m_nPatternAnim);  //頂点情報の生成(アニメーション)
	void SetVtxEffect(void);                //頂点情報の生成(エフェクト)

	int m_nCounterAnim;  //アニメーションカウンター
	int m_nPatternAnim;  //アニメーションパターンNo.

private:
	LPDIRECT3DTEXTURE9 m_pTexture;       //テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	 //頂点バッファへのポインタ
	D3DXMATRIX m_mtxWorld;               //ワールドマトリックス
	D3DXVECTOR3 m_pos;                   //位置
	D3DXVECTOR3 m_posOld;                //過去の位置
	D3DXVECTOR3 m_move;                  //移動量
	D3DXVECTOR3 m_rot;                   //回転量
	D3DXVECTOR3 m_scale;                 //拡大率
	D3DXVECTOR3 m_size;                  //サイズ量
	D3DXCOLOR m_Col;                     //色
	int m_typetex;                       //テクスチャタイプ
	int m_nIdxTexture;
	float m_fWidth;						 //幅
	float m_fHeight;					 //高さ
};

#endif