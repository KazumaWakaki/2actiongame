//=============================================================================
//
// ライフ処理 [life.cpp]
// Author：若木一真
//
//=============================================================================
#include "manager.h"
#include "life.h"
#include "player3D.h"

//静的メンバ変数
CLife *CLife::m_apObject = NULL;

//-------------------------------------------------------
//コンストラクタ
//-------------------------------------------------------
CLife::CLife()
{
	if (m_apObject == NULL)
	{
		m_apObject = this;
	}

	SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //位置の初期化
	SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //サイズの初期化
}
//-------------------------------------------------------
//デストラクタ
//-------------------------------------------------------
CLife::~CLife()
{

}
//-------------------------------------------------------
//ライフの初期化処理
//-------------------------------------------------------
HRESULT CLife::Init(void)
{
	CTexture *pTexture = CManager::GetTexture();

	m_nIdxTexture[TYPE_LIFEFRAME] = pTexture->Regist("data\\texture\\life001.png");
	m_nIdxTexture[TYPE_LIFEGAUGE] = pTexture->Regist("data\\texture\\lifegauge001.png");

	//オブジェクトビルボードの初期化処理
	CObject2D::Init();

	//種類の設定
	CObject::SetType(TYPE_LIFE);

	return (S_OK);
}
//-------------------------------------------------------
//ライフの終了処理
//-------------------------------------------------------
void CLife::Uninit(void)
{
	//オブジェクトビルボードの終了処理
	CObject2D::Uninit();

	m_apObject = NULL;
}
//-------------------------------------------------------
//ライフの更新処理
//-------------------------------------------------------
void CLife::Update(void)
{

}
//-------------------------------------------------------
//ライフの描画処理
//-------------------------------------------------------
void CLife::Draw(void)
{
	//オブジェクトビルボードの描画(アニメーション)処理
	CObject2D::Draw();
}
//-------------------------------------------------------
//生成処理
//-------------------------------------------------------
CLife *CLife::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 scale, int SetTypeTex)
{
	CLife *pLife = NULL;

	//ライフの生成
	pLife = new CLife;

	//pLifeがNULLじゃなかった時
	if (pLife != NULL)
	{
		//ライフの初期化処理
		pLife->Init();

		//ライフの位置の設定
		pLife->SetPosition(pos);

		//ライフのサイズ
		pLife->SetSize(size);

		//ライフのスケール
		pLife->SetScale(scale);

		//テクスチャタイプ
		pLife->SetTypeTex(SetTypeTex);

		//頂点情報の生成
		pLife->SetVtxUI();

		//nCount分回す
		for (int nCount = 0; nCount < TYPE_MAX; nCount++)
		{
			//nCountと選択されたモデルタイプが一致した時
			if (nCount == SetTypeTex)
			{
				//テクスチャの割り当て
				pLife->BindTexture(pLife->m_nIdxTexture[nCount]);
			}
		}
	}

	else
	{//生成に失敗した場合
		return NULL;
	}

	return pLife;
}
//-------------------------------------------------------
//ライフ設定処理
//-------------------------------------------------------
void CLife::LifeMove(CPlayer3D *pPlayer)
{
	if (m_apObject != NULL)
	{
		CObject::TYPE type;  //種類

		//種類を取得
		type = pPlayer->GetType();
		int typetex = m_apObject->GetTypeTex();

		//種類がプレイヤーの場合
		if (type == CObject::TYPE_PLAYER)
		{
			int m_lifePlayer = pPlayer->GetLife();  //プレイヤーのライフ取得

			if (m_lifePlayer == 400)
			{
				if (typetex == TYPE_LIFEGAUGE)
				{
					m_apObject->Uninit();
				}

				//---------------------------------------------------------------
				//ライフの生成
				//---------------------------------------------------------------
				CLife::Create(D3DXVECTOR3(117.0f, 650.0f, 0.0f), D3DXVECTOR3(240.0f, 30.0f, 0.0f), D3DXVECTOR3(0.8f, 0.0f, 0.0f), CLife::TYPE_LIFEGAUGE);
			}

			if (m_lifePlayer == 300)
			{
				if (typetex == TYPE_LIFEGAUGE)
				{
					m_apObject->Uninit();
				}

				//---------------------------------------------------------------
				//ライフの生成
				//---------------------------------------------------------------
				CLife::Create(D3DXVECTOR3(117.0f, 650.0f, 0.0f), D3DXVECTOR3(180.0f, 30.0f, 0.0f), D3DXVECTOR3(0.6f, 0.0f, 0.0f), CLife::TYPE_LIFEGAUGE);
			}

			if (m_lifePlayer == 200)
			{
				if (typetex == TYPE_LIFEGAUGE)
				{
					m_apObject->Uninit();
				}

				//---------------------------------------------------------------
				//ライフの生成
				//---------------------------------------------------------------
				CLife::Create(D3DXVECTOR3(117.0f, 650.0f, 0.0f), D3DXVECTOR3(120.0f, 30.0f, 0.0f), D3DXVECTOR3(0.4f, 0.0f, 0.0f), CLife::TYPE_LIFEGAUGE);
			}

			if (m_lifePlayer == 100)
			{
				if (typetex == TYPE_LIFEGAUGE)
				{
					m_apObject->Uninit();
				}

				//---------------------------------------------------------------
				//ライフの生成
				//---------------------------------------------------------------
				CLife::Create(D3DXVECTOR3(117.0f, 650.0f, 0.0f), D3DXVECTOR3(60.0f, 30.0f, 0.0f), D3DXVECTOR3(0.2f, 0.0f, 0.0f), CLife::TYPE_LIFEGAUGE);
			}

			if (m_lifePlayer == 0)
			{
				if (typetex == TYPE_LIFEGAUGE)
				{
					m_apObject->Uninit();
				}

				//---------------------------------------------------------------
				//ライフの生成
				//---------------------------------------------------------------
				CLife::Create(D3DXVECTOR3(117.0f, 650.0f, 0.0f), D3DXVECTOR3(0.0f, 30.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CLife::TYPE_LIFEGAUGE);
			}
		}
	}
}