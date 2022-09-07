#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class GameEngineUIRenderer;
class MenuButton;
class HPGauge;
class MPGauge;
class EXPGauge;
class QuickSlot;
class Player;
class StateBar : public GameEngineActor
{
private:
	GameEngineUIRenderer* mpBackGroundRenderer;
	GameEngineUIRenderer* mpLevelBackGroundRenderer;
	GameEngineUIRenderer* mpGaugeNamesRenderer;
	GameEngineUIRenderer* mpGaugeBackGroundRenderer;
	GameEngineUIRenderer* mpCashShopButtonRenderer;
	GameEngineUIRenderer* mpShortCutButtonRenderer;
	float4 mf4CameraPos;
	MenuButton* mpMenuButton;
	HPGauge* mpHPGauge;
	MPGauge* mpMPGauge;
	EXPGauge* mpEXPGauge;
	Player* mpPlayer;


	std::vector<GameEngineUIRenderer*> mvLevelNumbers;
	

public:
	// constrcuter destructer
	StateBar();
	~StateBar();

	// delete Function
	StateBar(const StateBar& _Other) = delete;
	StateBar(StateBar&& _Other) noexcept = delete;
	StateBar& operator=(const StateBar& _Other) = delete;
	StateBar& operator=(StateBar&& _Other) noexcept = delete;

	// void SetHPGauge(float _fDamage)

	void SetLevelFont(unsigned int _nLevel);

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:

};

