#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class Temple1Cloud : public GameEngineActor
{
public:
	// constrcuter destructer
	Temple1Cloud();
	~Temple1Cloud();

	// delete Function
	Temple1Cloud(const Temple1Cloud& _Other) = delete;
	Temple1Cloud(Temple1Cloud&& _Other) noexcept = delete;
	Temple1Cloud& operator=(const Temple1Cloud& _Other) = delete;
	Temple1Cloud& operator=(Temple1Cloud&& _Other) noexcept = delete;

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

