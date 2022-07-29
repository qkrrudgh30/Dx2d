#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class Temple0PixelCollisionMap : public GameEngineActor
{
public:
	// constrcuter destructer
	Temple0PixelCollisionMap();
	~Temple0PixelCollisionMap();

	// delete Function
	Temple0PixelCollisionMap(const Temple0PixelCollisionMap& _Other) = delete;
	Temple0PixelCollisionMap(Temple0PixelCollisionMap&& _Other) noexcept = delete;
	Temple0PixelCollisionMap& operator=(const Temple0PixelCollisionMap& _Other) = delete;
	Temple0PixelCollisionMap& operator=(Temple0PixelCollisionMap&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineTextureRenderer* mpRenderer;

};

