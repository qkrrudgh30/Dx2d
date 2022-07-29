#pragma once

#include "ContentsActor.h"

// Ό³Έν :
class Temple3Boss : public ContentsActor
{
public:
	// constrcuter destructer
	Temple3Boss();
	~Temple3Boss();

	// delete Function
	Temple3Boss(const Temple3Boss& _Other) = delete;
	Temple3Boss(Temple3Boss&& _Other) noexcept = delete;
	Temple3Boss& operator=(const Temple3Boss& _Other) = delete;
	Temple3Boss& operator=(Temple3Boss&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:

};

