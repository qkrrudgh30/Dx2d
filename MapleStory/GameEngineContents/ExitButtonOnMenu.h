#pragma once

// Ό³Έν :
class ExitButtonOnMenu
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
	ExitButtonOnMenu();
	~ExitButtonOnMenu();

	// delete Function
	ExitButtonOnMenu(const ExitButtonOnMenu& _Other) = delete;
	ExitButtonOnMenu(ExitButtonOnMenu&& _Other) noexcept = delete;
	ExitButtonOnMenu& operator=(const ExitButtonOnMenu& _Other) = delete;
	ExitButtonOnMenu& operator=(ExitButtonOnMenu&& _Other) noexcept = delete;

protected:
	float GetPositionX() { return mfPositionX; }
	float GetPositionY() { return mfPositionY; }

	void SetPositionX(float _fPositionX) { mfPositionX = _fPositionX; }
	void SetPositionY(float _fPositionY) { mfPositionY = _fPositionY; }

private:

};

