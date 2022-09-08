#include "PreCompile.h"
#include "Inventory.h"
#include "Player.h"
#include "MouseSlot.h"

#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include <GameEngineCore/GameEngineFontRenderer.h>

#include <queue>

Player* Inventory::spPlayer = nullptr;
Inventory* Inventory::spInventory = nullptr;

Inventory::Inventory() 
	: mfWidth(0.f)
	, mfHeight(0.f)
	, mpRenderer(nullptr)
	, mpETCRenderer(nullptr)
	, mpConsumptionRenderer(nullptr)
	, mf4TitlePos()
	, mf4MousePos()
	, mf4MouseDownPos()
	, mf4MouseUpPos()
	, mbOnTitle(false)
	, muAccMeso(0u)
	, mf4MesoFontPosition()
	, mbOnDrag(false)
	, muItemsIndex(0u)
	, mbInvenOnOff(true)
{
	spInventory = this;
	mfWidth = 175.f;
	mfHeight = 289.f;
	mvItemsVector.reserve(static_cast<size_t>(InventoryInfo::InventorySize));
	mvItemCountFont.reserve(static_cast<size_t>(InventoryInfo::InventorySize));
}

Inventory::~Inventory() 
{
}

void Inventory::RendererOnOff()
{
	mpRenderer->OnOffSwitch();

	auto begIter = mvItemsVector.begin();
	auto endIter = mvItemsVector.end();
	while (begIter != endIter)
	{
		begIter->first->OnOffSwitch();

		++begIter;
	}

	for (int i = 0; i < mvItemCountFont.size(); ++i)
	{
		mvItemCountFont[i]->OnOffSwitch();
	}

	mpFontRenderer->OnOffSwitch();

	mbInvenOnOff = !mbInvenOnOff;
}

int Inventory::FindItem(int _nObjectOrder)
{
	for (int i = 0; i < mvItemsVector.size(); ++i)
	{
		if (_nObjectOrder == mvItemsVector[i].second.mnItemType)
		{
			return i;
		}
	}

	return -1;
}

void Inventory::Start()
{
	mpRenderer = CreateComponent<GameEngineUIRenderer>("InventoryBackGround");
	mpRenderer->SetTexture("InventoryBackGround.png");
	mpRenderer->GetTransform().SetLocalScale(float4{ mfWidth, mfHeight, 1.f, 1.f });
	mpRenderer->SetPivot(PIVOTMODE::LEFTTOP);

	mpFontRenderer = CreateComponent<GameEngineFontRenderer>();
	mpFontRenderer->SetText("0", "메이플스토리");
	mpFontRenderer->SetColor({ 0.0f, 0.0f, 0.0f });
	mpFontRenderer->SetSize(15.f);
	mpFontRenderer->SetLeftAndRightSort(LeftAndRightSort::RIGHT);
	mpFontRenderer->ChangeCamera(CAMERAORDER::UICAMERA);
	
	mpFontRenderer->SetScreenPostion(GetTransform().GetWorldPosition() + float4{ GameEngineWindow::GetScale().x / 2.f + mfWidth - 34.f, (GameEngineWindow::GetScale().y / 2.f) + mfHeight - 13.f, 0.f, 0.f });

	ItemInfo emptyItemInfo = ItemInfo{};
	for (int i = 0; i < static_cast<int>(InventoryInfo::InventorySize); ++i)
	{
		GameEngineUIRenderer* ItemSlot = CreateComponent<GameEngineUIRenderer>("ItemSlot" + std::to_string(i));
		ItemSlot->SetPivot(PIVOTMODE::LEFTTOP);
		ItemSlot->GetTransform().SetLocalScale(float4{ static_cast<float>(InventoryInfo::ItemWidth), static_cast<float>(InventoryInfo::ItemHeight), 1.f, 1.f });
		mvItemsVector.push_back(std::make_pair(ItemSlot, emptyItemInfo));

		int j = i / 4;
		int k = i % 4;
		mvItemsVector[4 * j + k].first->GetTransform().SetLocalPosition(float4{
					35.f * k + 9.f,
					-34.f * j - 50.f,
					mvItemsVector[4 * j + k].first->GetTransform().GetWorldPosition().z,
					mvItemsVector[4 * j + k].first->GetTransform().GetWorldPosition().w,
			});

		GameEngineFontRenderer* ItemSlotFont = CreateComponent<GameEngineFontRenderer>();
		ItemSlotFont->SetText("0", "메이플스토리");
		// ItemSlotFont->Off();
		ItemSlotFont->SetColor({ 0.0f, 0.0f, 0.0f });
		ItemSlotFont->SetSize(15.f);
		ItemSlotFont->SetLeftAndRightSort(LeftAndRightSort::RIGHT);
		ItemSlotFont->SetScreenPostion( float4{
				GetTransform().GetWorldPosition().x + 35.f * k + 9.f,
				-(GetTransform().GetWorldPosition().y - 35.f * j - 50.f),
		});
		ItemSlotFont->ChangeCamera(CAMERAORDER::UICAMERA);
		mvItemCountFont.push_back(ItemSlotFont);
	}

	mpMouseSlot = GetLevel()->CreateActor<MouseSlot>(OBJECTORDER::UI);
	mpMouseSlot->SetLevelOverOn();

	RendererOnOff();
}

