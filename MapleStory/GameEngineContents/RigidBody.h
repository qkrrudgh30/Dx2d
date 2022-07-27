#pragma once
#include <GameEngineCore/GameEngineComponent.h>

// Ό³Έν :
class ContentsActor;
class RigidBody : public GameEngineComponent
{
private:
	ContentsActor* mpParent;
	float          mfGravity;

public:
	// constrcuter destructer
	RigidBody();
	~RigidBody();

	// delete Function
	RigidBody(const RigidBody& _Other) = delete;
	RigidBody(RigidBody&& _Other) noexcept = delete;
	RigidBody& operator=(const RigidBody& _Other) = delete;
	RigidBody& operator=(RigidBody&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

private:

};

