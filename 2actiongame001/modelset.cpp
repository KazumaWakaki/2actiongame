//=============================================================================
//
// モデル配置処理 [modelset.cpp]
// Author 若木 一真
//
//=============================================================================
#include "modelset.h"
#include "manager.h"
#include "player3D.h"

//静的メンバ変数
CModelSet *CModelSet::m_apObject[MAX_MODEL] = {};

//-------------------------------------------------------
//コンストラクタ
//-------------------------------------------------------
CModelSet::CModelSet()
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (m_apObject[nCnt] == NULL)
		{
			m_apObject[nCnt] = this;

			m_nID = nCnt;

			break;
		}
	}
}
//-------------------------------------------------------
//デストラクタ
//-------------------------------------------------------
CModelSet::~CModelSet()
{

}
//-------------------------------------------------------
//初期化処理
//-------------------------------------------------------
HRESULT CModelSet::Init()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CModel *pModel = CManager::GetModel();  //モデルのポインタ

	m_nIdxModel[TYPE_GATE_1] = pModel->Regist("data\\MODEL\\gate001.x");  //ゲート1
	m_nIdxModel[TYPE_GATE_2] = pModel->Regist("data\\MODEL\\gate001.x");  //ゲート2
	m_nIdxModel[TYPE_GATE_3] = pModel->Regist("data\\MODEL\\gate001.x");  //ゲート3
	m_nIdxModel[TYPE_KOIN] = pModel->Regist("data\\MODEL\\gate001.x");  //コイン

	//モデルの初期化処理
	CObjectX::Init();

	//種類の設定
	CObject::SetType(TYPE_MODEL);

	return (S_OK);
}
//-------------------------------------------------------
//終了処理
//-------------------------------------------------------
void CModelSet::Uninit()
{
	int nID = m_nID;

	//オブジェクトの削除処理
	CObjectX::Uninit();

	if (m_apObject[nID] != NULL)
	{
		m_apObject[nID] = NULL;
	}
}
//-------------------------------------------------------
//更新処理
//-------------------------------------------------------
void CModelSet::Update()
{

}
//-------------------------------------------------------
//描画処理
//-------------------------------------------------------
void CModelSet::Draw()
{
	//モデルXの描画処理
	CObjectX::Draw();
}
//-------------------------------------------------------
//生成処理
//-------------------------------------------------------
CModelSet *CModelSet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 size, int SetTypeTex)
{
	CModelSet *pModelSet = NULL;

	//モデルの生成
	pModelSet = new CModelSet;

	if (pModelSet != NULL)
	{
		//初期化処理
		pModelSet->Init();
	}

	else
	{//生成に失敗した場合
		return NULL;
	}

	pModelSet->SetPosition(pos);  //位置の設定
	pModelSet->SetRotation(rot);  //向きの設定
	pModelSet->SetScale(scale);  //拡大率の設定
	pModelSet->SetSize(size);  //サイズ設定
	pModelSet->SetTypeTex(SetTypeTex);  //テクスチャタイプ設定

	//nCount分回す
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		//nCountと選択されたモデルが一致した時
		if (nCount == SetTypeTex)
		{
			//モデルの割り当て
			pModelSet->BindModel(pModelSet->m_nIdxModel[nCount]);
		}
	}

	return pModelSet;
}
//-------------------------------------------------------
//プレイヤーとの当たり判定処理
//-------------------------------------------------------
bool CModelSet::ModelCollision(CPlayer3D *pPlayer)
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (m_apObject[nCnt] != NULL)
		{
			D3DXVECTOR3 m_pos = m_apObject[nCnt]->GetPosition();  //位置の取得
			D3DXVECTOR3 m_size = m_apObject[nCnt]->GetScale();  //拡大率の取得
			CObject::TYPE type;  //種類
			type = pPlayer->GetType();   //種類を取得

			 //種類がプレイヤーの場合
			if (type == CObject::TYPE_PLAYER)
			{
				D3DXVECTOR3 posPlayer = pPlayer->GetPosition();  //プレイヤーの位置の取得
				D3DXVECTOR3 sizePlayer = pPlayer->GetScale();  //プレイヤーの拡大率の取得
				int typetex = m_apObject[nCnt]->GetTypeTex();  //タイプ判定用

				//ゲート1の時
				if (typetex == TYPE_GATE_1)
				{
					//プレイヤーと重なった時
					if (m_pos.x - m_size.x <= posPlayer.x + sizePlayer.x + 50.0f
					&&  m_pos.x + m_size.x >= posPlayer.x - sizePlayer.x - 50.0f
					&&  m_pos.y - m_size.y <= posPlayer.y + sizePlayer.y + 50.0f
					&&  m_pos.y + m_size.y >= posPlayer.y - sizePlayer.y - 50.0f
					&&  m_pos.z - m_size.z <= posPlayer.z + sizePlayer.z + 200.0f
					&&  m_pos.z + m_size.z >= posPlayer.z - sizePlayer.z - 200.0f)
					{
						posPlayer = D3DXVECTOR3(-400.0f, 0.0f, -2000.0f);

						pPlayer->SetPosition(posPlayer);

						return TRUE;
					}
				}

				//ゲート2の時
				else if (typetex == TYPE_GATE_2)
				{
					//プレイヤーと重なった時
					if (m_pos.x - m_size.x <= posPlayer.x + sizePlayer.x + 50.0f
						&&  m_pos.x + m_size.x >= posPlayer.x - sizePlayer.x - 50.0f
						&&  m_pos.y - m_size.y <= posPlayer.y + sizePlayer.y + 50.0f
						&&  m_pos.y + m_size.y >= posPlayer.y - sizePlayer.y - 50.0f
						&&  m_pos.z - m_size.z <= posPlayer.z + sizePlayer.z + 200.0f
						&&  m_pos.z + m_size.z >= posPlayer.z - sizePlayer.z - 200.0f)
					{
						posPlayer = D3DXVECTOR3(-400.0f, 0.0f, 0.0f);

						pPlayer->SetPosition(posPlayer);

						return TRUE;
					}
				}
			}
		}
	}
	
	return FALSE;
}