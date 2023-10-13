//=============================================================================
//
// 弾の処理(3D) [bullet3D.cpp]
// Author 若木 一真
//
//=============================================================================
#include "bullet3D.h"
#include "manager.h"
#include "explosion.h"

//マクロ定義
#define LIFE_ENEMY	 (150)    //寿命
#define LIFE_PLAYER	 (80)     //寿命
#define TEXSIZE_X	 (40.0f)  //サイズX
#define TEXSIZE_Y	 (10.0f)  //サイズY
#define TEXSIZE_Z	 (10.0f)  //サイズZ
#define ENEMY_SPEED  (5.0f)   //敵の弾の速度

//静的メンバ変数
CBullet3D *CBullet3D::m_apObject[MAX_BULLET] = {};

//-------------------------------------------------------
//コンストラクタ
//-------------------------------------------------------
CBullet3D::CBullet3D()
{
	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
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
CBullet3D::~CBullet3D()
{

}
//-------------------------------------------------------
//初期化処理
//-------------------------------------------------------
HRESULT CBullet3D::Init(void)
{
	//デバイスの取得
	//LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CModel *pModel = CManager::GetModel();  //モデルのポインタ

	//モデルを宣言
	m_nIdxModel[BULLETTYPE_PLAYER] = pModel->Regist("data\\MODEL\\kunai001.x");    //クナイ
	//m_nIdxModel[BULLETTYPE_ENEMY] = pModel->Regist("data\\MODEL\\hane001.x");      //敵の弾

	//オブジェクトXの初期化処理
	CObjectX::Init();

	//値のクリア
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_nCntHit = 0;

	//弾のサイズ
	SetSize(D3DXVECTOR3(10.0f, 10.0f, 0.0f));

	////種類の設定
	CObject::SetType(TYPE_BULLET);

	return (S_OK);
}
//-------------------------------------------------------
//終了処理
//-------------------------------------------------------
void CBullet3D::Uninit(void)
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
void CBullet3D::Update(void)
{
	D3DXVECTOR3 m_pos = GetPosition();  //位置の取得
	D3DXVECTOR3 m_move = GetMove();	    //移動量の取得

	int nID = m_nID;

	//位置の更新
	m_pos += m_move;

	//位置の設定
	SetPosition(m_pos);

	//エフェクトの生成
	//CEffect::Create(GetPosition() - D3DXVECTOR3(50.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(255, 0, 0, 255));

	//ブロックとの当たり判定
	//if (CollisionBlock(m_pos))
	{

	}

	m_nLife++;
	m_nCntHit++;

	//弾のタイプが敵の時
	if (m_type == BULLETTYPE_ENEMY)
	{
		//弾が消えるまでのカウント
		if (m_nLife >= LIFE_ENEMY)
		{
			//削除処理
			Uninit();

			m_nLife = 0;  //0に戻す
		}
	}

	//弾のタイプがプレイヤーの時
	if (m_type == BULLETTYPE_PLAYER)
	{
		//弾が消えるまでのカウント
		if (m_nLife >= LIFE_PLAYER)
		{
			//削除処理
			Uninit();

			m_nLife = 0;  //0に戻す
		}
	}

	if (m_apObject[nID] != NULL)
	{
		//弾のタイプが敵の時
		if (m_type == BULLETTYPE_ENEMY)
		{
			if (m_nCntHit >= 10)
			{
				//プレイヤーとの当たり判定
				if (CPlayer3D::CollisionBullet(this) == true)
				{
					//自分の終了処理
					Uninit();

					m_nCntHit = 0;  //カウントを0にリセットする
				}
			}
		}

		//弾のタイプがプレイヤーの時
		if (m_type == BULLETTYPE_PLAYER)
		{
			//敵との当たり判定
			if (CEnemy3D::CollisionBullet(this) == true)
			{
				//自分の終了処理
				Uninit();
			}
		}
	}
}
//-------------------------------------------------------
//描画処理
//-------------------------------------------------------
void CBullet3D::Draw(void)
{
	//オブジェクトの描画処理
	CObjectX::Draw();
}
//-------------------------------------------------------
//生成処理
//-------------------------------------------------------
CBullet3D *CBullet3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR3 scale, int type)
{
	CBullet3D *pBullet = NULL;;

	//弾の生成
	pBullet = new CBullet3D;

	if (pBullet != NULL)
	{
		//初期化処理
		pBullet->Init();
	}

	else
	{//生成に失敗した場合
		return NULL;
	}

	//弾の位置の設定
	pBullet->SetPosition(pos);

	//弾の移動量の設定
	pBullet->SetMove(move);

	//弾の向きの設定
	pBullet->SetRotation(rot);

	//弾の拡大率の設定
	pBullet->SetScale(scale);

	//弾のサイズ
	pBullet->SetSize(D3DXVECTOR3(TEXSIZE_X, TEXSIZE_Y, TEXSIZE_Z));

	//弾の種類の設定
	pBullet->SetTypeBullet(type);

	//
	if (pBullet->m_type == BULLETTYPE_ENEMY)
	{
		//弾の移動量の設定
		pBullet->SetMove(move * ENEMY_SPEED);
	}

	//nCount分回す
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		//nCountと選択されたモデルタイプが一致した時
		if (nCount == type)
		{
			//モデルの割り当て
			pBullet->BindModel(pBullet->m_nIdxModel[nCount]);
		}
	}

	return pBullet;
}
//-------------------------------------------------------
//ブロックとの当たり判定
//-------------------------------------------------------
bool CBullet3D::CollisionBlock(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 m_pos = GetPosition();  //位置の取得
	D3DXVECTOR3 m_size = GetScale();     //サイズの取得
	D3DXVECTOR3 posBlock;
	D3DXVECTOR3 sizeBlock;

	//PRIORITY分回す
	for (int nCntPriority = 0; nCntPriority < PRIORITY; nCntPriority++)
	{
		//MAX_BULLET分回す
		for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
		{
			CObject *pObj;  //オブジェクトクラスのポインタ

			//オブジェクトを取得
			pObj = GetObject(nCntPriority, nCntObj);

			//pObjがNULLじゃなかった時
			if (pObj != NULL)
			{
				CObject::TYPE type;  //種類

				//種類を取得
				type = pObj->GetType();

				//種類が敵の場合
				if (type == CObject::TYPE_BLOCK)
				{
					//ブロックの位置の取得
					posBlock = pObj->GetPosition();

					//ブロックのサイズの取得
					sizeBlock = pObj->GetScale();

					//ブロックと重なった時
					if (m_pos.x - m_size.x <= posBlock.x + sizeBlock.x
						&&  m_pos.x + m_size.x >= posBlock.x - sizeBlock.x
						&&  m_pos.z - m_size.z <= posBlock.z + sizeBlock.z
						&&  m_pos.z + m_size.z >= posBlock.z - sizeBlock.z)
					{
						//爆発の生成
						CExplosion::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z));

						//ブロックの終了処理
						//pObj->Uninit();

						//自分の終了処理
						Uninit();

						return TRUE;
					}
				}
			}
		}
	}

	return FALSE;
}
//-------------------------------------------------------
//弾の種類タイプの設定
//-------------------------------------------------------
void CBullet3D::SetTypeBullet(int Type)
{
	m_type = Type;
}