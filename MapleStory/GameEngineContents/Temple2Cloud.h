#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class Temple2Cloud : public GameEngineActor
{
public:
	// constrcuter destructer
	Temple2Cloud();
	~Temple2Cloud();

	// delete Function
	Temple2Cloud(const Temple2Cloud& _Other) = delete;
	Temple2Cloud(Temple2Cloud&& _Other) noexcept = delete;
	Temple2Cloud& operator=(const Temple2Cloud& _Other) = delete;
	Temple2Cloud& operator=(Temple2Cloud&& _Other) noexcept = delete;

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

