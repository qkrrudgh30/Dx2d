#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class Temple1Tile : public GameEngineActor
{
public:
	// constrcuter destructer
	Temple1Tile();
	~Temple1Tile();

	// delete Function
	Temple1Tile(const Temple1Tile& _Other) = delete;
	Temple1Tile(Temple1Tile&& _Other) noexcept = delete;
	Temple1Tile& operator=(const Temple1Tile& _Other) = delete;
	Temple1Tile& operator=(Temple1Tile&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineTextureRenderer* mpRenderer;
	float                      mfWidth;
	float                      mfHeight;
	float                      mfPositionX;
	float                      mfPositionY;

};

