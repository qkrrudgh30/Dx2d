#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class GameEngineUIRenderer;
class ETCMenuButton;
class GameEngineFontRenderer;
class Inventory : public GameEngineActor
{
private:
	static Inventory* spInventory;
	float mfWidth;
	float mfHeight;
	static Player* spPlayer;
	GameEngineTextureRenderer* mpRenderer;
	GameEngineUIRenderer* mpETCRenderer;
	GameEngineUIRenderer* mpConsumptionRenderer;
	float4 mf4TitlePos;
	float4 mf4MousePos;
	float4 mf4MouseDownPos;
	float4 mf4MouseDownInvenPos;
	float4 mf4MouseUpPos;
	float4 mf4MouseUpInvenPos;
	bool   mbOnTitle;
	bool   mbOnDrag;
	unsigned int muAccMeso;
	float4 mf4MesoFontPosition;
	GameEngineFontRenderer* mpFontRenderer;

	// std::vector<int> 


public:
	// constrcuter destructer
	Inventory();
	~Inventory();

	// delete Function
	Inventory(const Inventory& _Other) = delete;
	Inventory(Inventory&& _Other) noexcept = delete;
	Inventory& operator=(const Inventory& _Other) = delete;
	Inventory& operator=(Inventory&& _Other) noexcept = delete;

	static Inventory* GetInventory() { return spInventory; }

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() {}

private:

};

