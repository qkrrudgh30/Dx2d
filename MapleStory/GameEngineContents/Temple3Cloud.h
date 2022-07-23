#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class Temple3Cloud : public GameEngineActor
{
public:
	// constrcuter destructer
	Temple3Cloud();
	~Temple3Cloud();

	// delete Function
	Temple3Cloud(const Temple3Cloud& _Other) = delete;
	Temple3Cloud(Temple3Cloud&& _Other) noexcept = delete;
	Temple3Cloud& operator=(const Temple3Cloud& _Other) = delete;
	Temple3Cloud& operator=(Temple3Cloud&& _Other) noexcept = delete;

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

