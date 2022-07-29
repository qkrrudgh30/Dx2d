#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class Temple0Tile : public GameEngineActor
{
public:
	// constrcuter destructer
	Temple0Tile();
	~Temple0Tile();

	// delete Function
	Temple0Tile(const Temple0Tile& _Other) = delete;
	Temple0Tile(Temple0Tile&& _Other) noexcept = delete;
	Temple0Tile& operator=(const Temple0Tile& _Other) = delete;
	Temple0Tile& operator=(Temple0Tile&& _Other) noexcept = delete;

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

