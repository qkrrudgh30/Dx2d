#include "PreCompile.h"
#include "Store.h"
#include "Inventory.h"
#include "Player.h"
#include "MouseSlot.h"

#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include <GameEngineCore/GameEngineFontRenderer.h>

enum { SELLINGITEMCOUNT = 5 };

Store::Store() 
	: mpInventory(nullptr)
	, spPlayer(nullptr)
	, mpFontRenderer(nullptr)
	, mpRenderer(nullptr)
	, mpBuyButtonRenderer(nullptr)
	, mpExitButtonRenderer(nullptr)
	, mfWidth(233.f)
	, mfHeight(318.f)
	, muAccMeso(0u)
	, mnSelectedIndex(15)
{
	mvItemsVector.reserve(static_cast<size_t>(SELLINGITEMCOUNT));
}

Store::~Store() 
{
}

void Store::Start()
{
	mpRenderer = CreateComponent<GameEngineUIRenderer>("StoreBackGround");
	mpRenderer->SetTexture("StoreBackGround.png");
	mpRenderer->GetTransform().SetLocalScale(float4{ mfWidth, mfHeight, 1.f, 1.f });

	mpFontRenderer = CreateComponent<GameEngineFontRenderer>();
	mpFontRenderer->SetText("0", "메이플스토리");
	mpFontRenderer->SetColor({ 0.0f, 0.0f, 0.0f });
	mpFontRenderer->SetSize(15.f);
	mpFontRenderer->SetLeftAndRightSort(LeftAndRightSort::RIGHT);
	mpFontRenderer->ChangeCamera(CAMERAORDER::UICAMERA);
	// mpFontRenderer->SetScreenPostion(GetTransform().GetWorldPosition() + float4{ GameEngineWindow::GetScale().x / 2.f + mfWidth - 34.f, (GameEngineWindow::GetScale().y / 2.f) + mfHeight - 13.f, 0.f, 0.f });
	mpFontRenderer->SetScreenPostion(float4{ (GameEngineWindow::GetScale().x+mfWidth) / 2.f - 40.f , (GameEngineWindow::GetScale().y+mfHeight) / 2.f - 23.f});
	this->Off();

	mpBuyButtonRenderer = CreateComponent<GameEngineUIRenderer>("BuyButtonRenderer");
	mpBuyButtonRenderer->SetTexture("StoreBuyButton.png", 0);
	mpBuyButtonRenderer->GetTransform().SetLocalScale(float4{ 39.f, 18.f, 1.f, 1.f });
	mpBuyButtonRenderer->GetTransform().SetLocalMove(float4{ 30.f, 100.f, 0.f, 0.f });
	mpExitButtonRenderer = CreateComponent<GameEngineUIRenderer>("BuyButtonRenderer");
	mpExitButtonRenderer->GetTransform().SetLocalScale(float4{ 39.f, 18.f, 1.f, 1.f });
	mpExitButtonRenderer->GetTransform().SetLocalMove(float4{ 80.f, 100.f, 0.f, 0.f });
	mpExitButtonRenderer->SetTexture("StoreExitButton.png", 0);

	mpSellectedRenderer = CreateComponent<GameEngineUIRenderer>("StoreSelected");
	mpSellectedRenderer->GetTransform().SetLocalScale(float4{ 202.f, 40.f, 1.f, 1.f });
	mpSellectedRenderer->GetTransform().SetLocalPosition(float4{ -12.f, 55.f, 0.f, 0.f });
	mpSellectedRenderer->SetTexture("StoreSelected.png");

	float4 f4ItemPositions;
	for (int i = 0; i < static_cast<int>(SELLINGITEMCOUNT); ++i)
	{
		f4ItemPositions = float4{-12.f, 55.f - 40 * i, 0.f, 0.f};
		mvItemsPositions.push_back(f4ItemPositions);
	}
	mpSellectedRenderer->GetTransform().SetLocalPosition(mvItemsPositions[0]);

	float fSellingItemSlotWidth = 200.f;
	float fSellingItemSlotHeight = 38.f;
	for (int i = 0; i < static_cast<int>(SELLINGITEMCOUNT); ++i)
	{
		GameEngineUIRenderer* ItemSlot = CreateComponent<GameEngineUIRenderer>("SellingItemSlot" + std::to_string(i));
		// ItemSlot->SetPivot(PIVOTMODE::LEFTTOP);
		ItemSlot->GetTransform().SetLocalScale(float4{ fSellingItemSlotWidth, fSellingItemSlotHeight, 1.f, 1.f });
		ItemSlot->GetTransform().SetLocalPosition(mvItemsPositions[i]);	
		ItemSlot->SetTexture("Clear.png");
		mvItemsVector.push_back(ItemSlot);
	}

	mvItemsVector[0]->SetTexture("SellingWhitePortion.png");
	mvItemsVector[1]->SetTexture("SellingBluePortion.png");
}

