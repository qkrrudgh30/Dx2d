// SnailsLandLevel.h

#pragma once

#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class SnailsLandLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	SnailsLandLevel();
	~SnailsLandLevel();

	// delete Function
	SnailsLandLevel(const SnailsLandLevel& _Other) = delete;
	SnailsLandLevel(SnailsLandLevel&& _Other) noexcept = delete;
	SnailsLandLevel& operator=(const SnailsLandLevel& _Other) = delete;
	SnailsLandLevel& operator=(SnailsLandLevel&& _Other) noexcept = delete;

protected:

private:
	virtual void Start() override {}
	virtual void Update(float _DeltaTime) override {}
	virtual void End() override {}

};

