#pragma once
#include "ContentsLevel.h"

// Ό³Έν :
class Temple2BackGround;
class Temple2Tile;
class Temple2Cloud;
class Temple2PixelCollisionMap;
class TempleOfTime2 : public ContentsLevel
{
private:
	Temple2BackGround* mpBackGround;
	Temple2Tile* mpTile;
	Temple2Cloud* mpCloud;

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
	void LevelStartEvent() override;
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

};
