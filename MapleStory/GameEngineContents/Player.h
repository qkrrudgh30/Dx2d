#pragma once
#include "ContentsActor.h"

// Ό³Έν :
class ContentsLevel;
class Player : public ContentsActor
{
private:
	ContentsLevel*         mpParentLevel;
	float4                 mf4PixelData;
	GameEngineStateManager StateManager;

public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	void IdleStart(const StateInfo& _Info);
	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void IdleEnd(const StateInfo& _Info) {}

	void MoveStart(const StateInfo& _Info);
	void MoveUpdate(float _DeltaTime, const StateInfo& _Info);
	void MoveEnd(const StateInfo& _Info) {}

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

	void JumpStart(const StateInfo& _Info);
	void JumpUpdate(float _DeltaTime, const StateInfo& _Info);
	void JumpEnd(const StateInfo& _Info) {}

	void LadderStart(const StateInfo& _Info);
	void LadderUpdate(float _DeltaTime, const StateInfo& _Info);
	void LadderEnd(const StateInfo& _Info) {}

	void FinalAttack1Start(const StateInfo& _Info);
	void FinalAttack1Update(float _DeltaTime, const StateInfo& _Info);
	void FinalAttack1End(const StateInfo& _Info) {}

	void FinalAttack2Start(const StateInfo& _Info);
	void FinalAttack2Update(float _DeltaTime, const StateInfo& _Info);
	void FinalAttack2End(const StateInfo& _Info) {} 

	/* Skill */

};

