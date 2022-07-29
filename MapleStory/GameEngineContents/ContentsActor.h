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
class ContentsActor : public GameEngineActor
{
	friend class ContentsLevel;

protected:
	GameEngineTextureRenderer* mpRenderer;
	float                      mfSpeed;
	float                      mfJumpSpeed;
	unsigned int               muHP;
	unsigned int               muMP;
	unsigned int               muPADamage;
	float                      mfPASpeed;
	unsigned int               muMADamage;
	float                      mfMASpeed;
	float                      mfWidth;
	float                      mfHeight;
	bool                       mbOnGround;
	States                     mStates;

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

	void SetHP(unsigned int _uHP) { muHP = _uHP; }
	unsigned int GetHP(void) { return muHP; }

	void BeAttacked(unsigned int _uDamage) { muHP -= _uDamage; }
	void BeHealedHP(unsigned int _uHealingAmount) { muHP += _uHealingAmount; }

	void SetMP(unsigned int _uMP) { muMP = _uMP; }
	unsigned int GetMP(void) { return muMP; }

	void SpellMagic(unsigned int _uMana) { muMP -= _uMana; }
	void BeHealedMP(unsigned int _uMana) { muMP += _uMana; }

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

protected:

private:

};

