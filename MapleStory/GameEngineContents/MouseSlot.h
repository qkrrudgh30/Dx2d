#pragma once
#include "Inventory.h"

// Ό³Έν :
class ItemInfo;
class MouseSlot : public GameEngineActor
{
private:
	static MouseSlot* spMouseSlot;
	GameEngineUIRenderer* mpRenderer;
	float mfWidth;
	float mfHeight;
	std::pair<GameEngineUIRenderer*, ItemInfo*> mpSelectedItemPointer;

public:
	// constrcuter destructer
	MouseSlot();
	~MouseSlot();

	// delete Function
	MouseSlot(const MouseSlot& _Other) = delete;
	MouseSlot(MouseSlot&& _Other) noexcept = delete;
	//MouseSlot& operator=(const MouseSlot& _Other) = delete;
	MouseSlot& operator=(MouseSlot&& _Other) noexcept = delete;

	void SetRenderer(const std::string& _Name);

	static MouseSlot* GetMouseSlot() { return spMouseSlot; }

	const std::pair<GameEngineUIRenderer*, ItemInfo*>& GetSelectedItemPointer() 
	{
		return mpSelectedItemPointer;
	}

	void SetSelectedItemPointer(const std::pair<GameEngineUIRenderer*, ItemInfo*>& _pSelectedItem);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:

};

