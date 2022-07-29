#pragma once
#include "ContentsLevel.h"

// Ό³Έν :
class Temple0BackGround;
class Temple0Tile;
class Temple0Cloud;
class TempleOfTime0 : public ContentsLevel
{
private:
	Temple0BackGround*        mpBackGround;
	Temple0Tile*              mpTile;
	Temple0Cloud*             mpCloud;

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
	void Start() override;
	void OnEvent() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:

};

