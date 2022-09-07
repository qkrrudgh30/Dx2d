#include "PreCompile.h"
#include "QuickSlot.h"
#include "Player.h"
#include "Inventory.h"
#include "MouseSlot.h"

#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineFontRenderer.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

Player* QuickSlot::spPlayer = nullptr;
Inventory* QuickSlot::spInventory = nullptr;
QuickSlot* QuickSlot::spQuickSlot = nullptr;

QuickSlot::QuickSlot() 
	: mpUIRenderer(nullptr)
{
	spQuickSlot = this;
	mfWidth = 151.f;
	mfHeight = 80.f;
	mvItemsVector.reserve(static_cast<size_t>(QuickSlotInfo::QuickSlotSize));
	mvOriginalItemsVector.reserve(static_cast<size_t>(QuickSlotInfo::QuickSlotSize));
	mvItemCountFont.reserve(static_cast<size_t>(QuickSlotInfo::QuickSlotSize));
	mvHotKeyFont.reserve(static_cast<size_t>(QuickSlotInfo::QuickSlotSize));
	mvHotkeyStrings.reserve(static_cast<size_t>(QuickSlotInfo::QuickSlotSize));

	mvHotkeyStrings.push_back("Shift");
	mvHotkeyStrings.push_back("Ins");
	mvHotkeyStrings.push_back("Hm");
	mvHotkeyStrings.push_back("Pup");

	mvHotkeyStrings.push_back("Ctrl");
	mvHotkeyStrings.push_back("Del");
	mvHotkeyStrings.push_back("End");
	mvHotkeyStrings.push_back("Pdn");
}

QuickSlot::~QuickSlot() 
{
}

int QuickSlot::Consume(int _Key)
{
	if (0u == mvOriginalItemsVector[_Key].second->muItemCount) { return 0; }
	int nAmount = mvOriginalItemsVector[_Key].second->mnItemType;
	--mvOriginalItemsVector[_Key].second->muItemCount;
	return nAmount;
}

void QuickSlot::Start()
{
	mpUIRenderer = CreateComponent<GameEngineUIRenderer>();
	mpUIRenderer->SetTexture("QuickSlot.png");
	mpUIRenderer->GetTransform().SetLocalScale(float4{ mfWidth, mfHeight, 1.f, 1.f });

	ItemInfo* temp1 = new ItemInfo();
	GameEngineUIRenderer* temp2 = CreateComponent<GameEngineUIRenderer>();
	temp2->SetTexture("clear.png");
	std::pair<GameEngineUIRenderer*, ItemInfo*> pEmpty(temp2, temp1);
	mpEmpty = pEmpty;

	for (int i = 0; i < static_cast<int>(QuickSlotInfo::QuickSlotSize); ++i)
	{
		GameEngineUIRenderer* QuickSlot = CreateComponent<GameEngineUIRenderer>("QuickSlot" + std::to_string(i));
		QuickSlot->SetPivot(PIVOTMODE::LEFTTOP);
		QuickSlot->GetTransform().SetLocalScale(float4{ static_cast<float>(QuickSlotInfo::ItemWidth), static_cast<float>(QuickSlotInfo::ItemHeight), 1.f, 1.f });
		ItemInfo* temp = new ItemInfo();
		mvItemsVector.push_back(std::make_pair(QuickSlot, temp));
		mvOriginalItemsVector.push_back(std::make_pair(QuickSlot, temp));

		int j = i / 4;
		int k = i % 4;
		mvItemsVector[4 * j + k].first->GetTransform().SetLocalPosition(float4{
					35.f * k - 70.f,
					-34.f * j + 33.f,
					mvItemsVector[4 * j + k].first->GetTransform().GetWorldPosition().z,
					mvItemsVector[4 * j + k].first->GetTransform().GetWorldPosition().w,
			});

		GameEngineFontRenderer* ItemSlotFont = CreateComponent<GameEngineFontRenderer>();
		ItemSlotFont->SetText("0", "메이플스토리");
		ItemSlotFont->Off();
		ItemSlotFont->SetColor({ 0.0f, 0.0f, 0.0f });
		ItemSlotFont->SetSize(15.f);
		ItemSlotFont->SetLeftAndRightSort(LeftAndRightSort::RIGHT);
		// ItemSlotFont->SetScreenPostion(float4{
		// 		GetTransform().GetWorldPosition().x + 35.f * k - 70.f,
		// 		-(GetTransform().GetWorldPosition().y - 34.f * j + 33.f),
		// 	});
		// 565.f, -255.f,
		ItemSlotFont->SetScreenPostion(float4{
				GameEngineWindow::GetScale().x / 2.f + 565.f + 35.f * k - mfWidth / 2.f + 37.f,
				GameEngineWindow::GetScale().y / 2.f + 255.f + 34.f * j - mfHeight / 2.f + 24.f,
			});
		ItemSlotFont->ChangeCamera(CAMERAORDER::UICAMERA);
		mvItemCountFont.push_back(ItemSlotFont);

		GameEngineFontRenderer* HotKeyFont = CreateComponent<GameEngineFontRenderer>();
		HotKeyFont->SetText(mvHotkeyStrings[i], "메이플스토리");
		HotKeyFont->SetColor({ 0.0f, 0.0f, 0.0f });
		HotKeyFont->SetSize(10.f);
		HotKeyFont->SetLeftAndRightSort(LeftAndRightSort::RIGHT);
		HotKeyFont->SetScreenPostion(float4{
				GameEngineWindow::GetScale().x / 2.f + 565.f + 35.f * k - mfWidth / 2.f + 27.f,
				GameEngineWindow::GetScale().y / 2.f + 255.f + 34.f * j - mfHeight / 2.f + 6.f,
			});
		HotKeyFont->ChangeCamera(CAMERAORDER::UICAMERA);
		mvHotKeyFont.push_back(HotKeyFont);
	}

}

