#pragma once
#include "ContentsActor.h"

// Ό³Έν :
class ContentsLevel;
class RigidBody;
class Player : public ContentsActor
{
private:
	ContentsLevel*         mpParentLevel;
	float4                 mf4PixelData;
	float4                 mf4PixelDataOnRightSide;
	float4                 mf4PixelDataOnLeftSide;
	GameEngineStateManager StateManager;
	static Player*         spPlayer;
	RigidBody*             mpRigidBody;
	bool                   mbOnAboveGround;

public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	static Player* GetPlayer() { return spPlayer; }

	float4 GetPixelData() { return mf4PixelData; }

	float4 PreviousDirection() 
	{
		if (0 <= mpRenderer->GetTransform().GetWorldScale().x)
		{
			return float4{ 1.f, 1.f, 1.f, 1.f };
		}
		else 
		{
			return float4{ -1.f, 1.f, 1.f, 1.f }; 
		}
	}

	void SetParentLevel(ContentsLevel* _pParentLevel) 
	{ 
		mpParentLevel = _pParentLevel; 
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	// Animation notify.
	void EndAttack1(const FrameAnimation_DESC& _Info);
	void EndAttack2(const FrameAnimation_DESC& _Info);
	void EndFinalAttack1(const FrameAnimation_DESC& _Info);
	void EndFinalAttack2(const FrameAnimation_DESC& _Info);

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

	void JumpStart(const StateInfo& _Info);
	void JumpUpdate(float _DeltaTime, const StateInfo& _Info);
	void JumpEnd(const StateInfo& _Info) {}

	void LadderIdleStart(const StateInfo& _Info);
	void LadderIdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void LadderIdleEnd(const StateInfo& _Info) {}

	void LadderMoveStart(const StateInfo& _Info);
	void LadderMoveUpdate(float _DeltaTime, const StateInfo& _Info);
	void LadderMoveEnd(const StateInfo& _Info) {}

	void FinalAttack1Start(const StateInfo& _Info);
	void FinalAttack1Update(float _DeltaTime, const StateInfo& _Info);
	void FinalAttack1End(const StateInfo& _Info) {}

	void FinalAttack2Start(const StateInfo& _Info);
	void FinalAttack2Update(float _DeltaTime, const StateInfo& _Info);
	void FinalAttack2End(const StateInfo& _Info) {} 

	/* Skill */

};

