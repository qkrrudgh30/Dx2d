#include "PreCompile.h"
#include "Inventory.h"

#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include <GameEngineCore/GameEngineFontRenderer.h>
#include "Player.h"

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
{
	spInventory = this;
	mfWidth = 175.f;
	mfHeight = 289.f;

}

Inventory::~Inventory() 
{
}

void Inventory::Start()
{
	mpRenderer = CreateComponent<GameEngineUIRenderer>("InventoryBackGround");
	mpRenderer->SetTexture("InventoryBackGround.png");
	// mpRenderer->SetScaleModeImage();
	mpRenderer->GetTransform().SetLocalScale(float4{ mfWidth, mfHeight, 1.f, 1.f });
	mpRenderer->SetPivot(PIVOTMODE::LEFTTOP);

	mpETCRenderer = CreateComponent<GameEngineUIRenderer>("EtcRenderer");
	mpETCRenderer->SetTexture("ETCMenu.png",0);
	mpETCRenderer->ScaleToCutTexture(0);
	// mpETCRenderer->GetTransform().SetLocalScale(float4{22.f, 18.f, 1.f, 1.f});
	mpETCRenderer->GetTransform().SetLocalMove(float4{20.f, -34.f, 0.f, 0.f});

	mpFontRenderer = CreateComponent<GameEngineFontRenderer>();
	mpFontRenderer->SetText("0", "메이플스토리");
	mpFontRenderer->SetColor({ 0.0f, 0.0f, 0.0f });
	mpFontRenderer->SetSize(15.f);
	mpFontRenderer->SetLeftAndRightSort(LeftAndRightSort::RIGHT);
	mpFontRenderer->ChangeCamera(CAMERAORDER::UICAMERA);
	
	mpFontRenderer->SetScreenPostion(GetTransform().GetWorldPosition() + float4{ GameEngineWindow::GetScale().x / 2.f + mfWidth - 34.f, (GameEngineWindow::GetScale().y / 2.f) + mfHeight - 13.f, 0.f, 0.f });
	// mpFontRenderer->SetScreenPostion(GetTransform().GetWorldPosition());

	this->Off();
}

void Inventory::Update(float _DeltaTime)
{
	// mpETCRenderer->SetFrame(0);
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

#pragma region InventoryMesoRendering
	
	
#pragma endregion
	muAccMeso = spPlayer->GetAccMeso();
	mpFontRenderer->SetText(std::to_string(muAccMeso), "메이플스토리");

	
}

