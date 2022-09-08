#include "PreCompile.h"
#include "TempleOfTime0.h"
#include "GlobalContentsValue.h"
#include "Player.h"
#include "Temple0BackGround.h"
#include "Temple0Tile.h"
#include "Temple0Cloud.h"
#include "PixelCollisionMap.h"
#include "Portal.h"
#include "Veil.h"
#include "StateBar.h"
#include "MenuButton.h"
#include "Temple2Monster.h"
#include "Inventory.h"
#include "MouseSlot.h"
#include "QuickSlot.h"

#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTransform.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineCore/GameEngineCamera.h>

#include <string>

TempleOfTime0::TempleOfTime0()
	: mpBackGround(nullptr)
	, mpTile(nullptr)
	, mpCloud(nullptr)
{
}

TempleOfTime0::~TempleOfTime0()
{
}

void TempleOfTime0::Start()
{
	mpCamera = GetMainCameraActor();
	mpCamera->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
	mpCamera->GetTransform().SetWorldPosition({0.0f, 0.0f, -500.0f});
	// GetMainCameraActor()->FreeCameraModeOnOff();

	SetMapSize(float4{2327.f, 955.f});
	
	mpBackGround = CreateActor<Temple0BackGround>(OBJECTORDER::UI);
	mpTile = CreateActor<Temple0Tile>(OBJECTORDER::UI);
	mpCloud = CreateActor<Temple0Cloud>(OBJECTORDER::UI);
	mpPCMap = CreateActor<PixelCollisionMap>(OBJECTORDER::UI);
	mpPCMap->SetInfo("Temple0TileP.png");
	mpPCMap->GetRenderer()->OnOffSwitch();
	
	float4 CenterPointOfMap = float4{ GetMapSize().x / 2.f, -(GetMapSize().y / 2.f), OBJECTORDER::UI, 0.f };
	mpBackGround->GetTransform().SetWorldPosition(CenterPointOfMap);
	mpTile->GetTransform().SetWorldPosition(CenterPointOfMap);
	mpCloud->GetTransform().SetWorldPosition(CenterPointOfMap + float4{0.f, 60.f, 0.f, 0.f});
	mpPCMap->GetTransform().SetWorldPosition(CenterPointOfMap);	

	mpPortalToNext = CreateActor<Portal>(OBJECTORDER::Character);
	mpPortalToNext->GetTransform().SetWorldPosition(float4{ 2000.f, -258.f, OBJECTORDER::Character, 1.f });

	mpStateBar = CreateActor<StateBar>(OBJECTORDER::UI);
	mpQuickSlot = CreateActor<QuickSlot>();
	mpQuickSlot->GetTransform().SetLocalPosition(float4{ 565.f, -255.f, OBJECTORDER::UIGauge, 1.f });

	mpVeil = CreateActor<Veil>(OBJECTORDER::UI);
	mpCamera->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
}

void TempleOfTime0::LevelStartEvent()
{
	if (nullptr == Player::GetPlayer())
	{
		Player* NewPlayer = CreateActor<Player>(OBJECTORDER::Character);
		NewPlayer->SetLevelOverOn();
		float4 StartPoint = float4{ 260.f, -757.f, OBJECTORDER::Character, 1.f };
		mpPlayer = Player::GetPlayer();
		mpPlayer->GetTransform().SetWorldPosition(StartPoint);

		Inventory* inventory = CreateActor<Inventory>(OBJECTORDER::UIGauge);
		inventory->SetLevelOverOn();
		inventory->GetTransform().SetLocalPosition(float4{ 0.f, -10.f, OBJECTORDER::UIGauge, 1.f });
		
		QuickSlot* quickSlot = CreateActor<QuickSlot>(OBJECTORDER::UIGauge);
		quickSlot->SetLevelOverOn();
		quickSlot->GetTransform().SetLocalPosition(float4{ 565.f, -255.f, OBJECTORDER::UIGauge, 1.f });
	}

	// if (nullptr == )

	mpPlayer = Player::GetPlayer();
	mpPlayer->SetParentLevel(this);
	Veil::SetVeilEffect(VEIL_EFFECT::FADE_IN);
}

