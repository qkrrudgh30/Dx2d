#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class GameEngineUIRenderer;
class PopupMenu : public GameEngineActor
{
public:

protected:

private:
	GameEngineUIRenderer* mpRenderer;
	float                      mfWidth;
	float                      mfHeight;
	float                      mfPositionX;
	float                      mfPositionY;
	POINT                      mptMousePos;
	float4                     mf4MousePos;
	bool                       mbVisible;
	float4                     mf4CameraPos;

public:
	// constrcuter destructer
	PopupMenu();
	~PopupMenu();

	// delete Function
	PopupMenu(const PopupMenu& _Other) = delete;
	PopupMenu(PopupMenu&& _Other) noexcept = delete;
	PopupMenu& operator=(const PopupMenu& _Other) = delete;
	PopupMenu& operator=(PopupMenu&& _Other) noexcept = delete;

	float GetPositionX() { return mfPositionX; }
	float GetPositionY() { return mfPositionY; }

	void SetPositionX(float _fPositionX) { mfPositionX = _fPositionX; }
	void SetPositionY(float _fPositionY) { mfPositionY = _fPositionY; }
	void SetVisible(bool _bVisible) { mbVisible = _bVisible; }

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:

};

