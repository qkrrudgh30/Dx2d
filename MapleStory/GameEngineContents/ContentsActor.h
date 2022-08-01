#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum
{
	eFalse = 0,
	eTrue = 1,
};

// Ό³Έν :
struct States
{
	union
	{
		float4 AllStates;
		struct
		{
			char mbStand;
			char mbWalk;
			char mbDead;
			char mbAttack1;

			char mbAttack2;
			char mbAlert;
			char mbJump;
			char mbLadder;
			
			char mbFinalAttack1;
			char mbFinalAttack2;
			char mbPadding0;
			char mbPadding1;
			
			char mbPadding2;
			char mbPadding3;
			char mbPadding4;
			char mbPadding5;
		};
	};
};

class GameEngineTextureRenderer;
class GameEngineCollision;
class ContentsActor : public GameEngineActor
{
	friend class ContentsLevel;

protected:
	GameEngineTextureRenderer* mpRenderer;
	float                      mfSpeed;
	float                      mfJumpSpeed;
	float                      mfHP;
	float                      mfMP;
	unsigned int               muPADamage;
	float                      mfPASpeed;
	unsigned int               muMADamage;
	float                      mfMASpeed;
	float                      mfWidth;
	float                      mfHeight;
	bool                       mbOnGround;
	bool                       mbOnLadder;
	bool                       mbHitted;
	bool                       mbInvincible;
	States                     mStates;
	GameEngineCollision*       mpCollision;

public:
	// constrcuter destructer
	ContentsActor();
	~ContentsActor();

	// delete Function
	ContentsActor(const ContentsActor& _Other) = delete;
	ContentsActor(ContentsActor&& _Other) noexcept = delete;
	ContentsActor& operator=(const ContentsActor& _Other) = delete;
	ContentsActor& operator=(ContentsActor&& _Other) noexcept = delete;

	GameEngineRenderer* GetRenderer() { return mpRenderer; }

	void SetSpeed(float _fSpeed) { mfSpeed = _fSpeed; }
	float GetSpeed(void) { return mfSpeed; }

	void SetHP(unsigned int _fHP) { mfHP = _fHP; }
	unsigned int GetHP(void) { return mfHP; }

	void BeAttacked(unsigned int _uDamage) { mfHP -= _uDamage; }
	void BeHealedHP(unsigned int _uHealingAmount) { mfHP += _uHealingAmount; }

	void SetMP(unsigned int _fMP) { mfMP = _fMP; }
	unsigned int GetMP(void) { return mfMP; }

	void SpellMagic(unsigned int _fMana) { mfMP -= _fMana; }
	void BeHealedMP(unsigned int _fMana) { mfMP += _fMana; }

	void SetPADamage(unsigned int _uPADamage) { muPADamage = _uPADamage; }
	unsigned int GetPADamage(void) { return muPADamage; }

	void SetPASpeed(float _fPASpeed) { mfPASpeed = _fPASpeed; }
	float GetPASpeed(void) { return mfPASpeed; }

	void SetMADamage(unsigned int _uMADamage) { muMADamage = _uMADamage; }
	unsigned int GetMADamage(void) { return muMADamage; }

	void SetMASpeed(float _fMASpeed) { mfMASpeed = _fMASpeed; }
	float GetMASpeed(void) { return mfMASpeed; }

	void SetGround(bool _bOnGround) { mbOnGround = _bOnGround; }
	bool IsOnGround() { return mbOnGround; }

	void SetLadder(bool _bOnLadder) { mbOnLadder = _bOnLadder; }
	bool IsOnLadder() { return mbOnLadder; }

	void SetHitted(bool _bHitted) { mbHitted = _bHitted; }
	bool IsOnHitted() { return mbHitted; }

	void SetInvincible(bool _bInvincible) { mbInvincible = _bInvincible; }
	bool IsInvincible() { return mbInvincible; }

	void SetCollision(GameEngineCollision* _pCollision) { mpCollision = _pCollision; }
	GameEngineCollision* GetCollision() { return mpCollision; }

protected:

private:

};

