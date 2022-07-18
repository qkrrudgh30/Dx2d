#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class LoginBackground : public GameEngineActor
{
public:
	// constrcuter destructer
	LoginBackground();
	~LoginBackground();

	// delete Function
	LoginBackground(const LoginBackground& _Other) = delete;
	LoginBackground(LoginBackground&& _Other) noexcept = delete;
	LoginBackground& operator=(const LoginBackground& _Other) = delete;
	LoginBackground& operator=(LoginBackground&& _Other) noexcept = delete;

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

