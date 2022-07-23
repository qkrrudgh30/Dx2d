#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class PopupMenu;
class Menu : public GameEngineActor
{
public:
	GameEngineTextureRenderer* mpRenderer;
	float                      mfWidth;
	float                      mfHeight;
	float                      mfPositionX;
	float                      mfPositionY;
	POINT                      mptMousePos;
	float4                     mf4MousePos;
	PopupMenu*                 mpPopupMenu;
	bool                       mbToggle;

public:
	// constrcuter destructer
	Menu();
	~Menu();

	// delete Function
	Menu(const Menu& _Other) = delete;
	Menu(Menu&& _Other) noexcept = delete;
	Menu& operator=(const Menu& _Other) = delete;
	Menu& operator=(Menu&& _Other) noexcept = delete;

	float GetPositionX() { return mfPositionX; }
	float GetPositionY() { return mfPositionY; }

	void SetPositionX(float _fPositionX) { mfPositionX = _fPositionX; }
	void SetPositionY(float _fPositionY) { mfPositionY = _fPositionY; }

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:

};
