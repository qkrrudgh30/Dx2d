#pragma once
#include "ContentsLevel.h"

// Ό³Έν :
class TempleOfTime2 : public ContentsLevel
{
public:
	// constrcuter destructer
	TempleOfTime2();
	~TempleOfTime2();

	// delete Function
	TempleOfTime2(const TempleOfTime2& _Other) = delete;
	TempleOfTime2(TempleOfTime2&& _Other) noexcept = delete;
	TempleOfTime2& operator=(const TempleOfTime2& _Other) = delete;
	TempleOfTime2& operator=(TempleOfTime2&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

};
