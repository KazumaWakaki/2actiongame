//=============================================================================
//
// 敵処理 [enemy3D.cpp]
// Author 若木 一真
//
//=============================================================================
#include "enemy3D.h"
#include "manager.h"
#include "game.h"
#include "explosion.h"
#include "bullet3D.h"
#include "effect.h"
#include "block3D.h"

//マクロ定義
#define TEXSIZE_X	(80.0f)   //サイズX
#define TEXSIZE_Y	(80.0f)   //サイズY
#define TEXSIZE_Z	(80.0f)   //サイズZ
#define BULLETSPEED (10.0f)   //敵の弾スピード
#define BESTPOS     (700.0f)  //敵の動いてくる最近距離
#define MOVEKOUMORI (0.5f)    //コウモリの動くスピード

//静的メンバ変数
CEnemy3D *CEnemy3D::m_apObject[MAX_ENEMY] = {};

//-------------------------------------------------------
//コンストラクタ
//-------------------------------------------------------
CEnemy3D::CEnemy3D()
{
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
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
CEnemy3D::~CEnemy3D()
{

}
//-------------------------------------------------------
//敵の初期化処理
//-------------------------------------------------------
HRESULT CEnemy3D::Init()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CModel *pModel = CManager::GetModel();  //モデルのポインタ

	//モデルを宣言
	m_nIdxModel[TYPE_KOUMORI] = pModel->Regist("data\\MODEL\\koumori001.x");  //コウモリ
	m_nIdxModel[TYPE_OOKAMI] = pModel->Regist("data\\MODEL\\ookami001.x");     //狼

	//オブジェクトXの初期化処理
	CObjectX::Init();

	//値を初期化
	m_Life = 0;
	m_nCntHit = 0;
	m_nCounterMove = 0;
	m_nCounterBullet = 0;

	SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //サイズ初期化
	SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //移動量初期化

	SetEnemyMoveState(ENEMYMOVE_RIGHT);  //初期化
	CObject::SetType(TYPE_ENEMY);  //種類の設定
	CObjectX::SetState(CObject::STATE_NORMAL, 0);  //状態管理設定

	return (S_OK);
}
//-------------------------------------------------------
//敵の終了処理
//-------------------------------------------------------
void CEnemy3D::Uninit(void)
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
//敵の更新処理
//-------------------------------------------------------
void CEnemy3D::Update(void)
{
	D3DXVECTOR3 m_pos = GetPosition();  //位置の取得
	D3DXVECTOR3 m_move = GetMove();   //移動量の取得
	D3DXVECTOR3 m_rot = GetRotation();  //向きの取得
	D3DXVECTOR3 posPlayer;

	SetPositionOld(m_pos);  //過去の位置設定

	//状態管理設定
	CObject::UpdateState();

	//状態管理
	UpdateEnemyState();

	//移動設定
	//MoveEnemy();

	m_nCntHit++;

	//位置の更新
	m_pos += m_move;

	//移動量を更新
	m_move.x += (0.0f - m_move.x) * ENEMYSPEEDUP;
	m_move.y += (0.0f - m_move.y) * ENEMYSPEEDUP;

	//床判定
	if (m_pos.y < 0)
	{
		m_pos.y = 0;
		m_move.y = 0;
	}

	SetPosition(m_pos);  //位置の設定
	SetMove(m_move);  //移動量の設定
	SetRotation(m_rot);  //向きの設定

	//当たり判定
	CBlock3D::CollisionEnemy(this);

	if (m_nCntHit >= 60)
	{
		//プレイヤーと敵との当たり判定
		if (CPlayer3D::CollisionEnemy(this))
		{
			m_nCntHit = 0;  //カウントを0にリセットする
		}
	}
}
//-------------------------------------------------------
//敵の描画処理
//-------------------------------------------------------
void CEnemy3D::Draw(void)
{
	//オブジェクトXの描画処理
	CObjectX::Draw();
}
//-------------------------------------------------------
//生成処理
//-------------------------------------------------------
CEnemy3D *CEnemy3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 size, int SetTypeTex, int Life)
{
	CEnemy3D *pEnemy3D;

	//敵の生成
	pEnemy3D = new CEnemy3D;

	if (pEnemy3D != NULL)
	{
		//初期化処理
		pEnemy3D->Init();

		//位置の設定
		pEnemy3D->SetPosition(pos);

		//位置の設定
		pEnemy3D->SetPositionOld(pos);

		//移動量の設定
		pEnemy3D->SetMove(move);

		//向きの設定
		pEnemy3D->SetRotation(rot);

		//拡大率の設定
		pEnemy3D->SetScale(scale);

		//サイズ
		pEnemy3D->SetSize(size);

		//テクスチャタイプ
		pEnemy3D->SetTypeTex(SetTypeTex);

		//ライフの設定
		pEnemy3D->SetLife(Life);

		//nCount分回す
		for (int nCount = 0; nCount < TYPE_MAX; nCount++)
		{
			//nCountと選択されたモデルタイプが一致した時
			if (nCount == SetTypeTex)
			{
				//テクスチャの割り当て
				pEnemy3D->BindModel(pEnemy3D->m_nIdxModel[nCount]);
			}
		}
	}

	else
	{//生成に失敗した場合
		return NULL;
	}

	return pEnemy3D;
}
//-------------------------------------------------------
//プレイヤーの近接攻撃
//-------------------------------------------------------
void CEnemy3D::PlayerAttack(CPlayer3D *pPlayer)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//ゲームパッドの取得
	CInputPad *pInputPad;
	pInputPad = CManager::GetInputPad();

	//サウンドの取得
	CSound *pSound;
	pSound = CManager::GetSound();

	CObject::TYPE type;  //種類

	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		//m_apObject[nCnt]がNULLじゃなかった時
		if (m_apObject[nCnt] != NULL)
		{
			//種類を取得
			type = pPlayer->GetType();

			//種類がプレイヤーの場合
			if (type == CObject::TYPE_PLAYER)
			{
				D3DXVECTOR3 m_pos = m_apObject[nCnt]->GetPosition();  //位置の取得
				D3DXVECTOR3 m_rot = m_apObject[nCnt]->GetRotation();  //向きの取得
				D3DXVECTOR3 m_size = m_apObject[nCnt]->GetScale();    //拡大率の取得
				D3DXVECTOR3 posPlayer = pPlayer->GetPosition();       //プレイヤーの位置の取得
				D3DXVECTOR3 rotPlayer = pPlayer->GetRotation();       //プレイヤーの向きの取得
				D3DXVECTOR3 sizePlayer = pPlayer->GetScale();         //プレイヤーの拡大率の取得
				int BattleState = pPlayer->GetAttackState();

				if (BattleState == pPlayer->BATTLESTATE_PROXIMITY)
				{
					if (pInputKeyboard->GetTrigger(DIK_V) == true || pInputPad->GetTrigger(CInputPad::BUTTON_RB, 0))
					{
						//プレイヤーが右向きの時
						if (rotPlayer.y == (-D3DX_PI * 0.5f))
						{
							//エフェクトの生成
							CEffect::Create(D3DXVECTOR3(posPlayer.x + 60.0f, posPlayer.y + 30.0f, posPlayer.z), D3DXVECTOR3(50.0f, 50.0f, 0.0f));

							//敵と重なった時
							if (m_pos.x + m_size.x >= posPlayer.x - sizePlayer.x
								&&  m_pos.x - m_size.x - 20.0f <= posPlayer.x + sizePlayer.x + 100.0f
								&&  m_pos.y + m_size.y + 80.0f >= posPlayer.y - sizePlayer.y
								&&  m_pos.y - m_size.y <= posPlayer.y + sizePlayer.y)
							{
								//敵が右向きの時
								if (m_rot.y == (-D3DX_PI * 0.5f))
								{
									m_pos.x -= 100.0f;
								}

								//敵が左向きの時
								else if (m_rot.y == (D3DX_PI * 0.5f))
								{
									m_pos.x += 100.0f;
								}

								m_apObject[nCnt]->SetPosition(m_pos);

								//敵のヒット処理
								HitEnemy(200, nCnt);
							}
						}

						//プレイヤーが左向きの時
						else if (rotPlayer.y == (D3DX_PI * 0.5f))
						{
							//エフェクトの生成
							CEffect::Create(D3DXVECTOR3(posPlayer.x - 60.0f, posPlayer.y + 30.0f, posPlayer.z), D3DXVECTOR3(50.0f, 50.0f, 0.0f));

							//敵と重なった時
							if (m_pos.x + m_size.x + 20.0f >= posPlayer.x - sizePlayer.x - 100.0f
								&&  m_pos.x - m_size.x <= posPlayer.x + sizePlayer.x
								&&  m_pos.y + m_size.y + 80.0f >= posPlayer.y - sizePlayer.y
								&&  m_pos.y - m_size.y <= posPlayer.y + sizePlayer.y)
							{
								//敵が右向きの時
								if (m_rot.y == (-D3DX_PI * 0.5f))
								{
									m_pos.x -= 100.0f;
								}

								//敵が左向きの時
								else if (m_rot.y == (D3DX_PI * 0.5f))
								{
									m_pos.x += 100.0f;
								}

								m_apObject[nCnt]->SetPosition(m_pos);

								//敵のヒット処理
								HitEnemy(200, nCnt);
							}
						}

						//SEの再生
						//pSound->PlaySound(SOUND_LABEL_SE_MELEE);
					}
				}
			}
		}
	}
}
//-------------------------------------------------------
//敵の移動
//-------------------------------------------------------
void CEnemy3D::MoveEnemy(CPlayer3D *pPlayer)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		//m_apObject[nCnt]がNULLじゃなかった時
		if (m_apObject[nCnt] != NULL)
		{
			D3DXVECTOR3 m_pos = m_apObject[nCnt]->GetPosition();  //位置の取得
			D3DXVECTOR3 m_posOld = m_apObject[nCnt]->GetPositionOld();  //過去の位置の取得
			D3DXVECTOR3 m_move = m_apObject[nCnt]->GetMove();  //移動量の取得
			D3DXVECTOR3 m_rot = m_apObject[nCnt]->GetRotation();  //向きの取得
			D3DXVECTOR3 m_size = m_apObject[nCnt]->GetSize();  //サイズの取得
			D3DXVECTOR3 posPlayer = pPlayer->GetPosition();  //プレイヤーの位置の取得
			D3DXVECTOR3 posOldPlayer = pPlayer->GetPositionOld();  //プレイヤーの過去の位置取得
			D3DXVECTOR3 sizePlayer = pPlayer->GetSize();  //プレイヤーのサイズ取得
			int typetex = m_apObject[nCnt]->GetTypeTex();

			CObject::TYPE type;  //種類

			//種類を取得
			type = pPlayer->GetType();

			//種類がプレイヤーの場合
			if (type == CObject::TYPE_PLAYER)
			{
				if (typetex == TYPE_KOUMORI)
				{
					if (m_apObject[nCnt]->m_nCounterMove < 50)
					{
						//左に動かす
						m_move.x = -MOVEKOUMORI;
					}

					if (m_apObject[nCnt]->m_nCounterMove > 50)
					{
						//右に動かす
						m_move.x = MOVEKOUMORI;
					}

					if (m_apObject[nCnt]->m_nCounterMove < 25)
					{
						//上に動かす
						m_move.y = MOVEKOUMORI;
					}

					else if (m_apObject[nCnt]->m_nCounterMove < 50)
					{
						//下に動かす
						m_move.y = -MOVEKOUMORI;
					}

					else if (m_apObject[nCnt]->m_nCounterMove < 75)
					{
						//下に動かす
						m_move.y = -MOVEKOUMORI;
					}

					else if (m_apObject[nCnt]->m_nCounterMove < 100)
					{
						//上に動かす
						m_move.y = MOVEKOUMORI;
					}

					if (m_apObject[nCnt]->m_nCounterMove > 100)
					{
						m_apObject[nCnt]->m_nCounterMove = 0;
					}
				}

				if (m_pos.z - m_size.z <= posPlayer.z + sizePlayer.z + 50.0f &&
					m_pos.z + m_size.z >= posPlayer.z - sizePlayer.z - 50.0f)
				{
					//プレイヤーより右にいる時
					if (m_pos.x  > posPlayer.x + 20.0f
						&&  m_pos.x - BESTPOS < posPlayer.x)
					{
						m_rot.y = (D3DX_PI * 0.5f);

						if (typetex == TYPE_OOKAMI)
						{
							//プレイヤーが敵と同じぐらいの高さにいるとき
							//if (m_pos.y + 20.0f >= posPlayer.y)
							{
								m_move.x = -1.0f;
								//m_apObject[nCnt]->SetEnemyMoveState(ENEMYMOVE_LEFT);
							}
						}

						if (typetex == TYPE_KOUMORI)
						{
							//コウモリの弾
							if (m_apObject[nCnt]->m_nCounterBullet >= 130)
							{
								//弾発射
								CBullet3D::Create(m_apObject[nCnt]->GetPosition(), D3DXVECTOR3(-sinf(m_rot.z), -cosf(m_rot.z), 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXVECTOR3(0.8f, 0.8f, 0.8f), CBullet3D::BULLETTYPE_ENEMY);

								m_apObject[nCnt]->m_nCounterBullet = 0;  //リセット
							}
						}
					}

					//プレイヤーより左にいる時
					if (m_pos.x < posPlayer.x)
					{
						m_rot.y = (-D3DX_PI * 0.5f);

						if (typetex == TYPE_OOKAMI)
						{
							m_move.x = 1.0f;

							//m_apObject[nCnt]->SetEnemyMoveState(ENEMYMOVE_RIGHT);
						}

						if (typetex == TYPE_KOUMORI)
						{
							//コウモリの弾
							if (m_apObject[nCnt]->m_nCounterBullet >= 130)
							{
								//弾発射
								CBullet3D::Create(m_apObject[nCnt]->GetPosition(), D3DXVECTOR3(-sinf(m_rot.z), -cosf(m_rot.z), 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f), D3DXVECTOR3(0.8f, 0.8f, 0.8f), CBullet3D::BULLETTYPE_ENEMY);

								m_apObject[nCnt]->m_nCounterBullet = 0;  //リセット
							}
						}
					}
				}
			}

			if (typetex == TYPE_OOKAMI)
			{
				//重力を加える
				m_move.y -= 3.0f;
			}

			if (typetex == TYPE_KOUMORI)
			{
				float fAngle = atan2f(m_pos.y - posOldPlayer.y, posOldPlayer.x - m_pos.x);

				m_rot.z = fAngle - D3DX_PI * 0.5f;

				m_apObject[nCnt]->SetRotation(m_rot);
			}

			//位置の更新
			m_pos += m_move;

			//移動量を更新
			m_move.x += (0.0f - m_move.x) * ENEMYSPEEDUP;
			m_move.y += (0.0f - m_move.y) * ENEMYSPEEDUP;

			//動きのカウンター
			m_apObject[nCnt]->m_nCounterMove++;

			//弾のカウンター
			m_apObject[nCnt]->m_nCounterBullet++;

			//位置の設定
			m_apObject[nCnt]->SetPosition(m_pos);

			//過去の位置の設定
			m_apObject[nCnt]->SetPositionOld(m_posOld);

			//移動量の設定
			m_apObject[nCnt]->SetMove(m_move);

			//向きの設定
			m_apObject[nCnt]->SetRotation(m_rot);
		}
	}
}
//-------------------------------------------------------
//状態管理設定
//-------------------------------------------------------
void CEnemy3D::UpdateEnemyState(void)
{
	switch (m_state)
	{
	case ENEMYSTATE_NORMAL:
		break;

	case ENEMYSTATE_DAMAGE:

		for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
		{
			//m_apObject[nCnt]がNULLじゃなかった時
			if (m_apObject[nCnt] != NULL)
			{
				D3DXVECTOR3 m_pos = m_apObject[nCnt]->GetPosition();  //位置の取得
				D3DXVECTOR3 m_move = m_apObject[nCnt]->GetMove();	  //移動量の取得

				//値を設定
				m_apObject[nCnt]->SetPosition(m_pos);
				m_apObject[nCnt]->SetMove(m_move);
			}
		}

		m_nCounterState--;

		if (m_nCounterState <= 0)
		{
			m_state = ENEMYSTATE_NORMAL;

			break;
		}
	}
}
//-------------------------------------------------------
//状態管理設定
//-------------------------------------------------------
void CEnemy3D::MoveEnemy(void)
{
	switch (m_movestate)
	{
	case ENEMYMOVE_RIGHT:  //右に移動する

		for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
		{
			//m_apObject[nCnt]がNULLじゃなかった時
			if (m_apObject[nCnt] != NULL)
			{
				D3DXVECTOR3 m_move = m_apObject[nCnt]->GetMove();	  //移動量の取得
				m_move.x = 1.0f;
				m_apObject[nCnt]->SetMove(m_move);
			}
		}

		break;

	case ENEMYMOVE_LEFT:  //左に移動する

		for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
		{
			//m_apObject[nCnt]がNULLじゃなかった時
			if (m_apObject[nCnt] != NULL)
			{
				D3DXVECTOR3 m_move = m_apObject[nCnt]->GetMove();	  //移動量の取得
				m_move.x = -1.0f;
				m_apObject[nCnt]->SetMove(m_move);
			}
		}

		break;

	case ENEMYMOVE_AUTO:  //自動的に移動する

		for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
		{
			//m_apObject[nCnt]がNULLじゃなかった時
			if (m_apObject[nCnt] != NULL)
			{
				D3DXVECTOR3 m_move = m_apObject[nCnt]->GetMove();	  //移動量の取得
				D3DXVECTOR3 m_rot = m_apObject[nCnt]->GetRotation();  //向きの取得

				//プレイヤーが左向きの時
				if (m_rot.y == (D3DX_PI * 0.5f))
				{
					m_move.x = -1.0f;
				}

				//プレイヤーが右向きの時
				if (m_rot.y == (-D3DX_PI * 0.5f))
				{
					m_move.x = 1.0f;
				}

				m_apObject[nCnt]->SetMove(m_move);   //移動量の設定
			}
		}

		break;
	}
}
//-------------------------------------------------------
//敵のヒット処理
//-------------------------------------------------------
void CEnemy3D::HitEnemy(int nDamage, int nCnt)
{
	//サウンドの取得
	CSound *pSound;
	pSound = CManager::GetSound();

	if (m_apObject[nCnt] != NULL)
	{
		m_apObject[nCnt]->m_Life -= nDamage;
		int typetex = m_apObject[nCnt]->GetTypeTex();
		D3DXVECTOR3 m_pos = m_apObject[nCnt]->GetPosition();  //位置の取得
		D3DXVECTOR3 m_rot = m_apObject[nCnt]->GetRotation();  //向きの取得

		if (m_apObject[nCnt]->m_Life <= 0)
		{
			if (typetex == TYPE_KOUMORI)
			{
				//爆発の生成
				CExplosion::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z));

				//死亡状態
				m_apObject[nCnt]->SetState(CObject::STATE_DEATH, 0);

				//自分の終了処理
				m_apObject[nCnt]->Uninit();

				//ゲームの状態の設定
				CGame::SetGameState(CGame::GAMESTATE_END, 60);
			}

			else if (typetex == TYPE_OOKAMI)
			{
				//爆発の生成
				CExplosion::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z));

				//死亡状態
				m_apObject[nCnt]->SetState(CObject::STATE_DEATH, 0);

				//自分の終了処理
				m_apObject[nCnt]->Uninit();
			}

			//SEの再生
			//pSound->PlaySound(SOUND_LABEL_SE_EXPLOSION);
		}

		else
		{
			m_apObject[nCnt]->SetState(CObject::STATE_DAMAGE, 20);  //ダメージ状態
			m_apObject[nCnt]->SetEnemyState(ENEMYSTATE_DAMAGE, 60);  //ダメージ状態

			//SEの再生
			//pSound->PlaySound(SOUND_LABEL_SE_DAMAGE);
		}
	}
}
//-------------------------------------------------------
//弾との当たり判定
//-------------------------------------------------------
bool CEnemy3D::CollisionBullet(CBullet3D *pBullet)
{
	CObject::TYPE type;  //種類

	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		if (m_apObject[nCnt] != NULL)
		{
			int typetex = m_apObject[nCnt]->GetTypeTex();
			type = pBullet->GetType();  //種類を取得

			//種類が弾の場合
			if (type == CObject::TYPE_BULLET)
			{
				D3DXVECTOR3 m_pos = m_apObject[nCnt]->GetPosition();  //位置の取得
				D3DXVECTOR3 m_size = m_apObject[nCnt]->GetScale();  //サイズの取得
				D3DXVECTOR3 posBullet = pBullet->GetPosition();  //弾の位置取得
				D3DXVECTOR3 sizeBullet = pBullet->GetScale();  //弾のサイズ取得

				//コウモリの時
				if (typetex == TYPE_KOUMORI)
				{
					//敵と重なった時
					if (m_pos.x + m_size.x >= posBullet.x - sizeBullet.x - 40.0f
						&&  m_pos.x - m_size.x <= posBullet.x + sizeBullet.x + 40.0f
						&&  m_pos.y + m_size.y + 40.0f >= posBullet.y - sizeBullet.y
						&&  m_pos.y - m_size.y - 40.0f <= posBullet.y + sizeBullet.y)
					{
						//敵のヒット処理
						CEnemy3D::HitEnemy(100, nCnt);

						return TRUE;
					}
				}

				//狼の時
				else if (typetex == TYPE_OOKAMI)
				{
					//敵と重なった時
					if (m_pos.x + m_size.x >= posBullet.x - sizeBullet.x - 40.0f
						&&  m_pos.x - m_size.x <= posBullet.x + sizeBullet.x + 40.0f
						&&  m_pos.y + m_size.y + 80.0f >= posBullet.y - sizeBullet.y
						&&  m_pos.y - m_size.y <= posBullet.y + sizeBullet.y)
					{
						//敵のヒット処理
						CEnemy3D::HitEnemy(100, nCnt);

						return TRUE;
					}
				}
			}
		}
	}

	return FALSE;
}
//-------------------------------------------------------
//プレイヤーが突進攻撃状態の時の敵との当たり判定
//-------------------------------------------------------
bool CEnemy3D::AttackCollision(CPlayer3D *pPlayer)
{
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		if (m_apObject[nCnt] != NULL)
		{
			D3DXVECTOR3 m_pos = m_apObject[nCnt]->GetPosition();  //位置の取得
			D3DXVECTOR3 m_size = m_apObject[nCnt]->GetScale();  //拡大率の取得
			CObject::TYPE type;  //種類
			int typetex;

			//種類を取得
			type = pPlayer->GetType();

			//種類が敵の場合
			if (type == CObject::TYPE_PLAYER)
			{
				D3DXVECTOR3 posPlayer = pPlayer->GetPosition();  //プレイヤーの位置の取得
				D3DXVECTOR3 sizePlayer = pPlayer->GetScale();  //プレイヤーの拡大率の取得
				typetex = m_apObject[nCnt]->GetTypeTex();  //敵の種類

				//敵がコウモリの時
				if (typetex == CEnemy3D::TYPE_KOUMORI)
				{
					//敵と重なった時
					if (m_pos.x - m_size.x <= posPlayer.x + sizePlayer.x + 50.0f
						&&  m_pos.x + m_size.x >= posPlayer.x - sizePlayer.x - 50.0f
						&&  m_pos.y - m_size.y <= posPlayer.y + sizePlayer.y + 50.0f
						&&  m_pos.y + m_size.y >= posPlayer.y - sizePlayer.y - 50.0f
						&&  m_pos.z - m_size.z <= posPlayer.z + sizePlayer.z + 50.0f
						&&  m_pos.z + m_size.z >= posPlayer.z - sizePlayer.z - 50.0f)
					{
						//敵のヒット処理
						CEnemy3D::HitEnemy(200, nCnt);

						return TRUE;
					}
				}

				//敵が狼の時
				else if (typetex == CEnemy3D::TYPE_OOKAMI)
				{
					//敵と重なった時
					if (m_pos.x - m_size.x <= posPlayer.x + sizePlayer.x + 50.0f
						&&  m_pos.x + m_size.x >= posPlayer.x - sizePlayer.x - 50.0f
						&&  m_pos.y - m_size.y <= posPlayer.y + sizePlayer.y + 50.0f
						&&  m_pos.y + m_size.y >= posPlayer.y - sizePlayer.y - 50.0f
						&&  m_pos.z - m_size.z <= posPlayer.z + sizePlayer.z + 50.0f
						&&  m_pos.z + m_size.z >= posPlayer.z - sizePlayer.z - 50.0f)
					{
						//敵のヒット処理
						CEnemy3D::HitEnemy(200, nCnt);

						return TRUE;
					}
				}
			}
		}
	}

	return FALSE;
}
//-------------------------------------------------------
//体力の設定処理
//-------------------------------------------------------
void CEnemy3D::SetLife(int Life)
{
	m_Life = Life;
}
//-------------------------------------------------------
//状態管理設定
//-------------------------------------------------------
void CEnemy3D::SetEnemyState(ENEMYSTATE state, int nCounterState)
{
	m_state = state;
	m_nCounterState = nCounterState;
}
//-------------------------------------------------------
//移動管理設定
//-------------------------------------------------------
void CEnemy3D::SetEnemyMoveState(ENEMYMOVE statemove)
{
	m_movestate = statemove;
}