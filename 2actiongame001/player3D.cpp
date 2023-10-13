//=============================================================================
//
// プレイヤー3D処理 [player3D.cpp]
// Author 若木 一真
//
//=============================================================================
#include "player3D.h"
#include "manager.h"
#include "bullet3D.h"
#include "explosion.h"
#include "game.h"
#include "modelset.h"
#include "block3D.h"
#include "life.h"
#include "attackgage.h"

//マクロ定義
#define PLAYERSPEED (3.0f)  //移動時のスピード
#define PLAYERSPEEDUP (0.2f)  //移動量更新時のスピード
#define PLAYERJAMPSPEED (3.0f)  //ジャンプ時の落下スピード
#define JAMPCNT (10)  //重力がかかるまでのカウント
#define BULLETSPEED (7.0f)  //プレイヤーの弾スピード
#define ATTACKCNT (10)  //アタックカウント
#define ATTACKGAGE (100)  //アタックゲージ

//静的メンバ変数
CPlayer3D *CPlayer3D::m_apObject = NULL;

//-------------------------------------------------------
//コンストラクタ
//-------------------------------------------------------
CPlayer3D::CPlayer3D()
{
	if (m_apObject == NULL)
	{
		m_apObject = this;
	}
}
//-------------------------------------------------------
//デストラクタ
//-------------------------------------------------------
CPlayer3D::~CPlayer3D()
{

}
//-------------------------------------------------------
//初期化処理
//-------------------------------------------------------
HRESULT CPlayer3D::Init()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	CModel *pModel = CManager::GetModel();  //モデルのポインタ

	//モデルを宣言
	m_nIdxModel = pModel->Regist("data\\MODEL\\rob001.x");  //プレイヤー

	//オブジェクトXの初期化処理
	CObjectX::Init();

	//種類の設定
	CObject::SetType(TYPE_PLAYER);

	//状態管理設定
	CObjectX::SetState(CObject::STATE_NORMAL, 0);

	//ライフの設定
	m_Life = 500;

	//値を初期化
	m_nCnt = 0;
	m_nCntState = 0;
	m_nCntDown = 0;
	m_nCntAttack = 0;
	m_AttackGage = ATTACKGAGE;
	m_jump = PLAYERJUMP_GROUND;
	m_AttackState = ATTACKSTATE_NONE;
	m_BattleState = BATTLESTATE_PROXIMITY;
	m_WarpState = WARPSTATE_FALSE;
	m_StartPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return (S_OK);
}
//-------------------------------------------------------
//終了処理
//-------------------------------------------------------
void CPlayer3D::Uninit()
{
	//オブジェクトXの終了処理
	CObjectX::Uninit();

	m_apObject = NULL;
}
//-------------------------------------------------------
//更新処理
//-------------------------------------------------------
void CPlayer3D::Update()
{
	D3DXVECTOR3 m_pos = GetPosition();  //位置の取得
	D3DXVECTOR3 m_move = GetMove();	//移動量の取得
	D3DXVECTOR3 m_rot = GetRotation();  //向きの取得
	D3DXVECTOR3 m_size = GetSize();        //サイズの取得

	//キーボードの取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//ゲームパッドの取得
	CInputPad *pInputPad;
	pInputPad = CManager::GetInputPad();

	//サウンドの取得
	CSound *pSound;
	pSound = CManager::GetSound();

	SetPositionOld(m_pos);  //過去の位置設定

	//状態管理設定
	CObject::UpdateState();

	//プレイヤーの近接攻撃
	CEnemy3D::PlayerAttack(this);

	//敵の移動
	CEnemy3D::MoveEnemy(this);

	m_nCntState = 0;

	if (m_AttackState == ATTACKSTATE_NONE)
	{
		///////////////////////////////////////////
		//プレイヤーキーボード操作
		///////////////////////////////////////////
		//Dキーが押されている時
		if (pInputKeyboard->GetPress(DIK_D) == true || pInputPad->CInputPad::GetJoyStickLX(0) > 0)
		{
			//Dキーが押された
			m_move.x += sinf(D3DX_PI * 0.5f) * PLAYERSPEED;
			m_rot.y = (-D3DX_PI * 0.5f);
		}

		//Aキーが押されている時
		else if (pInputKeyboard->GetPress(DIK_A) == true || pInputPad->CInputPad::GetJoyStickLX(0) < 0)
		{
			//Aキーが押された
			m_move.x += sinf(D3DX_PI * -0.5f) * PLAYERSPEED;
			m_rot.y = (D3DX_PI * 0.5f);	
		}

		//ジャンプ
		if (pInputKeyboard->GetTrigger(DIK_SPACE) == true && m_jump == PLAYERJUMP_GROUND   //SPACEが押された時
			|| pInputPad->GetTrigger(CInputPad::BUTTON_A, 0) && m_jump == PLAYERJUMP_GROUND)  //Aボタンが押された時
		{
			m_move.y = 60.0f;     //上に移動する
			//m_move.y -= 3.0f;     //重力を加える
			m_pos.y -= m_move.y;  //慣性

			m_jump = PLAYERJUMP_SKY;  //ジャンプしている状態にする

			m_nCntDown = 0;

			//SEの再生
			//pSound->PlaySound(SOUND_LABEL_SE_JAMP);
		}
	}

	//近接状態の時
	if (m_BattleState == BATTLESTATE_PROXIMITY  &&
		m_Attack == false)
	{
		if (m_AttackState == ATTACKSTATE_NONE)
		{
			if (m_AttackGage >= 25)
			{
				if (pInputKeyboard->GetTrigger(DIK_B) == true)  //Bを押したとき
				{
					m_AttackGage -= 25;  //ゲージを25減らす
					m_AttackState = ATTACKSTATE_RUSHATTACK;  //突進攻撃状態に切り替え
					m_nCntAttack = ATTACKCNT;  //アタックカウントを設定
					m_StartPos = m_pos;  //位置を保存
					m_Attack = true;
				}
			}
		}
	}

	if (m_nCntDown > JAMPCNT)
	{
		//重力を加える
		m_move.y -= PLAYERJAMPSPEED;
	}

	if (m_nCnt >= 10)
	{
		m_AttackGage++;  //アタックゲージを+1する
		m_nCnt = 0;  //初期化
	}

	//アタックゲージが100よりも多くなったら
	if (m_AttackGage >= ATTACKGAGE)
	{
		m_AttackGage = ATTACKGAGE;  //100に固定
	}

	//インクリメント
	m_nCnt++;
	m_nCntDown++;
	m_nCntBullet++;

	//位置の更新
	m_pos += m_move;

	//移動量を更新
	m_move.x += (0.0f - m_move.x) * PLAYERSPEEDUP;
	m_move.y += (0.0f - m_move.y) * PLAYERSPEEDUP;
	m_move.z += (0.0f - m_move.z) * PLAYERSPEEDUP;

	///////////////////////////////////////////
	//画面外に出た時
	///////////////////////////////////////////
	////右壁
	//if (m_pos.x >= SCREEN_WIDTH - 100)
	//{
	//	m_pos.x = SCREEN_WIDTH - 100;
	//}

	//左壁
	if (m_pos.x <= -570)
	{
		m_pos.x = -570;
	}

	//床判定
	if (m_pos.y < 0)
	{
		m_pos.y = 0;
		m_move.y = 0;

		m_Attack = false;
		m_jump = PLAYERJUMP_GROUND;  //ジャンプしてない状態にする
	}

	SetPosition(m_pos);  //位置の設定
	SetMove(m_move);  //移動量の設定
	SetRotation(m_rot);  //向きの設定
	SetLife(m_Life);  //ライフの設定
	SetAttackState(m_AttackState);  //戦闘状態の設定
	SetAttackGage(m_AttackGage);  //アタックゲージの設定
	CLife::LifeMove(this);  //ライフの移動量

	//攻撃状態の更新
	AttackState();

	CBlock3D::CollisionPlayer(this);  //ブロックとの当たり判定
	CModelSet::ModelCollision(this);  //モデルとの当たり判定

	//-------------------------------------------------------
	//プレイヤーのデバック表示
	//-------------------------------------------------------
	CManager::GetDebugProc()->Print("プレイヤー位置 [%f, %f, %f]\n", m_pos.x, m_pos.y, m_pos.z);
	CManager::GetDebugProc()->Print("プレイヤー移動量 [%f, %f, %f]\n", m_move.x, m_move.y, m_move.z);
	CManager::GetDebugProc()->Print("プレイヤー向き [%f, %f, %f]\n", m_rot.x, m_rot.y, m_rot.z);
	CManager::GetDebugProc()->Print("プレイヤー体力 [%d]\n", m_Life);
	CManager::GetDebugProc()->Print("プレイヤーのアタックゲージ [%d]\n", m_AttackGage);
}
//-------------------------------------------------------
//描画処理
//-------------------------------------------------------
void CPlayer3D::Draw()
{
	//オブジェクトXの描画処理
	CObjectX::Draw();
}
//-------------------------------------------------------
//生成処理
//-------------------------------------------------------
CPlayer3D *CPlayer3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 size)
{
	CPlayer3D *pPlayer3D = NULL;

	//プレイヤーの生成
	pPlayer3D = new CPlayer3D;

	if (pPlayer3D != NULL)
	{
		//初期化処理
		pPlayer3D->Init();
	}

	else
	{//生成に失敗した場合
		return NULL;
	}

	//位置の設定
	pPlayer3D->SetPosition(pos);

	//向きの設定
	pPlayer3D->SetRotation(rot);

	//拡大率の設定
	pPlayer3D->SetScale(scale);

	//サイズ設定
	pPlayer3D->SetSize(size);

	//モデルの割り当て
	pPlayer3D->BindModel(pPlayer3D->m_nIdxModel);

	//---------------------------------------------------------------
	//ライフの生成
	//---------------------------------------------------------------
	CLife::Create(D3DXVECTOR3(117.0f, 650.0f, 0.0f), D3DXVECTOR3(300.0f, 30.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), CLife::TYPE_LIFEGAUGE);
	CLife::Create(D3DXVECTOR3(10.0f, 650.0f, 0.0f), D3DXVECTOR3(410.0f, 40.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), CLife::TYPE_LIFEFRAME);

	//---------------------------------------------------------------
	//アタックゲージの生成
	//---------------------------------------------------------------
	CAttackGage::Create(D3DXVECTOR3(600.0f, 650.0f, 0.0f), D3DXVECTOR3(410.0f, 35.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), CAttackGage::TYPE_ATTACKFRAME);
	CAttackGage::Create(D3DXVECTOR3(625.0f, 647.0f, 0.0f), D3DXVECTOR3(360.0f, 18.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), CAttackGage::TYPE_ATTACKGAUGE);

	return pPlayer3D;
}
//-------------------------------------------------------
//攻撃状態
//-------------------------------------------------------
void CPlayer3D::AttackState(void)
{
	D3DXVECTOR3 m_pos = GetPosition();  //位置の取得
	D3DXVECTOR3 m_move = GetMove();   //移動量の取得
	D3DXVECTOR3 m_rot = GetRotation();  //向きの取得
	D3DXVECTOR3 m_startpos = GetStartPos();  //スタート位置の取得

    //キーボードの取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//ゲームパッドの取得
	CInputPad *pInputPad;
	pInputPad = CManager::GetInputPad();

	switch (m_AttackState)
	{
	case ATTACKSTATE_NONE:  //通常状態

		//if (m_move.x >= 1.0f)
		//{
		//	if (m_rot.y <= (-D3DX_PI * 0.5f))
		//	{
		//		m_rot.y = (-D3DX_PI * 0.5f);

		//		SetRotation(m_rot);
		//	}
		//}

		break;

	case ATTACKSTATE_MELEEATTACK:  //近接攻撃状態

		break;

	case	ATTACKSTATE_RUSHATTACK:  //突進攻撃状態
		
		//プレイヤーが右向きの時
		if (m_rot.y == (-D3DX_PI * 0.5f))
		{
			if (m_jump == PLAYERJUMP_GROUND)
			{
				m_move = D3DXVECTOR3(30.0f, 0.0f, 0.0f);  //攻撃スピード
			}

			else if (m_jump == PLAYERJUMP_SKY)
			{
				//Dキーが押されている時
				if (pInputKeyboard->GetPress(DIK_D) == true || pInputPad->CInputPad::GetJoyStickLX(0) > 0)
				{
					if (pInputKeyboard->GetPress(DIK_W) == true)       //Aキーが押されてるときにWキーが押された
					{
						//右上移動
						m_move = D3DXVECTOR3(30.0f, 30.0f, 0.0f);  //攻撃スピード
					}

					else if (pInputKeyboard->GetPress(DIK_S) == true)  //Aキーが押されてるときにSキーが押された
					{
						//右下移動
						m_move = D3DXVECTOR3(30.0f, -30.0f, 0.0f);  //攻撃スピード
					}

					else
					{
						//Dキーが押された
						m_move = D3DXVECTOR3(30.0f, 0.0f, 0.0f);  //攻撃スピード
					}
				}

				//Wキーが押されている時
				else if (pInputKeyboard->GetPress(DIK_W) == true)
				{
					//上方向へ移動
					m_move = D3DXVECTOR3(0.0f, 30.0f, 0.0f);  //攻撃スピード
				}

				//Sキーが押されている時
				else if (pInputKeyboard->GetPress(DIK_S) == true)
				{
					//下方向へ移動
					m_move = D3DXVECTOR3(0.0f, -30.0f, 0.0f);  //攻撃スピード
				}

				//何も押されてないとき
				else
				{
					//右に進む
					m_move = D3DXVECTOR3(30.0f, 0.0f, 0.0f);  //攻撃スピード
				}
			}

			if (m_nCntAttack < 0)
			{
				m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				m_nCntAttack = 0;
				m_AttackState = ATTACKSTATE_NONE;
			}

			//SEの再生
			//pSound->PlaySound(SOUND_LABEL_SE_FIRING);
		}

		//プレイヤーが左向きの時
		if (m_rot.y == (D3DX_PI * 0.5f))
		{
			if (m_jump == PLAYERJUMP_GROUND)
			{
				m_move = D3DXVECTOR3(-30.0f, 0.0f, 0.0f);  //攻撃スピード
			}

			else if (m_jump == PLAYERJUMP_SKY)
			{
				//Aキーが押されている時
				if (pInputKeyboard->GetPress(DIK_A) == true || pInputPad->CInputPad::GetJoyStickLX(0) < 0)
				{
					if (pInputKeyboard->GetPress(DIK_W) == true)       //Aキーが押されてるときにWキーが押された
					{
						//左上移動
						m_move = D3DXVECTOR3(-30.0f, 30.0f, 0.0f);  //攻撃スピード
					}

					else if (pInputKeyboard->GetPress(DIK_S) == true)  //Aキーが押されてるときにSキーが押された
					{
						//左下移動
						m_move = D3DXVECTOR3(-30.0f, -30.0f, 0.0f);  //攻撃スピード
					}

					else
					{
						//Aキーが押された
						m_move = D3DXVECTOR3(-30.0f, 0.0f, 0.0f);  //攻撃スピード
					}
				}

				//Wキーが押されている時
				else if (pInputKeyboard->GetPress(DIK_W) == true)
				{
					//上方向へ移動
					m_move = D3DXVECTOR3(0.0f, 30.0f, 0.0f);  //攻撃スピード
				}

				//Sキーが押されている時
				else if (pInputKeyboard->GetPress(DIK_S) == true)
				{
					//下方向へ移動
					m_move = D3DXVECTOR3(0.0f, -30.0f, 0.0f);  //攻撃スピード
				}

				//何も押されてないとき
				else
				{
					//左に進む
					m_move = D3DXVECTOR3(-30.0f, 0.0f, 0.0f);  //攻撃スピード
				}
			}

			if (m_nCntAttack < 0)
			{
				m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				m_nCntAttack = 0;
				m_AttackState = ATTACKSTATE_NONE;
			}

			//SEの再生
			//pSound->PlaySound(SOUND_LABEL_SE_FIRING);
		}

		//敵との当たり判定
		CEnemy3D::AttackCollision(this);

		m_nCntAttack--;
		SetMove(m_move);

		break;
	}
}
//-------------------------------------------------------
//プレイヤーのヒット処理
//-------------------------------------------------------
void CPlayer3D::HitPlayer(int nDamage)
{
	//サウンドの取得
	CSound *pSound;
	pSound = CManager::GetSound();

	if (m_apObject != NULL)
	{
		m_apObject->m_Life -= nDamage;

		D3DXVECTOR3 m_pos = m_apObject->GetPosition();  //位置の取得
		D3DXVECTOR3 m_rot = m_apObject->GetRotation();  //向きの取得

		if (m_apObject->m_Life <= 0)
		{
			//爆発の生成
			CExplosion::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z));

			m_apObject->SetState(CObject::STATE_DEATH, 0);  //死亡状態

			//自分の終了処理
			m_apObject->Uninit();

			//ゲームの状態の設定
			CGame::SetGameState(CGame::GAMESTATE_END, 60);

			//SEの再生
			//pSound->PlaySound(SOUND_LABEL_SE_DEATH);
		}
		else
		{
			//プレイヤーが右向きの時
			if (m_rot.y == (-D3DX_PI * 0.5f))
			{
				m_pos.x -= 150.0f;
			}

			//プレイヤーが左向きの時
			else if (m_rot.y == (D3DX_PI * 0.5f))
			{
				m_pos.x += 150.0f;
			}

			m_apObject->SetPosition(m_pos);
			m_apObject->SetState(CObject::STATE_DAMAGE, 20);  //ダメージ状態

			//SEの再生
			//pSound->PlaySound(SOUND_LABEL_SE_DAMAGE);
		}
	}
}
//-------------------------------------------------------
//敵との当たり判定
//-------------------------------------------------------
bool CPlayer3D::CollisionEnemy(CEnemy3D *pEnemy)
{	
	if (m_apObject != NULL)
	{
		D3DXVECTOR3 m_pos = m_apObject->GetPosition();  //位置の取得
		D3DXVECTOR3 m_size = m_apObject->GetScale();    //拡大率の取得
		CObject::TYPE type;  //種類
		int typetex = 0;  //敵の種類用
		int BattleState = m_apObject->GetAttackState();  //プレイヤーの攻撃状態取得
		type = pEnemy->GetType();   //種類を取得

		//種類が敵の場合
		if (type == CObject::TYPE_ENEMY)
		{
			D3DXVECTOR3 posEnemy = pEnemy->GetPosition();  //敵の位置の取得
			D3DXVECTOR3 sizeEnemy = pEnemy->GetScale();  //敵の拡大率の取得
			typetex = pEnemy->GetTypeTex();  //敵の種類

			//敵がコウモリの時
			if (typetex == CEnemy3D::TYPE_KOUMORI)
			{
				//敵と重なった時
				if (m_pos.x - m_size.x <= posEnemy.x + sizeEnemy.x + 50.0f
					&&  m_pos.x + m_size.x >= posEnemy.x - sizeEnemy.x - 50.0f
					&&  m_pos.y - m_size.y <= posEnemy.y + sizeEnemy.y + 50.0f
					&&  m_pos.y + m_size.y >= posEnemy.y - sizeEnemy.y - 50.0f)
				{
					if (BattleState != CPlayer3D::ATTACKSTATE_RUSHATTACK)
					{
						//プレイヤーのヒット処理
						HitPlayer(100);
					}

					return TRUE;
				}
			}

			//敵が狼の時
			else if (typetex == CEnemy3D::TYPE_OOKAMI)
			{
				//敵と重なった時
				if (m_pos.x - m_size.x <= posEnemy.x + sizeEnemy.x + 40.0f
					&&  m_pos.x + m_size.x >= posEnemy.x - sizeEnemy.x - 40.0f
					&&  m_pos.y - m_size.y <= posEnemy.y + sizeEnemy.y + 50.0f
					&&  m_pos.y + m_size.y >= posEnemy.y - sizeEnemy.y - 50.0f
					&&  m_pos.z - m_size.z <= posEnemy.z + sizeEnemy.z + 50.0f
					&&  m_pos.z + m_size.z >= posEnemy.z - sizeEnemy.z - 50.0f)
				{
					//突進攻撃状態じゃない時
					if (BattleState != CPlayer3D::ATTACKSTATE_RUSHATTACK)
					{
						//プレイヤーのヒット処理
						HitPlayer(100);
					}

					return TRUE;
				}
			}
		}
	}
	
	return FALSE;
}
//-------------------------------------------------------
//弾との当たり判定
//-------------------------------------------------------
bool CPlayer3D::CollisionBullet(CBullet3D *pBullet)
{
	D3DXVECTOR3 posBullet = pBullet->GetPosition();  //弾の位置取得
	D3DXVECTOR3 sizeBullet = pBullet->GetScale();    //弾のサイズ取得
	CObject::TYPE type;  //種類

	//種類を取得
	type = pBullet->GetType();

	if (m_apObject != NULL)
	{
		//種類が弾の場合
		if (type == CObject::TYPE_BULLET)
		{
			D3DXVECTOR3 m_pos = m_apObject->GetPosition();  //位置の取得
			D3DXVECTOR3 m_size = m_apObject->GetScale();  //サイズの取得

			//プレイヤーと重なった時
			if (m_pos.x + m_size.x >= posBullet.x - sizeBullet.x - 40.0f
			&&  m_pos.x - m_size.x <= posBullet.x + sizeBullet.x + 40.0f
			&&  m_pos.y + m_size.y + 80.0f >= posBullet.y - sizeBullet.y
			&&  m_pos.y - m_size.y <= posBullet.y + sizeBullet.y)
			{
				//プレイヤーのヒット処理
				CPlayer3D::HitPlayer(100);

				return TRUE;
			}
		}
	}

	return FALSE;
}
//-------------------------------------------------------
//アタックゲージ設定処理
//-------------------------------------------------------
void CPlayer3D::AttackGageMove(CAttackGage *pAttackGage)
{
	if (m_apObject != NULL)
	{
		CObject::TYPE type;  //種類

		//種類を取得
		type = pAttackGage->GetType();
		int typetex = pAttackGage->GetTypeTex();

		//タイプがアタックゲージの場合
		if (type == CObject::TYPE_ATTACKGAGE)
		{
			int m_AttackGagePlayer = m_apObject->GetAttackGage();  //アタックゲージ取得
			int Gage = pAttackGage->GetGage();

			if (m_AttackGagePlayer >= 100 &&
				Gage != CAttackGage::TYPE_GAUGE_1)
			{
				if (typetex == CAttackGage::TYPE_ATTACKGAUGE)
				{
					pAttackGage->Uninit();
				}

				//---------------------------------------------------------------
				//アタックゲージの生成
				//---------------------------------------------------------------
				CAttackGage::Create(D3DXVECTOR3(625.0f, 647.0f, 0.0f), D3DXVECTOR3(360.0f, 18.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), CAttackGage::TYPE_ATTACKGAUGE);

				Gage = CAttackGage::TYPE_GAUGE_1;
			}

			if (m_AttackGagePlayer >= 75 &&
				m_AttackGagePlayer < 100 &&
				Gage != CAttackGage::TYPE_GAUGE_2)
			{
				if (typetex == CAttackGage::TYPE_ATTACKGAUGE)
				{
					pAttackGage->Uninit();
				}

				//---------------------------------------------------------------
				//アタックゲージの生成
				//---------------------------------------------------------------
				CAttackGage::Create(D3DXVECTOR3(625.0f, 647.0f, 0.0f), D3DXVECTOR3(270.0f, 18.0f, 0.0f), D3DXVECTOR3(0.75f, 0.0f, 0.0f), CAttackGage::TYPE_ATTACKGAUGE);

				Gage = CAttackGage::TYPE_GAUGE_2;
			}

			if (m_AttackGagePlayer >= 50 &&
				m_AttackGagePlayer < 75 &&
				Gage != CAttackGage::TYPE_GAUGE_3)
			{
				if (typetex == CAttackGage::TYPE_ATTACKGAUGE)
				{
					pAttackGage->Uninit();
				}

				//---------------------------------------------------------------
				//アタックゲージの生成
				//---------------------------------------------------------------
				CAttackGage::Create(D3DXVECTOR3(625.0f, 647.0f, 0.0f), D3DXVECTOR3(180.0f, 18.0f, 0.0f), D3DXVECTOR3(0.5f, 0.0f, 0.0f), CAttackGage::TYPE_ATTACKGAUGE);

				Gage = CAttackGage::TYPE_GAUGE_3;
			}

			if (m_AttackGagePlayer >= 25 &&
				m_AttackGagePlayer < 50 &&
				Gage != CAttackGage::TYPE_GAUGE_4)
			{
				if (typetex == CAttackGage::TYPE_ATTACKGAUGE)
				{
					pAttackGage->Uninit();
				}

				//---------------------------------------------------------------
				//アタックゲージの生成
				//---------------------------------------------------------------
				CAttackGage::Create(D3DXVECTOR3(625.0f, 647.0f, 0.0f), D3DXVECTOR3(90.0f, 18.0f, 0.0f), D3DXVECTOR3(0.25f, 0.0f, 0.0f), CAttackGage::TYPE_ATTACKGAUGE);

				Gage = CAttackGage::TYPE_GAUGE_4;
			}

			if (m_AttackGagePlayer >= 0 &&
				m_AttackGagePlayer < 25 &&
				Gage != CAttackGage::TYPE_GAUGE_5)
			{
				if (typetex == CAttackGage::TYPE_ATTACKGAUGE)
				{
					pAttackGage->Uninit();
				}

				//---------------------------------------------------------------
				//アタックゲージの生成
				//---------------------------------------------------------------
				CAttackGage::Create(D3DXVECTOR3(625.0f, 647.0f, 0.0f), D3DXVECTOR3(0.0f, 18.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CAttackGage::TYPE_ATTACKGAUGE);

				Gage = CAttackGage::TYPE_GAUGE_5;
			}

			pAttackGage->SetAttackGage(Gage);
		}
	}
}
//-------------------------------------------------------
//体力の設定処理
//-------------------------------------------------------
void CPlayer3D::SetPlayerJump(PLAYERJAMP Jamp)
{
	m_jump = Jamp;
}
//-------------------------------------------------------
//体力の設定処理
//-------------------------------------------------------
void CPlayer3D::SetLife(int Life)
{
	m_Life = Life;
}
//-------------------------------------------------------
//攻撃の設定処理
//-------------------------------------------------------
void CPlayer3D::SetAttack(bool Attack)
{
	m_Attack = Attack;
}
//-------------------------------------------------------
//攻撃状態の設定処理
//-------------------------------------------------------
void CPlayer3D::SetAttackState(ATTACKSTATE AttackState)
{
	m_AttackState = AttackState;
}
//-------------------------------------------------------
//アタックゲージの設定処理
//-------------------------------------------------------
void CPlayer3D::SetAttackGage(int AttackGage)
{
	m_AttackGage = AttackGage;
}