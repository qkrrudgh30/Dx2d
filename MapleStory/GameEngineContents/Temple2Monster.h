#pragma once

#include "Monster.h"

// Ό³Έν :
class Player;
class Temple2Monster : public Monster
{
private:
	GameEngineStateManager     mStateManager;
	GameEngineTextureRenderer* mpHittedEffect;
	GameEngineTextureRenderer* mpDamageEffect;

public:
	// constrcuter destructer
	Temple2Monster();
	~Temple2Monster();

	// delete Function
	Temple2Monster(const Temple2Monster& _Other) = delete;
	Temple2Monster(Temple2Monster&& _Other) noexcept = delete;
	Temple2Monster& operator=(const Temple2Monster& _Other) = delete;
	Temple2Monster& operator=(Temple2Monster&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	// Animation notify.
	void EndAttack1();
	void EndAttack2();
	void EndHitting() { mpHittedEffect->ChangeFrameAnimation("Clear"); mpHittedEffect->Off(); }

	// FSM Functions.
	void StandStart(const StateInfo& _Info);
	void StandUpdate(float _DeltaTime, const StateInfo& _Info);
	void StandEnd(const StateInfo& _Info) {}

	void WalkStart(const StateInfo& _Info);
	void WalkUpdate(float _DeltaTime, const StateInfo& _Info);
	void WalkEnd(const StateInfo& _Info) {}

	void DeadStart(const StateInfo& _Info);
	void DeadUpdate(float _DeltaTime, const StateInfo& _Info);
	void DeadEnd(const StateInfo& _Info);

	void Attack1Start(const StateInfo& _Info);
	void Attack1Update(float _DeltaTime, const StateInfo& _Info);
	void Attack1End(const StateInfo& _Info) {}

	void Attack2Start(const StateInfo& _Info);
	void Attack2Update(float _DeltaTime, const StateInfo& _Info);
	void Attack2End(const StateInfo& _Info) {}

	void AlertStart(const StateInfo& _Info);
	void AlertUpdate(float _DeltaTime, const StateInfo& _Info);
	void AlertEnd(const StateInfo& _Info) {}
};