void Inventory::Update(float _DeltaTime)
{
	if (nullptr == spPlayer)
	{
		spPlayer = Player::GetPlayer();
		return;		
	}

#pragma region InventoryDragDrop
	mf4MousePos = GetLevel()->GetUICamera()->GetMouseWorldPosition() + float4{ GameEngineWindow::GetScale().x / 2.f, -GameEngineWindow::GetScale().y / 2.f, 0.f, 0.f};
	mf4TitlePos = mpRenderer->GetTransform().GetWorldPosition() + float4{ GameEngineWindow::GetScale().x / 2.f, -GameEngineWindow::GetScale().y / 2.f, 0.f, 0.f };

	if (mf4TitlePos.x <= mf4MousePos.x && mf4MousePos.x <= mf4TitlePos.x + mfWidth
		&& mf4MousePos.y <= mf4TitlePos.y && mf4TitlePos.y - 30.f <= mf4MousePos.y)
	{
		mbOnTitle = true;
	}
	else
	{
		mbOnTitle = false;
	}

	if (true == mbOnTitle && true == GameEngineInput::GetInst()->IsDown("MouseLButtonDown"))
	{
		mf4MouseDownPos = mf4MousePos;
		mf4MouseDownInvenPos = GetTransform().GetWorldPosition();
		mbOnDrag = true;
	}

	if (true == mbOnDrag && true == GameEngineInput::GetInst()->IsUp("MouseLButtonDown"))
	{
		mf4MouseUpPos = mf4MousePos - float4{ GameEngineWindow::GetScale().x / 2.f, -GameEngineWindow::GetScale().y / 2.f, 0.f, 0.f };
		float4 pos = float4{ mf4MouseUpPos.x, mf4MouseUpPos.y, GetTransform().GetWorldPosition().z, 1.f};
		GetTransform().SetWorldPosition(pos);
		mf4MouseUpInvenPos = pos;
		mf4MesoFontPosition = mpFontRenderer->GetScreenPostion() + float4{ -(mf4MouseDownInvenPos.x - pos.x), (mf4MouseDownInvenPos.y - pos.y), 0.f, 0.f};
		mpFontRenderer->SetScreenPostion(mf4MesoFontPosition);
		mbOnDrag = false;
	}
#pragma endregion

#pragma region InventoryItemRendering
	for (size_t i = 0; i < spPlayer->GetItemsQueue().size(); ++i)
	{
		int item = spPlayer->GetItemInQueue();
		int res = FindItem(item);
		if (-1 == res)
		{
			mvItemsVector[muItemsIndex].second.mnItemType = item;
			++mvItemsVector[muItemsIndex].second.muItemCount;
			++muItemsIndex;
		}
		else
		{
			++mvItemsVector[res].second.muItemCount;
		}
	}
	

	for (size_t i = 0; i < static_cast<size_t>(InventoryInfo::InventoryHeight); ++i)
	{
		for (size_t j = 0; j < static_cast<size_t>(InventoryInfo::InventoryWidth); ++j)
		{
			mvItemCountFont[4 * i + j]->SetScreenPostion(float4{
				GameEngineWindow::GetScale().x / 2.f + GetTransform().GetWorldPosition().x + 35.f * j + 40.f,
				-(GameEngineWindow::GetScale().y / -2.f + GetTransform().GetWorldPosition().y - 35.f * i - 70.f),
				});

			if (0u == mvItemsVector[4 * i + j].second.muItemCount)
			{
				mvItemsVector[4 * i + j].first->SetTexture("Clear.png");
				mvItemCountFont[4 * i + j]->Off();
			}
			else
			{
				if (true == mbInvenOnOff) { mvItemCountFont[4 * i + j]->On(); }
				mvItemCountFont[4 * i + j]->SetText(std::to_string(mvItemsVector[4 * i + j].second.muItemCount), "메이플스토리");
				switch (mvItemsVector[4 * i + j].second.mnItemType)
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

#pragma region ItemDrag
	float4 f4MouseSlotPosition = mpMouseSlot->GetTransform().GetWorldPosition();

	for (size_t i = 0; i < static_cast<size_t>(InventoryInfo::InventoryHeight); ++i)
	{
		for (size_t j = 0; j < static_cast<size_t>(InventoryInfo::InventoryWidth); ++j)
		{
			float4 MouseOnItemCheckPosition = mvItemsVector[4 * i + j].first->GetTransform().GetWorldPosition();

			if (MouseOnItemCheckPosition.x <= f4MouseSlotPosition.x && f4MouseSlotPosition.x <= MouseOnItemCheckPosition.x + mfWidth
				&& f4MouseSlotPosition.y <= MouseOnItemCheckPosition.y && MouseOnItemCheckPosition.y - 30.f <= f4MouseSlotPosition.y)
			{
				if (true == GameEngineInput::GetInst()->IsDown("MouseLButtonDown"))
				{
					std::string name = mvItemsVector[4 * i + j].first->GetCurTexture()->GetNameCopy();
					mpMouseSlot->SetRenderer(name);
					mpMouseSlot->SetSelectedItemPointer(mvItemsVector[4 * i + j]);
				}
			}
		}
	}
#pragma endregion


	muAccMeso = spPlayer->GetAccMeso();
	mpFontRenderer->SetText(std::to_string(muAccMeso), "메이플스토리");

	
}

