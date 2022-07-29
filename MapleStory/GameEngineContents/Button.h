#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class Button : public GameEngineActor
{
private:
	GameEngineTextureRenderer* mpRenderer;
	float                      mfWidth;
	float                      mfHeight;
	float                      mfPositionX;
	float                      mfPositionY;
	POINT                      mptMousePos;
	float4                     mf4MousePos;

public:
	// constrcuter destructer
	Button();
	~Button();

	// delete Function
	Button(const Button& _Other) = delete;
	Button(Button&& _Other) noexcept = delete;
	Button& operator=(const Button& _Other) = delete;
	Button& operator=(Button&& _Other) noexcept = delete;

	float GetPositionX() { return mfPositionX; }
	float GetPositionY() { return mfPositionY; }

	void SetPositionX(float _fPositionX) { mfPositionX = _fPositionX; }
	void SetPositionY(float _fPositionY) { mfPositionY = _fPositionY; }

protected:
	void Update(float _DeltaTime);

private:

};

