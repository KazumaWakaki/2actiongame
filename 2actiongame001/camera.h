//=============================================================================
//
// [camera.h]
// Author 若木 一真
//
//=============================================================================
#ifndef _CAMERA_H_  //このマクロ定義がされてなかったら
#define _CAMERA_H_  //2重インクルード防止のマクロを定義する

#include "main.h"

class CObject3D;

//レンダラークラス
class CCamera
{
public:
	CCamera();  //コンストラクタ
	~CCamera(); //デストラクタ

	//メンバ関数
	HRESULT Init(void);                //初期化処理
	void Uninit(void);                 //終了処理
	void Update(void);                 //更新処理
	void SetCamera(void);              //設定処理
	
	//設定
	void SetPosV(D3DXVECTOR3 posV);     //視点の設定処理
	void SetPosR(D3DXVECTOR3 posR);     //注視点の設定処理
	void SetVecU(D3DXVECTOR3 vecU);     //上方向ベクトルの設定処理
	void SetRotation(D3DXVECTOR3 rot);  //向きの設定処理

	//取得
	D3DXVECTOR3 GetCameraPos(void) { return m_posV; }  //カメラ位置(デバッグ)
	D3DXVECTOR3 GetCameraRot(void) { return m_rot; }   //カメラ角度の取得

private:
	//変数
	D3DXMATRIX mtxView;              //ビューマトリックス
	D3DXMATRIX mtxProjection;        //プロジェクションマトリックス
	D3DXVECTOR3 m_posV;              //視点
	D3DXVECTOR3 m_posR;              //注視点
	D3DXVECTOR3 m_vecU;              //上方向ベクトル
	D3DXVECTOR3 m_rot;               //向き
	D3DXVECTOR3 m_posVDest;          //目的の視点
	D3DXVECTOR3 m_posRDest;          //目的の注視点
	LPDIRECT3D9 m_pD3D;              //Direct3Dオブジェクトの生成
	LPDIRECT3DDEVICE9 m_pD3DDevice;  //デバイスの宣言
	float fLengthX;                  //X面の視点から注視点までの距離
	float fLengthY;                  //Y面の視点から注視点までの距離
	float fLengthZ;                  //Z面の視点から注視点までの距離
	float m_fLengthCamera;           //対角線の長さ
	float m_fAngleCamera;            //対角線の角度

	//関数
	void MoveCamera(void);  //追従処理

};

#endif