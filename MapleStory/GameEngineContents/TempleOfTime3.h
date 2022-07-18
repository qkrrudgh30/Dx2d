#pragma once
#include "ContentsLevel.h"

// Ό³Έν :
class TempleOfTime3 : public ContentsLevel
{
public:
	// constrcuter destructer
	TempleOfTime3();
	~TempleOfTime3();

	// delete Function
	TempleOfTime3(const TempleOfTime3& _Other) = delete;
	TempleOfTime3(TempleOfTime3&& _Other) noexcept = delete;
	TempleOfTime3& operator=(const TempleOfTime3& _Other) = delete;
	TempleOfTime3& operator=(TempleOfTime3&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

};
