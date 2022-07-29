#pragma once
#include <GameEngineCore/CoreMinimal.h>

// ���� :
class GameEngineTextureRenderer;
class PopupMenu;
class MenuButton : public GameEngineActor
{
public:
	GameEngineTextureRenderer* mpRenderer;
	float                      mfWidth;
	float                      mfHeight;
	POINT                      mptMousePos;
	float4                     mf4MousePos;
	float4                     mf4ButtonPos;
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

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:

};
