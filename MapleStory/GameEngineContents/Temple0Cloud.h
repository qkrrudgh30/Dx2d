#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class Temple0Cloud : public GameEngineActor
{
public:
	// constrcuter destructer
	Temple0Cloud();
	~Temple0Cloud();

	// delete Function
	Temple0Cloud(const Temple0Cloud& _Other) = delete;
	Temple0Cloud(Temple0Cloud&& _Other) noexcept = delete;
	Temple0Cloud& operator=(const Temple0Cloud& _Other) = delete;
	Temple0Cloud& operator=(Temple0Cloud&& _Other) noexcept = delete;

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

