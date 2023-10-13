//=============================================================================
//
// オブジェクト管理 [object.cpp]
// Author 若木 一真
//
//=============================================================================
#include "object.h"
#include "manager.h"

//静的メンバ変数
CObject *CObject::m_apObject[PRIORITY][MAX_OBJECT] = {};
int CObject::m_nNumAll = 0;

//-------------------------------------------------------
//コンストラクタ
//-------------------------------------------------------
CObject::CObject(int nPriority)
{
	//MAX_OBJECT分回す
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nPriority][nCntObject] == NULL)
		{
			m_apObject[nPriority][nCntObject] = this;
			m_nPriority = nPriority;
			m_nlD = nCntObject;  //自分自身のIDを保存
			m_nNumAll++;  //総数をカウントアップ

			break;
		}
	}
}
//-------------------------------------------------------
//デストラクタ
//-------------------------------------------------------
CObject::~CObject()
{

}
//-------------------------------------------------------
//全てのオブジェクトの破棄
//-------------------------------------------------------
void CObject::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY; nCntPriority++)
	{
		//MAX_OBJECT分回す
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != NULL)
			{
				//終了処理
				m_apObject[nCntPriority][nCntObject]->Uninit();
			}
		}
	}
}
//-------------------------------------------------------
//全てのオブジェクトの更新処理
//-------------------------------------------------------
void CObject::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY; nCntPriority++)
	{
		//MAX_OBJECT分回す
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != NULL)
			{
				//更新処理
				m_apObject[nCntPriority][nCntObject]->Update();
			}
		}
	}
}
//-------------------------------------------------------
//全てのオブジェクトの描画処理
//-------------------------------------------------------
void CObject::DrawAll(void)
{
	CCamera *pCamera = CManager::GetCamera();

	//カメラの設定
	pCamera->SetCamera();

	//PRIORITY分回す
	for (int nCntPriority = 0; nCntPriority < PRIORITY; nCntPriority++)
	{
		//MAX_OBJECT分回す
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != NULL)
			{
				//描画処理
				m_apObject[nCntPriority][nCntObject]->Draw();
			}
		}
	}
}
//-------------------------------------------------------
//オブジェクトの破棄
//-------------------------------------------------------
void CObject::Release(void)
{
	int nNum = m_nlD;                //番号保持
	int nNumPriority = m_nPriority;  //番号保持

	if (m_apObject[nNumPriority][nNum]!= NULL)
	{
		delete m_apObject[nNumPriority][nNum];  //メモリの開放

		m_apObject[nNumPriority][nNum] = NULL;  //使用していない状態にする

		m_nNumAll--;  //総数をカウントダウン
	}	
}
//-------------------------------------------------------
//タイプ設定
//-------------------------------------------------------
void CObject::SetType(TYPE type)
{
	m_type = type;
}
//-------------------------------------------------------
//状態管理設定
//-------------------------------------------------------
void CObject::SetState(STATE state, int nCounterState)
{
	m_state = state;
	m_nCounterState = nCounterState;
}
//-------------------------------------------------------
//状態管理設定
//-------------------------------------------------------
void CObject::UpdateState(void)
{
	switch (m_state)
	{
	case STATE_NORMAL:
		break;

	case STATE_DAMAGE:

		m_nCounterState--;

		if (m_nCounterState <= 0)
		{
			m_state = STATE_NORMAL;

			break;
		}

	case STATE_DEATH:
		break;
	}
}
//-------------------------------------------------------
//オブジェクト取得
//-------------------------------------------------------
CObject *CObject::GetObject(int nPriority, int nIdx)
{
	return m_apObject[nPriority][nIdx];
}