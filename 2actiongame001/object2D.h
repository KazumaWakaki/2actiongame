//=============================================================================
//
//[object2D.h]
//Author 若木 一真
//
//=============================================================================
#ifndef _OBJECT2D_H_  //このマクロ定義がされてなかったら
#define _OBJECT2D_H_  //2重インクルード防止のマクロを定義する

#include "object.h"

//マクロ定義
#define COUNTAMIME (8)  //アニメーション速度
#define PATTERNAMIME (8)  //アニメーションパターン数
#define PATTERNTEX (0.125f)  //テクスチャのパターン数

//オブジェクト2Dクラス
class CObject2D : public CObject
{
public:
	//テクスチャタイプ種類
	typedef enum
	{
		TYPE_TITLE = 0,  //タイトル
		TYPE_TUTORIAL,  //チュートリアル
		TYPE_RESULT,  //リザルト
		TYPE_ENTER,  //プレスエンター
		TYPE_NUMBER,  //ナンバー
		TYPE_MAX
	}TYPE;

	CObject2D(int nPriority = 3);  //コンストラクタ
	~CObject2D();  //デストラクタ

	//メンバ関数
	virtual HRESULT Init(void);  //初期化処理
	virtual void Uninit(void);  //終了処理
	virtual void Update(void);  //更新処理
	virtual void Draw(void);  //描画処理
	virtual void DrawEffect(void);  //描画処理(エフェクト)
	static CObject2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int SetTypeTex);  //生成処理
	void BindTexture(int nIdx);  //テクスチャの割り当て

	//取得
	D3DXVECTOR3 GetPosition(void) { return m_pos; };  //位置の取得
	D3DXVECTOR3 GetPositionOld(void) { return m_posOld; };  //過去の位置の取得
	D3DXVECTOR3 GetMove(void) { return m_move; };  //移動量の取得
	D3DXVECTOR3 GetRotation(void) { return m_rot; };  //向きの取得
	D3DXVECTOR3 GetScale(void) { return m_scale; };  //拡大率の取得
	D3DXVECTOR3 GetSize(void) { return m_size; };  //サイズの取得
	int GetTypeTex(void) { return m_typetex; };  //テクスチャタイプの取得

	//設定
	void SetPosition(D3DXVECTOR3 pos);  //位置の設定処理
	void SetPositionOld(D3DXVECTOR3 posOld);  //過去の位置の設定処理
	void SetMove(D3DXVECTOR3 move);  //移動量の設定処理
	void SetRotation(D3DXVECTOR3 rot);  //向きの設定処理
	void SetScale(D3DXVECTOR3 scale);  //拡大率の設定処理
	void SetSize(D3DXVECTOR3 size);  //サイズの設定処理
	void SetTypeTex(int Type);  //テクスチャタイプの設定処理

	//メンバ関数
	void SetVtx(void);  //頂点情報の生成
	void SetVtxUI(void);  //頂点情報の生成(UI)
	void SetVtxBG(float g_aTexV, float g_aTexU);  //頂点情報の生成(背景)
	void SetVtxEffect(void);  //頂点情報の生成(エフェクト)
	void SetVtx(const int nPatternAnim, const int nTexWidth, const int nTexHeight);  //頂点情報の生成(アニメーション)
	void SetVtxLife(int posR);  //頂点情報の生成(体力)
	void SetCol(const D3DXCOLOR col);  //色の設定
	int m_nCounterAnim;  //アニメーションカウンター
	int m_nPatternAnim;  //アニメーションパターンNo.

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	 //頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;  //位置
	D3DXVECTOR3 m_posOld;  //過去の位置
	D3DXVECTOR3 m_move;  //移動量
	D3DXVECTOR3 m_rot;  //回転量
	D3DXVECTOR3 m_scale;  //拡大率
	D3DXVECTOR3 m_size;  //サイズ量
	float m_fWidth;  //幅
	float m_fHeight;  //高さ
	int m_typetex;  //テクスチャタイプ
	int m_nIdxTexture[TYPE_MAX];  //テクスチャ割り当て
};

#endif