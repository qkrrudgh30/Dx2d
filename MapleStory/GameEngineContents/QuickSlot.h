#pragma once
#include "ItemInfo.h"

enum class QuickSlotInfo
{
	QuickSlotSize = 8,
	QuickSlotWidth = 4,
	QuickSlotHeight = 2,
	ItemWidth = 32,
	ItemHeight = 32,
	ItemWidthOffset = 10,
	ItemHeightOffset = 10,
};


// Ό³Έν :
class GameEngineTextureRenderer;
class GameEngineUIRenderer;
class ETCMenuButton;
class GameEngineFontRenderer;
class MouseSlot;
class ItemInfo;
class GameEngineSoundPlayer;
class QuickSlot : public GameEngineActor
{
private:
	GameEngineUIRenderer* mpUIRenderer;
	GameEngineUIRenderer* mpEmptyRenderer;
	ItemInfo              mEmptyItemInfo;
	float                 mfWidth;
	float                 mfHeight;
	GameEngineSoundPlayer mSoundPlayer;

	static Inventory* spInventory;
	static Player* spPlayer;
	static QuickSlot* spQuickSlot;
	GameEngineTextureRenderer* mpRenderer;
	std::vector<std::pair<GameEngineUIRenderer*, ItemInfo>> mvItemsVector;
	std::vector<std::pair<GameEngineUIRenderer*, ItemInfo>*> mvOriginalItemsVector;
	std::vector<GameEngineFontRenderer*> mvItemCountFont;
	std::vector<GameEngineFontRenderer*> mvHotKeyFont;
	std::vector<std::string> mvHotkeyStrings;
	unsigned int muItemsIndex;
	MouseSlot* mpMouseSlot;
	std::pair<GameEngineUIRenderer*, ItemInfo> mpEmpty;

public:
	// constrcuter destructer
	QuickSlot();
	~QuickSlot();

	// delete Function
	QuickSlot(const QuickSlot& _Other) = delete;
	QuickSlot(QuickSlot&& _Other) noexcept = delete;
	QuickSlot& operator=(const QuickSlot& _Other) = delete;
	QuickSlot& operator=(QuickSlot&& _Other) noexcept = delete;

	static QuickSlot* GetQuickSlot() { return spQuickSlot; }

	int Consume(int _Key);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {}

private:

};

