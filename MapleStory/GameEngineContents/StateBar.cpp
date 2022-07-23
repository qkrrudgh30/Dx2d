#include "PreCompile.h"
#include "StateBar.h"
#include "Menu.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineContents/GlobalContentsValue.h>
#include <GameEngineCore/GameEngineRenderingPipeLine.h>
#include <GameEngineCore/GameEngineVertexShader.h>
#include <GameEngineCore/GameEngineConstantBuffer.h>
#include <GameEngineCore/GameEngineDevice.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

StateBar::StateBar() 
{
}

StateBar::~StateBar() 
{
}

void StateBar::Start()
{
	mf4CameraPos = GetLevel()->GetMainCameraActorTransform().GetLocalPosition();

	mpBackGroundRenderer = CreateComponent<GameEngineTextureRenderer>();
	mpBackGroundRenderer->SetTexture("BackGround.png");
	mpBackGroundRenderer->GetTransform().SetWorldScale(float4{ GameEngineWindow::GetScale().x, 71.f, 1.f, 1.f });

	mpLevelBackGroundRenderer = CreateComponent<GameEngineTextureRenderer>();
	mpLevelBackGroundRenderer->SetTexture("LevelBackGround.png");
	mpLevelBackGroundRenderer->GetTransform().SetWorldScale(float4{ GameEngineWindow::GetScale().x * 0.7125f + 10.f, 71.f, 1.f, 1.f });

	mpGaugeBarRenderer = CreateComponent<GameEngineTextureRenderer>();
	mpGaugeBarRenderer->SetTexture("GaugeBar.png");
	mpGaugeBarRenderer->GetTransform().SetWorldScale(float4{ GameEngineWindow::GetScale().x * 0.425f, 31.f, 1.f, 1.f });

	mpGaugeBackGroundRenderer = CreateComponent<GameEngineTextureRenderer>();
	mpGaugeBackGroundRenderer->SetTexture("GaugeBackGround.png");
	mpGaugeBackGroundRenderer->GetTransform().SetWorldScale(float4{ GameEngineWindow::GetScale().x * 0.425f, 31.f, 1.f, 1.f });

	mpCashShopButtonRenderer = CreateComponent<GameEngineTextureRenderer>();
	mpCashShopButtonRenderer->SetTexture("CashShopButton.png");
	mpCashShopButtonRenderer->GetTransform().SetWorldScale(float4{ GameEngineWindow::GetScale().x * 0.09125f, 35.f, 1.f, 1.f });

	mpShortCutButtonRenderer = CreateComponent<GameEngineTextureRenderer>();
	mpShortCutButtonRenderer->SetTexture("ShortCutButton.png");
	mpShortCutButtonRenderer->GetTransform().SetWorldScale(float4{ GameEngineWindow::GetScale().x * 0.09125f, 35.f, 1.f, 1.f });

	mpMenu = GetLevel()->CreateActor<Menu>();
}

void StateBar::Update(float _DeltaTime)
{
	mf4CameraPos = GetLevel()->GetMainCameraActorTransform().GetLocalPosition();
	mpBackGroundRenderer->GetTransform().SetWorldPosition(float4{ mf4CameraPos.x, mf4CameraPos.y - GameEngineWindow::GetScale().y / 2.f + 35.f, 1.f, 1.f });
	mpLevelBackGroundRenderer->GetTransform().SetWorldPosition(float4{ mf4CameraPos.x - GameEngineWindow::GetScale().x / 2.f + (GameEngineWindow::GetScale().x * 0.7125f * 0.5f) + 10.f, mf4CameraPos.y - GameEngineWindow::GetScale().y / 2.f + 35.f, 1.f, 1.f});
	mpGaugeBackGroundRenderer->GetTransform().SetWorldPosition(float4{ mf4CameraPos.x - 23.f, mf4CameraPos.y - GameEngineWindow::GetScale().y / 2.f + 20.f, 1.f, 1.f });
	mpGaugeBarRenderer->GetTransform().SetWorldPosition(float4{ mf4CameraPos.x - 23.f, mf4CameraPos.y - GameEngineWindow::GetScale().y / 2.f + 20.f, 1.f, 1.f });
	mpCashShopButtonRenderer->GetTransform().SetWorldPosition(float4{ mf4CameraPos.x + 350.f, mf4CameraPos.y - GameEngineWindow::GetScale().y / 2.f + 17.f, 1.f, 1.f });
	mpShortCutButtonRenderer->GetTransform().SetWorldPosition(float4{ GameEngineWindow::GetScale().x * 0.09125f * 1.95f + mf4CameraPos.x + 350.f, mf4CameraPos.y - GameEngineWindow::GetScale().y / 2.f + 17.f, 1.f, 1.f });
	mpMenu->GetTransform().SetWorldPosition(float4{ GameEngineWindow::GetScale().x * 0.09125f + mf4CameraPos.x + 350.f, mf4CameraPos.y - GameEngineWindow::GetScale().y / 2.f + 17.f, 1.f, 1.f });
	mpMenu->SetPositionX(GameEngineWindow::GetScale().x * 0.09125f + mf4CameraPos.x + 350.f);
	mpMenu->SetPositionY(mf4CameraPos.y - GameEngineWindow::GetScale().y / 2.f + 17.f);
}

