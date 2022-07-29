#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class Temple3Tile : public GameEngineActor
{
public:
	// constrcuter destructer
	Temple3Tile();
	~Temple3Tile();

	// delete Function
	Temple3Tile(const Temple3Tile& _Other) = delete;
	Temple3Tile(Temple3Tile&& _Other) noexcept = delete;
	Temple3Tile& operator=(const Temple3Tile& _Other) = delete;
	Temple3Tile& operator=(Temple3Tile&& _Other) noexcept = delete;

	GameEngineTextureRenderer* GetRenderer() { return mpRenderer; }

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

