#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class Temple3Monster : public GameEngineActor
{
public:
	// constrcuter destructer
	Temple3Monster();
	~Temple3Monster();

	// delete Function
	Temple3Monster(const Temple3Monster& _Other) = delete;
	Temple3Monster(Temple3Monster&& _Other) noexcept = delete;
	Temple3Monster& operator=(const Temple3Monster& _Other) = delete;
	Temple3Monster& operator=(Temple3Monster&& _Other) noexcept = delete;

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

