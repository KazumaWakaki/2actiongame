//=============================================================================
//
// ブロック3D処理 [block3D.cpp]
// Author 若木 一真
//
//=============================================================================
#include "block3D.h"
#include "manager.h"
#include "player3D.h"
#include "enemy3D.h"

//マクロ定義
#define COLLISION_COR	(10.0f) //横の当たり判定 (プレイヤー)
#define CORRECTION	(6.0f)  //横の当たり判定補正

//静的メンバ変数
CBlock3D *CBlock3D::m_apObject[MAX_BLOCK] = {};

//-------------------------------------------------------
//コンストラクタ
//-------------------------------------------------------
CBlock3D::CBlock3D()
{
	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
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
CBlock3D::~CBlock3D()
{

}
//-------------------------------------------------------
//初期化処理
//-------------------------------------------------------
HRESULT CBlock3D::Init()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CModel *pModel = CManager::GetModel();  //モデルのポインタ

	m_nIdxModel = pModel->Regist("data\\MODEL\\block000.x");  //ベンチ

	//モデルの初期化処理
	CObjectX::Init();

	//種類の設定
	CObject::SetType(TYPE_BLOCK);

	return (S_OK);
}
//-------------------------------------------------------
//終了処理
//-------------------------------------------------------
void CBlock3D::Uninit()
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
void CBlock3D::Update()
{
	D3DXVECTOR3 m_pos = GetPosition();  //位置の取得
	D3DXVECTOR3 m_posOld = GetPositionOld();  //位置の取得
	D3DXVECTOR3 m_move = GetMove();  //移動量の取得
	D3DXVECTOR3 m_rot = GetRotation();   //向きの取得
	D3DXVECTOR3 m_scale = GetScale();  //拡大率の取得
	D3DXVECTOR3 m_size = GetSize();  //サイズの取得

	//位置の更新
	m_pos += m_move;

	//移動量を更新
	m_move.x += (0.0f - m_move.x) * 0.1f;
	m_move.y += (0.0f - m_move.y) * 0.1f;
}
//-------------------------------------------------------
//描画処理
//-------------------------------------------------------
void CBlock3D::Draw()
{
	//オブジェクトXの描画処理
	CObjectX::Draw();
}
//-------------------------------------------------------
//生成処理
//-------------------------------------------------------
CBlock3D *CBlock3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 size)
{
	CBlock3D *pBlock3D = NULL;

	//ブロックの生成
	pBlock3D = new CBlock3D;

	if (pBlock3D != NULL)
	{
		//初期化処理
		pBlock3D->Init();
	}

	else
	{//生成に失敗した場合
		return NULL;
	}

	//ブロックの位置の設定
	pBlock3D->SetPosition(pos);

	//ブロックの向きの設定
	pBlock3D->SetRotation(rot);

	//ブロックの拡大率の設定
	pBlock3D->SetScale(scale);

	//ブロックのサイズ設定
	pBlock3D->SetSize(size);

	//モデルの割り当て
	pBlock3D->BindModel(pBlock3D->m_nIdxModel);

	return pBlock3D;
}
//-------------------------------------------------------
//プレイヤーとの当たり判定
//-------------------------------------------------------
bool CBlock3D::CollisionPlayer(CPlayer3D *pPlayer)
{
	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
	{
		//m_apObject[nCnt]がNULLじゃなかった時
		if (m_apObject[nCnt] != NULL)
		{
			D3DXVECTOR3 m_pos = m_apObject[nCnt]->GetPosition();  //ブロックの位置の取得
			D3DXVECTOR3 m_move = m_apObject[nCnt]->GetMove();  //移動量の取得
			D3DXVECTOR3 m_size = m_apObject[nCnt]->GetScale();  //ブロックの拡大率の取得
			CObject::TYPE type;  //種類

			//種類を取得
			type = pPlayer->GetType();

			//種類がプレイヤーの場合
			if (type == CObject::TYPE_PLAYER)
			{
				D3DXVECTOR3 posPlayer = pPlayer->GetPosition();  //プレイヤーの位置
				D3DXVECTOR3 posOldPlayer = pPlayer->GetPositionOld();  //プレイヤーの過去の位置
				D3DXVECTOR3 movePlayer = pPlayer->GetMove();  //プレイヤーの移動量
				D3DXVECTOR3 sizePlayer = pPlayer->GetScale();  //プレイヤーの拡大率

				///////////////////////////////////
				//横の判定
				///////////////////////////////////
				//敵と重なった時
				if (m_pos.z - m_size.z <= posPlayer.z + sizePlayer.z
					&&  m_pos.z + m_size.z >= posPlayer.z - sizePlayer.z)
				{
					if (m_pos.y - m_size.y * COLLISION_COR - 10.0f < posPlayer.y + sizePlayer.y * COLLISION_COR + 10.0f
						&&  m_pos.y + m_size.y * COLLISION_COR + 10.0f > posPlayer.y - sizePlayer.y * COLLISION_COR - 10.0f)
					{
						if (m_pos.x - m_size.x * COLLISION_COR - CORRECTION > posOldPlayer.x + sizePlayer.x * COLLISION_COR
							&&  m_pos.x - m_size.x * COLLISION_COR - CORRECTION < posPlayer.x + sizePlayer.x * COLLISION_COR)
						{//ひだり。
							posPlayer.x = m_pos.x - m_size.x * COLLISION_COR - 10.0f;  //ブロックの左から抜けない
							movePlayer.x = 0.0f;  //プレイヤーの移動量を0にする
						}

						if (m_pos.x + m_size.x * COLLISION_COR + CORRECTION < posOldPlayer.x - sizePlayer.x * COLLISION_COR
							&&  m_pos.x + m_size.x * COLLISION_COR + CORRECTION > posPlayer.x - sizePlayer.x * COLLISION_COR)
						{//ミギー。
							posPlayer.x = m_pos.x + m_size.x * COLLISION_COR + 10.0f;  //ブロックの右から抜けない
							movePlayer.x = 0.0f;  //プレイヤーの移動量を0にする
						}
					}
				}

				///////////////////////////////////
				//縦の判定
				///////////////////////////////////
				if (m_pos.z - m_size.z <= posPlayer.z + sizePlayer.z
					&&  m_pos.z + m_size.z >= posPlayer.z - sizePlayer.z)
				{
					if ((m_pos.x - m_size.x * COLLISION_COR - 2.0f < posPlayer.x + sizePlayer.x * COLLISION_COR + 10.0f
						&& m_pos.x + m_size.x * COLLISION_COR + 2.0f > posPlayer.x - sizePlayer.x * COLLISION_COR - 10.0f))
					{
						if (m_pos.y + m_size.y * COLLISION_COR < posOldPlayer.y - sizePlayer.y * COLLISION_COR - 17.0f
							&&  m_pos.y + m_size.y * COLLISION_COR > posPlayer.y - sizePlayer.y * COLLISION_COR - 17.0f)
						{//上だ。
							posPlayer.y = m_pos.y + m_size.y * COLLISION_COR + 25.0f;  //ブロックの上に立たせる
							movePlayer.y = 0.0f;  //移動量を0にする
							pPlayer->SetAttack(false);
							pPlayer->SetPlayerJump(CPlayer3D::PLAYERJUMP_GROUND);  //プレイヤーを地上状態にする
						}

						if (m_pos.y - m_size.y * COLLISION_COR  > posOldPlayer.y + sizePlayer.y * COLLISION_COR + 60.0f
							&&  m_pos.y - m_size.y * COLLISION_COR  < posPlayer.y + sizePlayer.y * COLLISION_COR + 60.0f)
						{//下
							posPlayer.y = m_pos.y - m_size.y * COLLISION_COR - 80.0f;  //ブロックの下から貫通防ぐ
							movePlayer.y = 0.0f;  //移動量を0にする
						}
					}
				}

				pPlayer->SetPosition(posPlayer);  //プレイヤーの位置の設定
				pPlayer->SetMove(movePlayer);	   //プレイヤーの移動量の設定
			}
		}
	}
	
	return FALSE;
}
//-------------------------------------------------------
//敵との当たり判定
//-------------------------------------------------------
bool CBlock3D::CollisionEnemy(CEnemy3D *pEnemy)
{
	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
	{
		//m_apObject[nCnt]がNULLじゃなかった時
		if (m_apObject[nCnt] != NULL)
		{
			D3DXVECTOR3 m_pos = m_apObject[nCnt]->GetPosition();  //ブロックの位置の取得
			D3DXVECTOR3 m_move = m_apObject[nCnt]->GetMove();  //移動量の取得
			D3DXVECTOR3 m_size = m_apObject[nCnt]->GetScale();  //ブロックのサイズの取得
			CObject::TYPE type;  //種類

			//種類を取得
			type = pEnemy->GetType();

			//種類が敵の場合
			if (type == CObject::TYPE_ENEMY)
			{
				D3DXVECTOR3 posEnemy = pEnemy->GetPosition();        //敵の位置の取得
				D3DXVECTOR3 posOldEnemy = pEnemy->GetPositionOld();  //敵の過去の位置の取得
				D3DXVECTOR3 moveEnemy = pEnemy->GetMove();           //敵の移動量の取得
				D3DXVECTOR3 sizeEnemy = pEnemy->GetScale();          //敵のサイズの取得

				///////////////////////////////////
				//横の判定
				///////////////////////////////////
				if (m_pos.y - m_size.y * COLLISION_COR - 10.0f < posEnemy.y + sizeEnemy.y * COLLISION_COR + 10.0f
					&&  m_pos.y + m_size.y * COLLISION_COR + 10.0f > posEnemy.y - sizeEnemy.y * COLLISION_COR - 10.0f)
				{
					if (m_pos.x - m_size.x * COLLISION_COR - CORRECTION > posOldEnemy.x + sizeEnemy.x * COLLISION_COR + 20.0f
						&&  m_pos.x - m_size.x * COLLISION_COR - CORRECTION < posEnemy.x + sizeEnemy.x * COLLISION_COR + 20.0f)
					{//ひだり。
						posEnemy.x = m_pos.x - m_size.x * COLLISION_COR - 30.0f;  //ブロックの左から抜けない
						moveEnemy.x = 0.0f;  //プレイヤーの移動量を0にする
					}

					if (m_pos.x + m_size.x * COLLISION_COR + CORRECTION < posOldEnemy.x - sizeEnemy.x * COLLISION_COR
						&&  m_pos.x + m_size.x * COLLISION_COR + CORRECTION > posEnemy.x - sizeEnemy.x * COLLISION_COR)
					{//ミギー。
						posEnemy.x = m_pos.x + m_size.x * COLLISION_COR + 10.0f;  //ブロックの右から抜けない
						moveEnemy.x = 0.0f;  //プレイヤーの移動量を0にする
					}
				}

				///////////////////////////////////
				//縦の判定
				///////////////////////////////////
				if ((m_pos.x - m_size.x * COLLISION_COR < posEnemy.x + sizeEnemy.x * COLLISION_COR + 20.0f
					&&   m_pos.x + m_size.x * COLLISION_COR > posEnemy.x - sizeEnemy.x * COLLISION_COR - 20.0f))
				{
					if (m_pos.y + m_size.y * COLLISION_COR < posOldEnemy.y - sizeEnemy.y * COLLISION_COR - 18.0f
						&&  m_pos.y + m_size.y * COLLISION_COR > posEnemy.y - sizeEnemy.y * COLLISION_COR - 18.0f)
					{//上だ。
						posEnemy.y = m_pos.y + m_size.y * COLLISION_COR + 29.0f;  //ブロックの上に立たせる
						moveEnemy.y = 0.0f;  //移動量を0にする
					}

					if (m_pos.y - m_size.y * COLLISION_COR > posOldEnemy.y + sizeEnemy.y * COLLISION_COR
						&&  m_pos.y - m_size.y * COLLISION_COR < posEnemy.y + sizeEnemy.y * COLLISION_COR)
					{//下
						posEnemy.y = m_pos.y - m_size.y * COLLISION_COR - 80.0f;  //ブロックの下から貫通防ぐ
						moveEnemy.y = 0.0f;  //移動量を0にする
					}
				}

				pEnemy->SetPosition(posEnemy);  //敵の位置の設定
				pEnemy->SetMove(moveEnemy);	  //敵の移動量の設定
			}
		}
	}

	return FALSE;
}