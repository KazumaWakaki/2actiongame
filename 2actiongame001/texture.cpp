//=============================================================================
//
// テクスチャ管理 [texture.cpp]
// Author 若木 一真
//
//=============================================================================
#include "texture.h"
#include "manager.h"

//静的メンバ変数
LPDIRECT3DTEXTURE9 CTexture::m_apTexture[MAX_TEXTURE] = {};
char CTexture::m_FileName[MAX_TEXTURE][512] = {};
int  CTexture::m_nNumAll = 0;

//-------------------------------------------------------
//コンストラクタ
//-------------------------------------------------------
CTexture::CTexture()
{

}
//-------------------------------------------------------
//デストラクタ
//-------------------------------------------------------
CTexture::~CTexture()
{

}
//-------------------------------------------------------
//全てのテクスチャの読み込み
//-------------------------------------------------------
HRESULT CTexture::Load(void)
{
	return (S_OK);
}
//-------------------------------------------------------
//全てのテクスチャの破棄
//-------------------------------------------------------
void CTexture::Unload(void)
{
	//MAX_TEXTURE分回す
	for (int nCntTexture = 0; nCntTexture < MAX_TEXTURE; nCntTexture++)
	{
		//テクスチャの破棄
		if (m_apTexture[nCntTexture] != NULL)
		{
			m_apTexture[nCntTexture]->Release();
			m_apTexture[nCntTexture] = NULL;
		}
	}
}
//-------------------------------------------------------
//テクスチャを設定する
//-------------------------------------------------------
int CTexture::Regist(const char *pFilename)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	int nIdx;

	nIdx = m_nNumAll + 1;  //保存

	//m_nNumAll分回す
	for (int nCntTexture = 0; nCntTexture < m_nNumAll; nCntTexture++)
	{
		if (strcmp(&m_FileName[nCntTexture][0], pFilename) == 0)
		{
			nIdx = nCntTexture;

			return nIdx;
		}
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, pFilename, &m_apTexture[nIdx]);

	strcpy(&m_FileName[nIdx][0], pFilename);

	m_nNumAll++;

	return nIdx;
}
//-------------------------------------------------------
//アドレスを返す
//-------------------------------------------------------
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nIdx)
{
	if (nIdx <= m_nNumAll && 0 <= nIdx)
	{
		return m_apTexture[nIdx];
	}

	return NULL;
}