void TempleOfTime0::Update(float _DeltaTime)
{
	// 1 2 0.2 -> 0.8 + 0.4 -> 1.2
    // 1 2 0.3 -> 0.7 + 0.6 -> 1.3

	if (true == ContentsCore::IsCameraFollowingOn())
	{
		float4 f4CurrentPosition = mpCamera->GetTransform().GetWorldPosition();
		float4 f4DestinationPosition = mpPlayer->GetTransform().GetWorldPosition();
		float4 f4MoveToPosition = float4::Lerp(f4CurrentPosition, f4DestinationPosition, _DeltaTime * 10.f);

		mpCamera->GetTransform().SetWorldPosition(f4MoveToPosition);
	}
	/*
	else
	{
		if (true == GameEngineInput::GetInst()->IsPress("CamLeft"))
		{
			GetMainCameraActorTransform().SetWorldMove(-GetMainCameraActorTransform().GetRightVector() * 100 * _DeltaTime);
		}
		if (true == GameEngineInput::GetInst()->IsPress("CamRight"))
		{
			GetMainCameraActorTransform().SetWorldMove(GetMainCameraActorTransform().GetRightVector() * 100 * _DeltaTime);
		}
		if (true == GameEngineInput::GetInst()->IsPress("CamUp"))
		{
			GetMainCameraActorTransform().SetWorldMove(GetMainCameraActorTransform().GetUpVector() * 100 * _DeltaTime);
		}
		if (true == GameEngineInput::GetInst()->IsPress("CamDown"))
		{
			GetMainCameraActorTransform().SetWorldMove(-GetMainCameraActorTransform().GetUpVector() * 100 * _DeltaTime);
		}
	}
	*/

	if (true == mbLimitCameraMoving)
	{
		LimitCameraMoving(GetMapSize());
	}

	float4 pos = mpCamera->GetTransform().GetWorldPosition();
	pos.z = OBJECTORDER::Alpha;
	mpVeil->GetTransform().SetWorldPosition(pos);

	if (PortalCollisionType::NEXT == IsPortalCollided())
	{
		if (true == GameEngineInput::GetInst()->IsPress("PlayerUp"))
		{
			mfVeilStartSecond = GetAccTime();
			Veil::SetVeilEffect(VEIL_EFFECT::FADE_OUT);		
			// Veil::SetVeilEffect(VEIL_EFFECT::FADE_IN);		
		}
	}

	if (-1.f != mfVeilStartSecond && 1.0f <= GetAccTime() - mfVeilStartSecond)
	{
		mfVeilStartSecond = -1.f;

		float4 StartPoint = float4{ 173.f, -605.f, OBJECTORDER::Character, 0.f };
		mpPlayer->GetTransform().SetWorldPosition(StartPoint);
		GEngine::ChangeLevel("TempleOfTime1");
	}

#pragma region CheckKeysForDebugging
	if (true == GameEngineInput::GetInst()->IsDown("PCMapOnOffToggle"))
	{
		mpPCMap->GetRenderer()->OnOffSwitch();
	}
	if (true == GameEngineInput::GetInst()->IsDown("PrintDescription"))
	{
		PrintDescription();
	}
	if (true == GameEngineInput::GetInst()->IsDown("PrintPixelColor"))
	{
		PrintPixelColor();
	}
	if (true == GameEngineInput::GetInst()->IsDown("PrintPlayerWorldPosition"))
	{
		PrintPlayerWorldPosition();
	}
	if (true == GameEngineInput::GetInst()->IsDown("FreeCameraOnOff"))
	{
		FreeCameraOnOff();
	}
	if (true == GameEngineInput::GetInst()->IsDown("LimitCameraMovingOnOff"))
	{
		LimitCameraMovingOnOff();
	}
#pragma endregion

	
	
	/*
	GameEngineDebug::OutPutString(
		std::to_string(mpPlayer->GetRenderer()->GetTransform().GetWorldPosition().x) + "  " +
		std::to_string(mpPlayer->GetRenderer()->GetTransform().GetWorldPosition().y) + "  " +
		std::to_string(mpPlayer->GetRenderer()->GetTransform().GetWorldPosition().z) + "  " +
		std::to_string(mpPortalToNext->GetRenderer()->GetTransform().GetWorldPosition().x) + "  " +
		std::to_string(mpPortalToNext->GetRenderer()->GetTransform().GetWorldPosition().y) + "  " +
		std::to_string(mpPortalToNext->GetRenderer()->GetTransform().GetWorldPosition().z));
	*/
	/*
	GameEngineDebug::OutPutString(
		std::to_string(GetMainCameraActor()->GetTransform().GetWorldPosition().x) + ", " +
		std::to_string(GetMainCameraActor()->GetTransform().GetWorldPosition().y) + ", " +
		std::to_string(GetMainCameraActor()->GetTransform().GetWorldPosition().z)
	);
	*/
}

void TempleOfTime0::End()
{
	Veil::SetVeilEffect(VEIL_EFFECT::FADE_OUT);
}
