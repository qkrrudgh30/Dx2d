#pragma once


// Ό³Έν :
class ItemInfo
{
public:
	int mnItemType;
	unsigned int muItemCount;

public:
	// constrcuter destructer
	ItemInfo()
		: mnItemType(static_cast<int>(OBJECTORDER::End))
		, muItemCount(0u)
	{

	}

	~ItemInfo() {};

	// delete Function
	// ItemInfo(const ItemInfo& _Other) = delete;
	// ItemInfo(ItemInfo&& _Other) noexcept = delete;
	// ItemInfo& operator=(const ItemInfo& _Other) = delete;
	// ItemInfo& operator=(ItemInfo&& _Other) noexcept = delete;

protected:

private:

};
