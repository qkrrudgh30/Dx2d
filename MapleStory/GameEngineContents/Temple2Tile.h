#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class Temple2Tile : public GameEngineActor
{
public:
	// constrcuter destructer
	Temple2Tile();
	~Temple2Tile();

	// delete Function
	Temple2Tile(const Temple2Tile& _Other) = delete;
	Temple2Tile(Temple2Tile&& _Other) noexcept = delete;
	Temple2Tile& operator=(const Temple2Tile& _Other) = delete;
	Temple2Tile& operator=(Temple2Tile&& _Other) noexcept = delete;

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

