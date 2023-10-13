//=============================================================================
//
// ライト処理 [light.cpp]
// Author 若木 一真
//
//=============================================================================
#include "light.h"
#include "input.h"
#include "manager.h"
#include "debugproc.h"

//マクロ定義
#define ROLL_SPEED  (0.03f)  //回るスピード

//-------------------------------------------------------
//コンストラクタ
//-------------------------------------------------------
CLight::CLight()
{

}
//-------------------------------------------------------
//デストラクタ
//-------------------------------------------------------
CLight::~CLight()
{

}
//=======================================================
//ライトの初期化処理
//=======================================================
HRESULT CLight::Init(void)
{
	//変数初期化
	m_nCurrentLight = 0;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXVECTOR3 vecDir;

	//ライトの種類設定
	m_aLight[0].Type = D3DLIGHT_DIRECTIONAL;

	//ライトの拡散光の設定
	m_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//ライトの方向設定
	vecDir = D3DXVECTOR3(-0.38f, - 0.86f, 0.33f);
	D3DXVec3Normalize(&vecDir, &vecDir);		//ベクトル正規化
	m_aLight[0].Direction = vecDir;

	//ライト設定
	pDevice->SetLight(0, &m_aLight[0]);

	//ライト有効化
	pDevice->LightEnable(0, TRUE);

	/////////////////////////////////
	//ライト２の設定
	/////////////////////////////////
	//ライトの種類設定
	m_aLight[1].Type = D3DLIGHT_DIRECTIONAL;

	//ライトの拡散光の設定
	m_aLight[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//ライトの方向設定
	vecDir = D3DXVECTOR3(0.57f, - 0.5f, - 0.65f);
	D3DXVec3Normalize(&vecDir, &vecDir);  //ベクトル正規化
	m_aLight[1].Direction = vecDir;

	//ライト設定
	pDevice->SetLight(1, &m_aLight[1]);

	//ライト有効化
	pDevice->LightEnable(1, TRUE);

	/////////////////////////////////
	//ライト３の設定
	/////////////////////////////////
	//ライトの種類設定
	m_aLight[2].Type = D3DLIGHT_DIRECTIONAL;

	//ライトの拡散光の設定
	m_aLight[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//ライトの方向設定
	vecDir = D3DXVECTOR3(0.89f, - 0.11f, 0.44f);
	D3DXVec3Normalize(&vecDir, &vecDir);  //ベクトル正規化
	m_aLight[2].Direction = vecDir;

	//ライト設定
	pDevice->SetLight(2, &m_aLight[2]);

	//ライト有効化
	pDevice->LightEnable(2, TRUE);

	return (S_OK);
}
//=======================================================
//ライトの終了処理
//=======================================================
void CLight::Uninit(void)
{

}
//=======================================================
//ライトの更新処理
//=======================================================
void CLight::Update(void)
{
	//デバイスポインタ設定
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXVECTOR3 vecDir;

	//キーボードの取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

#if _DEBUG

	/////////////////////////////////
	//ライト移動
	/////////////////////////////////
	//if (pInputKeyboard->GetPress(DIK_J) == true)
	//{//左移動
	//	m_aLight[m_nCurrentLight].Direction.x -= ROLL_SPEED;
	//}
	//if (pInputKeyboard->GetPress(DIK_L) == true)
	//{//右移動
	//	m_aLight[m_nCurrentLight].Direction.x += ROLL_SPEED;
	//}

	//if (pInputKeyboard->GetPress(DIK_T) == true)
	//{//奥移動
	//	m_aLight[m_nCurrentLight].Direction.z += ROLL_SPEED;
	//}
	//if (pInputKeyboard->GetPress(DIK_B) == true)
	//{//手前移動
	//	m_aLight[m_nCurrentLight].Direction.z -= ROLL_SPEED;
	//}

	//if (pInputKeyboard->GetPress(DIK_U) == true)
	//{//上移動
	//	m_aLight[m_nCurrentLight].Direction.y += ROLL_SPEED;
	//}
	//if (pInputKeyboard->GetPress(DIK_M) == true)
	//{//下移動
	//	m_aLight[m_nCurrentLight].Direction.y -= ROLL_SPEED;
	//}

	///////////////////////////////////
	////ライト切り替え
	///////////////////////////////////
	//if (pInputKeyboard->GetTrigger(DIK_O) == true)
	//{//ライト切り替え
	//	m_nCurrentLight = (m_nCurrentLight + 1) % MAX_LIGHT;
	//}

#endif

	//MAX_LIGHT分回す
	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//ベクトル正規化
		D3DXVec3Normalize
		(
			&(D3DXVECTOR3)m_aLight[nCntLight].Direction,
			&(D3DXVECTOR3)m_aLight[nCntLight].Direction
		);

		//ライト設定
		pDevice->SetLight(nCntLight, &m_aLight[nCntLight]);
	}

	//-------------------------------------------------------
	//ライトのデバック表示
	//-------------------------------------------------------
	//CManager::GetDebugProc()->Print("ライト1位置 [%f, %f, %f]\n", m_aLight[0].Direction.x, m_aLight[0].Direction.y, m_aLight[0].Direction.z);
	//CManager::GetDebugProc()->Print("ライト2位置 [%f, %f, %f]\n", m_aLight[1].Direction.x, m_aLight[1].Direction.y, m_aLight[1].Direction.z);
	//CManager::GetDebugProc()->Print("ライト3位置 [%f, %f, %f]\n", m_aLight[2].Direction.x, m_aLight[2].Direction.y, m_aLight[2].Direction.z);
}