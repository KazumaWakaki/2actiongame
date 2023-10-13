//=============================================================================
//
// アタックゲージ処理 [life.cpp]
// Author：若木一真
//
//=============================================================================
#include "manager.h"
#include "attackgage.h"
#include "player3D.h"

//静的メンバ変数
CAttackGage *CAttackGage::m_apObject = NULL;

//-------------------------------------------------------
//コンストラクタ
//-------------------------------------------------------
CAttackGage::CAttackGage()
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apObject == NULL)
		{
			m_apObject = this;

			m_nID = nCnt;

			break;
		}
	}
}
//-------------------------------------------------------
//デストラクタ
//-------------------------------------------------------
CAttackGage::~CAttackGage()
{

}
//-------------------------------------------------------
//アタックゲージの初期化処理
//-------------------------------------------------------
HRESULT CAttackGage::Init(void)
{
	CTexture *pTexture = CManager::GetTexture();

	m_nIdxTexture[TYPE_ATTACKFRAME] = pTexture->Regist("data\\texture\\attackgagecover001.png");
	m_nIdxTexture[TYPE_ATTACKGAUGE] = pTexture->Regist("data\\texture\\attackgage001.png");

	//オブジェクト2Dの初期化処理
	CObject2D::Init();

	//種類の設定
	CObject::SetType(TYPE_ATTACKGAGE);

	//初期化
	SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //位置
	SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //サイズ
	m_Gage = TYPE_GAUGE_2;

	return (S_OK);
}
//-------------------------------------------------------
//アタックゲージの終了処理
//-------------------------------------------------------
void CAttackGage::Uninit(void)
{
	//オブジェクト2Dの終了処理
	CObject2D::Uninit();
}
//-------------------------------------------------------
//アタックゲージの更新処理
//-------------------------------------------------------
void CAttackGage::Update(void)
{
	CPlayer3D::AttackGageMove(this);  //アタックゲージの移動量
}
//-------------------------------------------------------
//アタックゲージの描画処理
//-------------------------------------------------------
void CAttackGage::Draw(void)
{
	//オブジェクト2Dの描画処理
	CObject2D::Draw();
}
//-------------------------------------------------------
//生成処理
//-------------------------------------------------------
CAttackGage *CAttackGage::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 scale, int SetTypeTex)
{
	CAttackGage *pAttackgage = NULL;

	//アタックゲージの生成
	pAttackgage = new CAttackGage;

	//pAttackgageがNULLじゃなかった時
	if (pAttackgage != NULL)
	{
		//初期化処理
		pAttackgage->Init();

		//位置の設定
		pAttackgage->SetPosition(pos);

		//サイズ
		pAttackgage->SetSize(size);

		//スケール
		pAttackgage->SetScale(scale);

		//テクスチャタイプ
		pAttackgage->SetTypeTex(SetTypeTex);

		//頂点情報の生成
		pAttackgage->SetVtxUI();

		//nCount分回す
		for (int nCount = 0; nCount < TYPE_MAX; nCount++)
		{
			//nCountと選択されたモデルタイプが一致した時
			if (nCount == SetTypeTex)
			{
				//テクスチャの割り当て
				pAttackgage->BindTexture(pAttackgage->m_nIdxTexture[nCount]);
			}
		}
	}

	else
	{//生成に失敗した場合
		return NULL;
	}

	return pAttackgage;
}
//-------------------------------------------------------
//アタックゲージの設定処理
//-------------------------------------------------------
void CAttackGage::SetAttackGage(int Gage)
{
	m_Gage = Gage;
}