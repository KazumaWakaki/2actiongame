//=============================================================================
//
// [player3D.h]
// Author ��� ��^
//
//=============================================================================
#ifndef _PLAYER3D_H_  //���̃}�N����`������ĂȂ�������
#define _PLAYER3D_H_  //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "objectX.h"
#include "enemy3D.h"

class CBullet3D;
class CAttackGage;

//�v���C���[3D�N���X
class CPlayer3D : public CObjectX
{
public:
	//�W�����v���
	typedef enum
	{
		PLAYERJUMP_GROUND = 0,  //�n��
		PLAYERJUMP_SKY,  //�W�����v���
		PLAYERJUMP_GETOFF,  //�~�����
		PLAYERJUMP_MAX
	}PLAYERJAMP;

	//�U�����
	typedef enum
	{
		ATTACKSTATE_NONE = 0,     //�������Ă��Ȃ�
		ATTACKSTATE_MELEEATTACK,  //�ߐڍU�����
		ATTACKSTATE_RUSHATTACK,  //�ːi�U�����
		ATTACKSTATE_MAX
	}ATTACKSTATE;

	//�퓬���
	typedef enum
	{
		BATTLESTATE_PROXIMITY = 0,  //�ߐڏ��
		BATTLESTATE_LONG,  //���������
		BATTLESTATE_MAX
	}BATTLESTATE;

	//���[�v�\���
	typedef enum
	{
		WARPSTATE_FALSE = 0,  //���[�v�o���Ȃ����
		WARPSTATE_TURE,  //���[�v�o������
		WARPSTATE_MAX
	}WARPSTATE;

	CPlayer3D();   //�R���X�g���N�^
	~CPlayer3D();  //�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(void);  //����������
	virtual void Uninit(void);	 //�I������
	virtual void Update(void);  //�X�V����
	virtual void Draw(void);	 //�`�揈��
	static CPlayer3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 size);  //��������
	void AttackState(void);  //�U�����

	//�擾
	int GetLife(void) { return m_Life; };  //�̗͂̎擾
	int GetAttackGage(void) { return m_AttackGage; };  //�A�^�b�N�Q�[�W�̎擾
	int GetAttackState(void) { return m_AttackState; };  //�U����Ԃ̎擾
	D3DXVECTOR3 GetStartPos(void) { return m_StartPos; };  //�퓬��Ԃ̎擾

	//�ݒ�
	void SetPlayerJump(PLAYERJAMP Jamp);  //�W�����v��Ԃ̐ݒ菈��
	void SetLife(int Life);  //�̗͂̐ݒ�
	void SetAttack(bool Attack);  //�U����Ԃ̐ݒ�
	void SetAttackState(ATTACKSTATE AttackState);  //�퓬��Ԃ̐ݒ�
	void SetAttackGage(int AttackGage);  //�A�^�b�N�Q�[�W�̐ݒ�

	//�����蔻��
	static void HitPlayer(int nDamage);  //�v���C���[�̃q�b�g����
	static bool CollisionEnemy(CEnemy3D *pEnemy);  //�G�Ƃ̓����蔻��
	static bool CollisionBullet(CBullet3D *pBullet);  //�e�Ƃ̓����蔻��

	static void AttackGageMove(CAttackGage *pAttackGage);  //�A�^�b�N�Q�[�W�ݒ菈��

private:
	int m_nIdxTexture;  //�e�N�X�`���ۑ�
	int m_nIdxMode;  //���f�����蓖��
	int m_nCnt;  //�C���N�������g�̃J�E���g
	int m_nCntDown;  //�W�����v�̃J�E���g
	int m_nCntBullet;  //�e���˂̃J�E���g
	int m_nCntAttack;  //�A�^�b�N�J�E���g
	int m_Life;  //�̗�
	int m_BoostGage;  //�u�[�X�g�Q�[�W
	int m_State;  //��ԊǗ�
	int m_nCntState;  //��Ԃ̃J�E���g
	int m_AttackGage;  //�A�^�b�N�Q�[�W
	bool m_Attack;  //�U����Ԑ؂�ւ�
	PLAYERJAMP m_jump;  //�v���C���[�̃W�����v
	ATTACKSTATE m_AttackState;  //�U�����
	BATTLESTATE m_BattleState;  //�퓬���
	WARPSTATE m_WarpState;  //���[�v�\���
	D3DXVECTOR3 m_StartPos;  //�X�^�[�g�ʒu
	D3DXVECTOR3 m_vtxMin;  //�ŏ��̒��_���W
	D3DXVECTOR3 m_vtxMax;  //�ő�̒��_���W
	static CPlayer3D *m_apObject;  //�I�u�W�F�N�g�N���X�̃|�C���^
};

#endif