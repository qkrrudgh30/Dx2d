#pragma once

#include <GameEngineCore/GameEngineComponent.h>

// Ό³Έν :
class Physics : public GameEngineComponent
{
private:
	ContentsActor* mpParent;
	float4         mf4Force;
	float4         mf4Mass;
	float4         mf4Accelation;
	float4         mf4Velocity;
	float4         mf4Position;
	float          mfGravity;

public:
	// constrcuter destructer
	Physics();
	~Physics();

	// delete Function
	Physics(const Physics& _Other) = delete;
	Physics(Physics&& _Other) noexcept = delete;
	Physics& operator=(const Physics& _Other) = delete;
	Physics& operator=(Physics&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update(float _fDeltaTime) override;
	virtual void End() override;

private:

};

