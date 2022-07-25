#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class PopupMenu;
class MenuButton : public GameEngineActor
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
	MenuButton();
	~MenuButton();

	// delete Function
	MenuButton(const MenuButton& _Other) = delete;
	MenuButton(MenuButton&& _Other) noexcept = delete;
	MenuButton& operator=(const MenuButton& _Other) = delete;
	MenuButton& operator=(MenuButton&& _Other) noexcept = delete;

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
