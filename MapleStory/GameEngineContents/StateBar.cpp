#include "PreCompile.h"
#include "StateBar.h"
#include "MenuButton.h"
#include "HPGauge.h"
#include "MPGauge.h"
#include "EXPGauge.h"
#include "QuickSlot.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineContents/GlobalContentsValue.h>
#include <GameEngineCore/GameEngineRenderingPipeLine.h>
#include <GameEngineCore/GameEngineVertexShader.h>
#include <GameEngineCore/GameEngineConstantBuffer.h>
#include <GameEngineCore/GameEngineDevice.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include <GameEngineCore/GameEngineUIRenderer.h>

StateBar::StateBar() 
{
}

StateBar::~StateBar() 
{
}

void StateBar::Start()
{
	mpBackGroundRenderer = CreateComponent<GameEngineUIRenderer>();
	mpBackGroundRenderer->SetTexture("BackGround.png");
	mpBackGroundRenderer->GetTransform().SetLocalScale(float4{ GameEngineWindow::GetScale().x, 71.f, 1.f, 1.f });
	mpBackGroundRenderer->GetTransform().SetLocalPosition(float4{ 0.f, -GameEngineWindow::GetScale().y / 2.f + 35.f, OBJECTORDER::UIBackGround, 1.f});

	mpLevelBackGroundRenderer = CreateComponent<GameEngineUIRenderer>();
	mpLevelBackGroundRenderer->SetTexture("LevelBackGround.png");
	mpLevelBackGroundRenderer->GetTransform().SetLocalScale(float4{ GameEngineWindow::GetScale().x * 0.7125f + 10.f, 71.f, 1.f, 1.f });
	mpLevelBackGroundRenderer->GetTransform().SetLocalPosition(float4{ -GameEngineWindow::GetScale().x / 2.f + (GameEngineWindow::GetScale().x * 0.7125f + 10.f)/ 2.f, -GameEngineWindow::GetScale().y / 2.f + 35.f, OBJECTORDER::UIBackBoard, 1.f });
	
	mpGaugeNamesRenderer = CreateComponent<GameEngineUIRenderer>();
	mpGaugeNamesRenderer->SetTexture("GaugeNames.png");
	mpGaugeNamesRenderer->GetTransform().SetLocalScale(float4{ GameEngineWindow::GetScale().x * 0.3075f, 13.f, 1.f, 1.f });
	mpGaugeNamesRenderer->GetTransform().SetLocalPosition(float4{ -100.f, -GameEngineWindow::GetScale().y / 2.f + 26.f, OBJECTORDER::UIGaugeBG, 1.f });

	mpHPGauge = GetLevel()->CreateActor<HPGauge>();
	mpHPGauge->GetTransform().SetLocalPosition(float4{ -296.f, -(GameEngineWindow::GetScale().y / 2.f) + 20.f, OBJECTORDER::UIGauge, 1.f });
	mpMPGauge = GetLevel()->CreateActor<MPGauge>();
	mpMPGauge->GetTransform().SetLocalPosition(float4{ -124.f, -GameEngineWindow::GetScale().y / 2.f + 20.f, OBJECTORDER::UIGauge, 1.f });
	mpEXPGauge = GetLevel()->CreateActor<EXPGauge>();
	mpEXPGauge->GetTransform().SetLocalPosition(float4{ 58.f, -GameEngineWindow::GetScale().y / 2.f + 20.f, OBJECTORDER::UIGauge, 1.f });

	mpGaugeBackGroundRenderer = CreateComponent<GameEngineUIRenderer>();
	mpGaugeBackGroundRenderer->SetTexture("GaugeBackGround.png");
	mpGaugeBackGroundRenderer->GetTransform().SetLocalScale(float4{ GameEngineWindow::GetScale().x * 0.425f, 31.f, 1.f, 1.f });
	mpGaugeBackGroundRenderer->GetTransform().SetLocalPosition(float4{ -25.f, -GameEngineWindow::GetScale().y / 2.f + 17.f, OBJECTORDER::UIGaugeBG, 1.f });

	mpCashShopButtonRenderer = CreateComponent<GameEngineUIRenderer>();
	mpCashShopButtonRenderer->SetTexture("CashShopButton.png");
	mpCashShopButtonRenderer->GetTransform().SetLocalScale(float4{ GameEngineWindow::GetScale().x * 0.09125f, 35.f, 1.f, 1.f });
	mpCashShopButtonRenderer->GetTransform().SetLocalPosition(float4{ 345.f, -GameEngineWindow::GetScale().y / 2.f + 17.f, OBJECTORDER::UIGaugeBG, 1.f });

	mpShortCutButtonRenderer = CreateComponent<GameEngineUIRenderer>();
	mpShortCutButtonRenderer->SetTexture("ShortCutButton.png");
	mpShortCutButtonRenderer->GetTransform().SetLocalScale(float4{ GameEngineWindow::GetScale().x * 0.09125f, 35.f, 1.f, 1.f });
	mpShortCutButtonRenderer->GetTransform().SetLocalPosition(float4{ 579.f, -GameEngineWindow::GetScale().y / 2.f + 17.f, OBJECTORDER::UIGauge-1, 1.f });

	mpQuickSlot = GetLevel()->CreateActor<QuickSlot>();
	mpQuickSlot->GetTransform().SetLocalPosition(float4{ 565.f, -255.f, OBJECTORDER::UIGauge, 1.f });


	mpMenuButton = GetLevel()->CreateActor<MenuButton>();
	
}

void StateBar::Update(float _DeltaTime)
{
	//GameEngineDebug::OutPutString(
	//	std::to_string(mpBackGroundRenderer->GetTransform().GetWorldPosition().x) + "  " +
	//	std::to_string(mpBackGroundRenderer->GetTransform().GetWorldPosition().y) + "  " +
	//	std::to_string(mpBackGroundRenderer->GetTransform().GetWorldPosition().z) + "  " +
	//	std::to_string(mpLevelBackGroundRenderer->GetTransform().GetWorldPosition().z) + "  " +
	//	std::to_string(mpGaugeNamesRenderer->GetTransform().GetWorldPosition().z) + "  " +
	//	std::to_string(mpGaugeBackGroundRenderer->GetTransform().GetWorldPosition().z) + "  " +
	//	std::to_string(mpCashShopButtonRenderer->GetTransform().GetWorldPosition().z) + "  " +
	//	std::to_string(mpShortCutButtonRenderer->GetTransform().GetWorldPosition().z));
}

