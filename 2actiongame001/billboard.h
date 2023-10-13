//=============================================================================
//
// [billboard.h]
// Author 若木 一真
//
//=============================================================================
#ifndef _BILLBOARD_H_  //このマクロ定義がされてなかったら
#define _BILLBOARD_H_  //2重インクルード防止のマクロを定義する

#include "object.h"

//オブジェクト3Dクラス
class CBillboard : public CObject
{
public:
	CBillboard();   //コンストラクタ
	~CBillboard();  //デストラクタ

	//メンバ関数
	virtual HRESULT Init(void);                                                                 //初期化処理
	virtual void Uninit(void);	                                                                //終了処理
	virtual void Update(void);	                                                                //更新処理
	virtual void Draw(void);	                                                                //描画処理
	static CBillboard *CBillboard::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);  //生成処理
	void BindTexture(int nIdx);                                                                 //テクスチャ割り当て
	void SetVtx(void);                                                                          //頂点情報の生成
	void SetVtxLife(void);                                                                      //頂点情報の生成(ライフ)
	void SetVtx(const int nPatternAnim, const int nTexWidth, const int nTexHeight);             //頂点情報の生成(アニメーション)

	//設定
	void SetPosition(D3DXVECTOR3 pos);        //位置の設定処理
	void SetPositionOld(D3DXVECTOR3 posOld);  //位置(過去)の設定処理
	void SetMove(D3DXVECTOR3 move);           //移動量の設定処理
	void SetRotation(D3DXVECTOR3 rot);        //向きの設定処理
	void SetScale(D3DXVECTOR3 scale);         //拡大率の設定処理
	void SetSize(D3DXVECTOR3 size);           //サイズの設定処理
	void SetTypeTex(int Type);                //テクスチャタイプの設定処理

	//取得
	D3DXVECTOR3 GetPosition(void) { return m_pos; };        //位置の取得
	D3DXVECTOR3 GetPositionOld(void) { return m_posOld; };  //過去の位置の取得
	D3DXVECTOR3 GetMove(void) { return m_move; };           //移動量の取得
	D3DXVECTOR3 GetRotation(void) { return m_rot; };        //向きの取得
	D3DXVECTOR3 GetScale(void) { return m_scale; };         //拡大率の取得
	D3DXVECTOR3 GetSize(void) { return m_size; };           //サイズの取得
	int GetTypeTex(void) { return m_typetex; };             //テクスチャタイプの取得

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	 //頂点バッファへのポインタ
	D3DXMATRIX m_mtxWorld;               //ワールドマトリックス
	D3DXVECTOR3 m_pos;                   //位置
	D3DXVECTOR3 m_posOld;                //過去の位置
	D3DXVECTOR3 m_move;                  //移動量
	D3DXVECTOR3 m_rot;                   //回転量
	D3DXVECTOR3 m_scale;                 //拡大率
	D3DXVECTOR3 m_size;                  //サイズ量
	int m_typetex;                       //テクスチャタイプ
	int m_nIdxTexture;                   //テクスチャ割り当て
};

#endif