#pragma once
#include "ContentsLevel.h"

// Ό³Έν :
class TempleOfTime1 : public ContentsLevel
{
public:
	// constrcuter destructer
	TempleOfTime1();
	~TempleOfTime1();

	// delete Function
	TempleOfTime1(const TempleOfTime1& _Other) = delete;
	TempleOfTime1(TempleOfTime1&& _Other) noexcept = delete;
	TempleOfTime1& operator=(const TempleOfTime1& _Other) = delete;
	TempleOfTime1& operator=(TempleOfTime1&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

};
