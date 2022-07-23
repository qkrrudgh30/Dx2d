#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class Menu;
class StateBar : public GameEngineActor
{
private:
	GameEngineTextureRenderer* mpBackGroundRenderer;
	GameEngineTextureRenderer* mpLevelBackGroundRenderer;
	GameEngineTextureRenderer* mpGaugeBackGroundRenderer;
	GameEngineTextureRenderer* mpGaugeBarRenderer;
	GameEngineTextureRenderer* mpCashShopButtonRenderer;
	GameEngineTextureRenderer* mpShortCutButtonRenderer;
	float4                     mf4CameraPos;
	Menu* mpMenu;

public:
	// constrcuter destructer
	StateBar();
	~StateBar();

	// delete Function
	StateBar(const StateBar& _Other) = delete;
	StateBar(StateBar&& _Other) noexcept = delete;
	StateBar& operator=(const StateBar& _Other) = delete;
	StateBar& operator=(StateBar&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:

};

