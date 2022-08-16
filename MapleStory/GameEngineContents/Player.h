#pragma once
#include "ContentsActor.h"

// Ό³Έν :
class ContentsLevel;
class RigidBody;
class Player : public ContentsActor
{
private:
	float4                 mf4PixelData;
	float4                 mf4HeadPixelData;
	GameEngineStateManager mStateManager;
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
	float4 GetHeadPixelData() { return mf4HeadPixelData; }
	float4 GetPixelDataOnLeftSide() { return mf4PixelDataOnLeftSide; }
	float4 GetPixelDataOnRightSide() { return mf4PixelDataOnRightSide; }

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



protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	// Animation notify.
	void EndAttack1(const FrameAnimation_DESC& _Info);
	void EndAttack2();
	void EndFinalAttack1();
	void EndFinalAttack2();

	// FSM Functions.
	void StandStart(const StateInfo& _Info);
	void StandUpdate(float _DeltaTime, const StateInfo& _Info);
	void StandEnd(const StateInfo& _Info) {}

	void WalkStart(const StateInfo& _Info);
	void WalkUpdate(float _DeltaTime, const StateInfo& _Info);
	void WalkEnd(const StateInfo& _Info) {}

	void DeadStart(const StateInfo& _Info);
	void DeadUpdate(float _DeltaTime, const StateInfo& _Info);
	void DeadEnd(const StateInfo& _Info) {}

	void AttackStart(const StateInfo& _Info);
	void AttackUpdate(float _DeltaTime, const StateInfo& _Info) {}
	void AttackEnd(const StateInfo& _Info) {}

	void JumpStart(const StateInfo& _Info);
	void JumpUpdate(float _DeltaTime, const StateInfo& _Info);
	void JumpEnd(const StateInfo& _Info) {}

	void LadderStart(const StateInfo& _Info);
	void LadderUpdate(float _DeltaTime, const StateInfo& _Info);
	void LadderEnd(const StateInfo& _Info) {}

	void AlertStart(const StateInfo& _Info);
	void AlertUpdate(float _DeltaTime, const StateInfo& _Info);
	void AlertEnd(const StateInfo& _Info) {}

	/* Skill */

};

