//=============================================================================
//
// [enemy3D.h]
// Author ��� ��^
//
//=============================================================================
#ifndef _ENEMY3D_H_  //���̃}�N����`������ĂȂ�������
#define _ENEMY3D_H_  //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "objectX.h"

//�}�N����`
#define ENEMYSPEED   (3.0f)    //�ړ����̃X�s�[�h
#define ENEMYSPEEDUP (0.15f)   //�ړ��ʍX�V���̃X�s�[�h
#define ENEMY_COLLISION  (50)  //�G�̓����蔻��
#define MAX_ENEMY         (20)  //�G�̍ő吔

class CBullet3D;
class CPlayer3D;

//�G�N���X
class CEnemy3D : public CObjectX
{
public:
	//�e�N�X�`���^�C�v���
	typedef enum
	{
		TYPE_KOUMORI = 0,  //�R�E����
		TYPE_OOKAMI,           //�T
		TYPE_MAX
	}TYPE;

	//��ԊǗ�
	typedef enum
	{
		ENEMYSTATE_NORMAL = 0,     //�ʏ���
		ENEMYSTATE_DAMAGE,         //�_���[�W���
		ENEMYSTATE_MAX
	}ENEMYSTATE;

	//�ړ��Ǘ�
	typedef enum
	{
		ENEMYMOVE_RIGHT = 0,  //�E�Ɉړ�����
		ENEMYMOVE_LEFT,       //���Ɉړ�����
		ENEMYMOVE_AUTO,       //�����œ���
		ENEMYMOVE_MAX
	}ENEMYMOVE;

	CEnemy3D();   //�R���X�g���N�^
	~CEnemy3D();  //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);  //����������
	void Uninit(void);   //�I������
	void Update(void);   //�X�V����
	void Draw(void);	 //�`�揈��
	static CEnemy3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 size, int SetTypeTex, int Life);  //��������
	static void PlayerAttack(CPlayer3D *pPlayer);  //�v���C���[�ߐڍU������
	static void MoveEnemy(CPlayer3D *pPlayer);  //�G�̈ړ�
	void UpdateEnemyState(void);  //�G�̏��
	void MoveEnemy(void);  //�G�̈ړ�

	//�擾
	//int GetnID(void) { return m_nID; };  //�ԍ��̎擾

	//�ݒ�
	void SetLife(int Life);  //�̗͂̐ݒ�
	void SetEnemyState(ENEMYSTATE state, int nCounterState);  //��Ԃ̐ݒ�
	void SetEnemyMoveState(ENEMYMOVE statemove);

	//�����蔻�菈��
	static void HitEnemy(int nDamage, int nCnt);  //�G�̃q�b�g����
	static bool CollisionBullet(CBullet3D *pBullet);  //�e�Ƃ̓����蔻��
	static bool AttackCollision(CPlayer3D *pPlayer);  //�ːi�U���̓G�Ƃ̓����蔻��

private:
	int m_nIdxModel[TYPE_MAX];  //���f�����蓖��
	int m_Life;  //�̗�
	int m_nID;  //�ԍ�
	int m_nCntHit;  //�_���[�W��Ԃ̃J�E���g
	int m_nCounterState;  //��ԊǗ��J�E���^�[
	int m_nCounterMove;  //�ړ��J�E���^�[
	int m_nCounterBullet;  //�e�̃J�E���^�[
	ENEMYSTATE m_state;  //��ԊǗ�
	ENEMYMOVE m_movestate;  //�ړ��Ǘ�
	static CEnemy3D *m_apObject[MAX_ENEMY];  //�I�u�W�F�N�g�N���X�̃|�C���^
};

#endif