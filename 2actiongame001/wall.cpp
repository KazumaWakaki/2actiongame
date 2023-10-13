//=============================================================================
//
//壁の処理 [wall.cpp]
//Author 若木 一真
//
//=============================================================================
#include "manager.h"
#include "wall.h"

//-------------------------------------------------------
//コンストラクタ
//-------------------------------------------------------
CWall::CWall(int nPriority) : CObject3D(nPriority)
{
	//変数のクリア
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//-------------------------------------------------------
//デストラクタ
//-------------------------------------------------------
CWall::~CWall()
{

}
//-------------------------------------------------------
//初期化処理
//-------------------------------------------------------
HRESULT CWall::Init()
{
	CTexture *pTexture = CManager::GetTexture();

	m_nIdxTexture[TYPE_BLOCK003] = pTexture->Regist("data\\texture\\block003.jpg");
	m_nIdxTexture[TYPE_HAIKEI001] = pTexture->Regist("data\\texture\\haikei001.jpg");

	//3Dオブジェクトの初期化処理
	CObject3D::Init();

	return (S_OK);
}
//-------------------------------------------------------
//終了処理
//-------------------------------------------------------
void CWall::Uninit()
{
	//3Dオブジェクトの終了処理
	CObject3D::Uninit();
}
//-------------------------------------------------------
//更新処理
//-------------------------------------------------------
void CWall::Update()
{
	//3Dオブジェクトの更新処理
	CObject3D::Update();

	//頂点情報の呼び出し(縦)
	CObject3D::SetVtxHeight();
}
//-------------------------------------------------------
//描画処理
//-------------------------------------------------------
void CWall::Draw()
{
	//3Dオブジェクトの描画処理
	CObject3D::Draw();
}
//-------------------------------------------------------
//生成処理
//-------------------------------------------------------
CWall *CWall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int SetTypeTex)
{
	CWall *pWall;

	//壁の生成
	pWall = new CWall;

	//pWallがNULLじゃない時
	if (pWall != NULL)
	{
		//初期化処理
		pWall->Init();
	}

	else
	{//生成に失敗した場合
		return NULL;
	}

	//壁の位置の設定
	pWall->SetPosition(pos);

	//壁の向きの設定
	pWall->SetRotation(rot);

	//壁のサイズ設定
	pWall->SetSize(size);

	//壁のテクスチャタイプ
	pWall->SetTypeTex(SetTypeTex);

	//nCount分回す
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		//nCountと選択されたテクスチャタイプが一致した時
		if (nCount == SetTypeTex)
		{
			//テクスチャの割り当て
			pWall->BindTexture(pWall->m_nIdxTexture[nCount]);
		}
	}

	return pWall;
}