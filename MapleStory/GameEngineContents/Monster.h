#pragma once
#include "ContentsActor.h"

#define StateCount (8);
struct MonsterState
{
	union 
	{
		long long AllState;

		struct
		{
			bool mbStand;
			bool mbLeftWalk;
			bool mbRightWalk;
			bool mbDead;
			bool mbAttack1;
			bool mbAttack2;
			bool mbAlert;
			bool mbPadding;
		};
	};
};

// Ό³Έν :
class GameEngineTextureRenderer;
class MonsterHPGauge;
class Monster : public ContentsActor
{
protected:
	MonsterHPGauge*            mpMonsterHP;
	MonsterState               mState;
	static Player*             spPlayer;
	float                      mfPreAccTime;
	float                      mfDistanceFromPlayer;
	float4                     mf4DirectionToPlayer;
	bool                       mbAttack;
	GameEngineTextureRenderer* mpEffect;
	unsigned int               muHittedDamage;
	std::vector<GameEngineTextureRenderer*> mvDamageFonts;
	float4 mf4DamageFontPosition;

public:
	// constrcuter destructer
	Monster();
	~Monster();

	// delete Function
	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;

	void SetHittedAfterSecond()
	{
		if (-1.f != mfBeforeAccTimeForHit && 30.f <= mfAccTime - mfBeforeAccTimeForHit)
		{
			mbHitted = false;
			mbAttack = false;
			mfBeforeAccTimeForHit = -1.f;
		}
	}

	unsigned int GetHittedDamage() { return muHittedDamage; }

	void SetDamageFont(unsigned int _nDamage);
	void SetDamageFontFading(float _fDeltaTime);

protected:
	virtual void Start() override;
	virtual void Update(float _fDeltaTime) override;



};

