#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class GameEngineUIRenderer;
class ExitButton;
class BuyButton;
class GameEngineFontRenderer;
class Inventory;
class Store : public GameEngineActor
{
private:
	GameEngineUIRenderer*   mpRenderer;
	GameEngineUIRenderer*   mpBuyButtonRenderer;
	GameEngineUIRenderer*   mpExitButtonRenderer;
	GameEngineUIRenderer*   mpSellectedRenderer;
	Inventory*              mpInventory;
	GameEngineFontRenderer* mpFontRenderer;
	Player* spPlayer;
	float mfWidth;
	float mfHeight;
	std::vector<GameEngineUIRenderer*> mvItemsVector;
	std::vector<float4> mvItemsPositions;
	float4 mf4MousePosition;
	unsigned int muAccMeso;
	unsigned int mnSelectedIndex;

public:
	// constrcuter destructer
	Store();
	~Store();

	// delete Function
	Store(const Store& _Other) = delete;
	Store(Store&& _Other) noexcept = delete;
	Store& operator=(const Store& _Other) = delete;
	Store& operator=(Store&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() {}

private:

};

