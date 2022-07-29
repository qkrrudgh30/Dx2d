#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class PixelCollisionMap : public GameEngineActor
{
public:
	// constrcuter destructer
	PixelCollisionMap();
	~PixelCollisionMap();

	// delete Function
	PixelCollisionMap(const PixelCollisionMap& _Other) = delete;
	PixelCollisionMap(PixelCollisionMap&& _Other) noexcept = delete;
	PixelCollisionMap& operator=(const PixelCollisionMap& _Other) = delete;
	PixelCollisionMap& operator=(PixelCollisionMap&& _Other) noexcept = delete;

	void SetInfo(const std::string& _strTextureName);

	GameEngineTextureRenderer* GetRenderer() { return mpRenderer; }

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineTextureRenderer* mpRenderer;

};