void Store::Update(float _DeltaTime)
{
	if (nullptr == spPlayer)
	{
		spPlayer = Player::GetPlayer();
		return;
	}
	muAccMeso = spPlayer->GetAccMeso();

#pragma region SelectItem
	float4 f4MouseSlotPosition = GetLevel()->GetUICamera()->GetMouseWorldPosition();

	for (size_t i = 0; i < static_cast<size_t>(SELLINGITEMCOUNT); ++i)
	{
		float4 MouseOnItemCheckPosition = mvItemsPositions[i];
		
		if (
			MouseOnItemCheckPosition.x - 100.f <= f4MouseSlotPosition.x && f4MouseSlotPosition.x <= MouseOnItemCheckPosition.x + 100.f &&
			MouseOnItemCheckPosition.y - 20.f <= f4MouseSlotPosition.y && f4MouseSlotPosition.y <= MouseOnItemCheckPosition.y + 20.f
			)
		{
			if (true == GameEngineInput::GetInst()->IsDown("MouseLButtonDown"))
			{
				mSoundPlayer = GameEngineSound::SoundPlayControl("BtMouseClick.mp3");
				mpSellectedRenderer->GetTransform().SetLocalPosition(mvItemsPositions[i]);
				mnSelectedIndex = i == 0u ? 15 : 16;
			}
		}
	}
#pragma endregion

#pragma region Button
	float mfButtonWidth = 39.f;
	float mfButtonHeight = 18.f;

	float4 mf4MousePos = GetLevel()->GetUICamera()->GetMouseWorldPosition();
	float4 mf4ButtonPos = mpBuyButtonRenderer->GetTransform().GetWorldPosition();
	if (mf4ButtonPos.x - (mfButtonWidth / 2) <= mf4MousePos.x && mf4MousePos.x <= mf4ButtonPos.x + (mfButtonWidth / 2)
		&& mf4ButtonPos.y - (mfButtonHeight / 2) <= mf4MousePos.y && mf4MousePos.y <= mf4ButtonPos.y + (mfButtonHeight / 2))
	{
		mpBuyButtonRenderer->SetFrame(1);
		if (true == GameEngineInput::GetInst()->IsDown("MouseLButtonDown"))
		{
			mpBuyButtonRenderer->SetFrame(2);
			if (50u <= muAccMeso)
			{
				mSoundPlayer = GameEngineSound::SoundPlayControl("BtMouseClick.mp3");
				spPlayer->SetAccMeso(spPlayer->GetAccMeso() - 50u);
				spPlayer->PushItemInQueue(mnSelectedIndex);
			}

		}
	}
	else
	{
		mpBuyButtonRenderer->SetFrame(0);
	}

	mf4ButtonPos = mpExitButtonRenderer->GetTransform().GetWorldPosition();
	if (mf4ButtonPos.x - (mfButtonWidth / 2) <= mf4MousePos.x && mf4MousePos.x <= mf4ButtonPos.x + (mfButtonWidth / 2)
		&& mf4ButtonPos.y - (mfButtonHeight / 2) <= mf4MousePos.y && mf4MousePos.y <= mf4ButtonPos.y + (mfButtonHeight / 2))
	{
		mpExitButtonRenderer->SetFrame(1);
		if (true == GameEngineInput::GetInst()->IsPress("MouseLButtonDown"))
		{
			mSoundPlayer = GameEngineSound::SoundPlayControl("BtMouseClick.mp3");
			mpExitButtonRenderer->SetFrame(2);
			this->Off();
		}
	}
	else
	{
		mpExitButtonRenderer->SetFrame(0);
	}
#pragma endregion


	muAccMeso = spPlayer->GetAccMeso();
	mpFontRenderer->SetText(std::to_string(muAccMeso), "메이플스토리");

	mSoundPlayer.Volume(0.1f);
}

