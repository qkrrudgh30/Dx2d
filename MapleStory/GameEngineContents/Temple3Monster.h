#pragma once
#include "Monster.h"

// Ό³Έν :
class Temple3Monster : public Monster
{
private:
	GameEngineStateManager mStateManager;

public:
	// constrcuter destructer
	Temple3Monster();
	~Temple3Monster();

	// delete Function
	Temple3Monster(const Temple3Monster& _Other) = delete;
	Temple3Monster(Temple3Monster&& _Other) noexcept = delete;
	Temple3Monster& operator=(const Temple3Monster& _Other) = delete;
	Temple3Monster& operator=(Temple3Monster&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	// Animation notify.
	void EndAttack1();
	void EndAttack2();

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

