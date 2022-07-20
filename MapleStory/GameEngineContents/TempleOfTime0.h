#pragma once
#include "ContentsLevel.h"

// Ό³Έν :
class TempleOfTime0 : public ContentsLevel
{
public:
	// constrcuter destructer
	TempleOfTime0();
	~TempleOfTime0();

	// delete Function
	TempleOfTime0(const TempleOfTime0& _Other) = delete;
	TempleOfTime0(TempleOfTime0&& _Other) noexcept = delete;
	TempleOfTime0& operator=(const TempleOfTime0& _Other) = delete;
	TempleOfTime0& operator=(TempleOfTime0&& _Other) noexcept = delete;

protected:
	void OnEvent() override;
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:

};

