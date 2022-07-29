#pragma once
#include "ContentsLevel.h"

// Ό³Έν :
class Temple3BackGround;
class Temple3Tile;
class Temple3Cloud;
class Temple3PixelCollisionMap;
class TempleOfTime3 : public ContentsLevel
{
private:
	Temple3BackGround* mpBackGround;
	Temple3Tile* mpTile;
	Temple3Cloud* mpCloud;

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
	void OnEvent() override;
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

};
