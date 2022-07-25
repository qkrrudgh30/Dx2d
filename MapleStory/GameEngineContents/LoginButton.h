#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
class GameEngineTextureRenderer;
class LoginButton : public GameEngineActor
{
public:
	// constrcuter destructer
	LoginButton();
	~LoginButton();

	// delete Function
	LoginButton(const LoginButton& _Other) = delete;
	LoginButton(LoginButton&& _Other) noexcept = delete;
	LoginButton& operator=(const LoginButton& _Other) = delete;
	LoginButton& operator=(LoginButton&& _Other) noexcept = delete;

	bool IsLoginButtonClicked() { return mbClicked; }
	void SetLoginButton(bool _bClicked) { mbClicked = _bClicked; }
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

	bool                       mbClicked;

};