void QuickSlot::Update(float _DeltaTime)
{
	if (nullptr == spPlayer)
	{
		spPlayer = Player::GetPlayer();
		return;
	}
	if (nullptr == spInventory)
	{
		spInventory = Inventory::GetInventory();
	}

	if (nullptr == mpMouseSlot)
	{
		mpMouseSlot = MouseSlot::GetMouseSlot();
	}

#pragma region QuickSlotItemRendering

	for (size_t i = 0; i < static_cast<size_t>(QuickSlotInfo::QuickSlotHeight); ++i)
	{
		for (size_t j = 0; j < static_cast<size_t>(QuickSlotInfo::QuickSlotWidth); ++j)
		{
			// mvItemCountFont[4 * i + j]->SetScreenPostion(float4{
			// 	GameEngineWindow::GetScale().x / 2.f + GetTransform().GetWorldPosition().x + 35.f * j + 40.f,
			// 	-(GameEngineWindow::GetScale().y / -2.f + GetTransform().GetWorldPosition().y - 35.f * i - 70.f),
			// 	});
			if (nullptr == mvOriginalItemsVector[4 * i + j].second) { continue; }
			if (0u == mvOriginalItemsVector[4 * i + j].second->muItemCount)
			{
				mvItemsVector[4 * i + j].first->SetTexture("Clear.png");
				mvItemCountFont[4 * i + j]->Off();
				mvOriginalItemsVector[4 * i + j] = mpEmpty;
			}
			else
			{
				mvItemCountFont[4 * i + j]->On();
				mvItemCountFont[4 * i + j]->SetText(std::to_string(mvOriginalItemsVector[4 * i + j].second->muItemCount), "메이플스토리");
				switch (mvOriginalItemsVector[4 * i + j].second->mnItemType)
				{
				case static_cast<int>(OBJECTORDER::Portion1):
					mvItemsVector[4 * i + j].first->SetTexture("WhitePortion.png");
					break;
				case static_cast<int>(OBJECTORDER::Portion2):
					mvItemsVector[4 * i + j].first->SetTexture("BluePortion.png");
					break;
				case static_cast<int>(OBJECTORDER::Portion3):
					mvItemsVector[4 * i + j].first->SetTexture("Elixir.png");
					break;
				default:
					break;
				}
			}
		}
  	}

#pragma endregion

#pragma region ItemDrop
	float4 f4MouseSlotPosition = mpMouseSlot->GetTransform().GetWorldPosition();

	for (size_t i = 0; i < static_cast<size_t>(QuickSlotInfo::QuickSlotHeight); ++i)
	{
		for (size_t j = 0; j < static_cast<size_t>(QuickSlotInfo::QuickSlotWidth); ++j)
		{
			float4 MouseOnItemCheckPosition = mvItemsVector[4 * i + j].first->GetTransform().GetWorldPosition();

			if (MouseOnItemCheckPosition.x <= f4MouseSlotPosition.x && f4MouseSlotPosition.x <= MouseOnItemCheckPosition.x + 35.f
				&& f4MouseSlotPosition.y <= MouseOnItemCheckPosition.y && MouseOnItemCheckPosition.y - 34.f <= f4MouseSlotPosition.y)
			{
				if (true == GameEngineInput::GetInst()->IsUp("MouseLButtonDown"))
				{
					mvOriginalItemsVector[4 * i + j] = mpMouseSlot->GetSelectedItemPointer();
					// mvItemsVector[4 * i + j].second = mpMouseSlot->GetSelectedItemPointer().second;
					int a = 100;
				}
			}
		}
	}
#pragma endregion

}

