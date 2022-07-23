#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class ExitButton : public GameEngineActor
{
public:
	// constrcuter destructer
	ExitButton();
	~ExitButton();

	// delete Function
	ExitButton(const ExitButton& _Other) = delete;
	ExitButton(ExitButton&& _Other) noexcept = delete;
	ExitButton& operator=(const ExitButton& _Other) = delete;
	ExitButton& operator=(ExitButton&& _Other) noexcept = delete;

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
	float4                     mf4MousePos;

};

