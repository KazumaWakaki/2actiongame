//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author 若木 一真
//
//=============================================================================
#include "camera.h"
#include "manager.h"

//マクロ定義
#define MOVE_SPEED		(3.0f)	  //移動スピード
#define ROLL_SPEED		(0.03f)	  //回転スピード
#define CAMERA_MAX_ROT (D3DX_PI * 0.99f)  //視点の限界角
#define CAMERA_MIN_ROT (D3DX_PI * 0.01f)   //視点の限界角

//-------------------------------------------------------
//コンストラクタ
//-------------------------------------------------------
CCamera::CCamera()
{

}
//-------------------------------------------------------
//デストラクタ
//-------------------------------------------------------
CCamera::~CCamera()
{

}
//=======================================================
//カメラの初期化処理
//=======================================================
HRESULT CCamera::Init(void)
{
	//ローカル変数宣言
	D3DXVECTOR3 StartRot;

	//値の初期化
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 1.57f, 0.0f);
	fLengthX = 0.0f;       //X面の視点から注視点までの距離
	fLengthY = 0.0f;       //Y面の視点から注視点までの距離
	fLengthZ = -100.0f;  //Z面の視点から注視点までの距離

	//PRIORITY分回す
	for (int nCntPriority = 0; nCntPriority < PRIORITY; nCntPriority++)
	{
		//MAX_OBJECT分回す
		for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
		{
			CObject *pObj;  //オブジェクトクラスのポインタ

			//オブジェクトを取得
			pObj = CObject::GetObject(nCntPriority, nCntObj);

			//pObjがNULLじゃなかった時
			if (pObj != NULL)
			{
				CObject::TYPE type;  //種類

				//種類を取得
				type = pObj->GetType();

				//種類がプレイヤーの場合
				if (type == CObject::TYPE_PLAYER)
				{
					//初期位置をプレイヤーの後方に設定する
					StartRot = -pObj->GetRotation();

					//目標位置まで移動する
					m_rot.x = StartRot.y + (-D3DX_PI * 0.5f);
				}
			}
		}
	}

	return (S_OK);
}
//=======================================================
//カメラの終了処理
//=======================================================
void CCamera::Uninit(void)
{

}
//=======================================================
//カメラの更新処理
//=======================================================
void CCamera::Update(void)
{
	CInputKeyboard *pInputKeyboard;

	//キーボードの取得
	pInputKeyboard = CManager::GetInputKeyboard();

	//カメラ追従
	MoveCamera();

	//カメラと注視点の距離を算出
	//fLengthX = sqrtf    //X視点
	//(
	//	(m_posV.z - m_posR.z) * (m_posV.z - m_posR.z) + (m_posV.y - m_posR.y) * (m_posV.y - m_posR.y)
	//);

	//fLengthY = sqrtf    //Y視点
	//(
	//	(m_posV.x - m_posR.x) * (m_posV.x - m_posR.x) + (m_posV.z - m_posR.z) * (m_posV.z - m_posR.z)
	//);

	/////////////////////////////////
	//移動
	/////////////////////////////////
	if (pInputKeyboard->GetPress(DIK_Y) == true)         //Yキーが押された (上移動)
	{
		m_posV.y += MOVE_SPEED;
	}

	if (pInputKeyboard->GetPress(DIK_N) == true)         //Nキーが押された (下移動)
	{
		m_posV.y -= MOVE_SPEED;
	}

	/////////////////////////////////
	//視点回転
	/////////////////////////////////
	if (pInputKeyboard->GetPress(DIK_Q) == true)   //Qキーが押された  (正面)
	{
		m_rot.y -= ROLL_SPEED;
	}

	if (pInputKeyboard->GetPress(DIK_E) == true)   //Eキーが押された  (上)
	{
		m_rot.y += ROLL_SPEED;
	}

	if (pInputKeyboard->GetPress(DIK_Z) == true)   //Zキーが押された  (左回り)
	{
		m_rot.y += ROLL_SPEED;

		m_posV.x = m_posR.x + sinf(m_rot.y) * -fLengthY;
		m_posV.z = m_posR.z + cosf(m_rot.y) * -fLengthY;
	}

	if (pInputKeyboard->GetPress(DIK_C) == true)   //Cキーが押された  (右回り)
	{
		m_rot.y -= ROLL_SPEED;

		m_posV.x = m_posR.x + sinf(m_rot.y) * -fLengthY;
		m_posV.z = m_posR.z + cosf(m_rot.y) * -fLengthY;
	}

	//角度の補正
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI;
	}

	//角度の補正
	if (m_rot.z > CAMERA_MAX_ROT)
	{
		m_rot.z = CAMERA_MAX_ROT;
	}
	if (m_rot.z < CAMERA_MIN_ROT)
	{
		m_rot.z = CAMERA_MIN_ROT;
	}
	if (m_rot.x > D3DX_PI)
	{
		m_rot.x = -D3DX_PI;
	}
	if (m_rot.x < -D3DX_PI)
	{
		m_rot.x = D3DX_PI;
	}

	//注視点を相対位置に設定
	//m_posR =
	//{
	//	m_posV.x + sinf(m_rot.y) * fLengthY,
	//	m_posV.y - 20,
	//	m_posV.z + cosf(m_rot.y) * fLengthY
	//};

	//m_posR.x = m_posV.x + sinf(m_rot.y) * fLengthY;
	////m_posR.y = m_posV.y + cosf(m_rot.y) * fLengthY;
	//m_posR.z = m_posV.z + cosf(m_rot.y) * fLengthY;

	m_posV.x = m_posR.x + (sinf(m_rot.z) * cosf(m_rot.x)) * 0.0f;
	m_posV.y = m_posR.y + fLengthY;
	m_posV.z = m_posR.z + fLengthZ;

	SetPosV(m_posV);     //視点の設定
	SetPosR(m_posR);     //注視点の設定
	SetRotation(m_rot);  //向きの設定

	//-------------------------------------------------------
	//カメラのデバック表示
	//-------------------------------------------------------
	CManager::GetDebugProc()->Print("視点 [%f, %f, %f]\n", m_posV.x, m_posV.y, m_posV.z);
	CManager::GetDebugProc()->Print("注視点 [%f, %f, %f]\n", m_posR.x, m_posR.y, m_posR.z);
	CManager::GetDebugProc()->Print("向き [%f, %f, %f]\n", m_rot.x, m_rot.y, m_rot.z);
	CManager::GetDebugProc()->Print("カメラ操作 [Q、E、Z、C、Y、N]\n");
}
//=======================================================
//カメラの設定処理
//=======================================================
void CCamera::SetCamera(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&mtxProjection);

	////プロジェクションマトリックスを作成(透視投影)
	//D3DXMatrixPerspectiveFovLH(&mtxProjection,
	//	D3DXToRadian(45.0f),
	//	(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
	//	1.0f,
	//	1000.0f);

	//プロジェクションマトリックスを設定(平行投影)
	D3DXMatrixOrthoLH(&mtxProjection,
					  (float)SCREEN_WIDTH,
					  (float)SCREEN_HEIGHT,
					  1.0f,
					  1000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&mtxView,
					   &m_posV,
					   &m_posR,
					   &m_vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &mtxView);
}
//=======================================================
//カメラの追従処理
//=======================================================
void CCamera::MoveCamera(void)
{
	//PRIORITY分回す
	for (int nCntPriority = 0; nCntPriority < PRIORITY; nCntPriority++)
	{
		//MAX_OBJECT分回す
		for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
		{
			CObject *pObj;  //オブジェクトクラスのポインタ

			//オブジェクトを取得
			pObj = CObject::GetObject(nCntPriority, nCntObj);

			//pObjがNULLじゃなかった時
			if (pObj != NULL)
			{
				CObject::TYPE type;  //種類

				//種類を取得
				type = pObj->GetType();

				//種類がプレイヤーの場合
				if (type == CObject::TYPE_PLAYER)
				{
					D3DXVECTOR3 posPlayer = pObj->GetPosition();  //プレイヤーの位置の取得
					D3DXVECTOR3 movePlayer = pObj->GetMove();     //プレイヤーの移動量の取得
					D3DXVECTOR3 rotPlayer = pObj->GetRotation();  //プレイヤーの向きの取得

					m_posR += movePlayer;

					//注視点の目標位置を算出
					m_posRDest = D3DXVECTOR3
					(
						posPlayer.x - sinf(rotPlayer.y),
						posPlayer.y + 100.0f,
						posPlayer.z - cosf(rotPlayer.y)
					);

					//注視点を補正
					D3DXVECTOR3 RDeff = D3DXVECTOR3
					(
						m_posRDest.x - m_posR.x,
						m_posRDest.y - m_posR.y,
						m_posRDest.z - m_posR.z
					);

					//慣性の付与
					m_posR += RDeff * 0.05f;

					//視点注視点間の距離を求める
					float fLength_X = sqrtf((m_posR.x * m_posR.x) + (m_posV.x * m_posV.x));
					float fLength_Y = sqrtf((m_posR.y * m_posR.y) + (m_posV.y * m_posV.y));
					float fLength_Z = sqrtf((m_posR.z * m_posR.z) + (m_posV.z * m_posV.z));

					//視点の目標位置を算出
					m_posVDest = D3DXVECTOR3
					(
						movePlayer.x - sinf(rotPlayer.x * fLength_X),
						movePlayer.y - cosf(rotPlayer.y * fLength_Y),
						movePlayer.z - cosf(rotPlayer.z * fLength_Z)
					);

					//視点を補正
					D3DXVECTOR3 VDeff = D3DXVECTOR3
					(
						m_posVDest.x - m_posV.x,
						m_posVDest.y - m_posV.y,
						m_posVDest.z - m_posV.z
					);

					//慣性の付与
					m_posV += VDeff * 0.01f;
				}
			}
		}
	}
}
//-------------------------------------------------------
//視点の設定処理
//-------------------------------------------------------
void CCamera::SetPosV(const D3DXVECTOR3 posV)
{
	m_posV = posV;
}
//-------------------------------------------------------
//注視点の設定処理
//-------------------------------------------------------
void CCamera::SetPosR(const D3DXVECTOR3 posR)
{
	m_posR = posR;
}
//-------------------------------------------------------
//上方向ベクトルの設定処理
//-------------------------------------------------------
void CCamera::SetVecU(const D3DXVECTOR3 vecU)
{
	m_vecU = vecU;
}
//-------------------------------------------------------
//向きの設定処理
//-------------------------------------------------------
void CCamera::SetRotation(const D3DXVECTOR3 rot)
{
	m_rot = rot;
}