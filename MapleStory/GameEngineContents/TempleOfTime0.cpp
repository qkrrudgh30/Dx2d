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

#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTransform.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineCameraActor.h>

#include <string>


TempleOfTime0::TempleOfTime0()
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
	
	float4 CenterPointOfMap = float4{ GetMapSize().x / 2.f, -(GetMapSize().y / 2.f), 3.f, 0.f };
	mpBackGround->GetTransform().SetWorldMove(CenterPointOfMap);
	mpTile->GetTransform().SetWorldMove(CenterPointOfMap);
	mpCloud->GetTransform().SetWorldMove(CenterPointOfMap);
	mpPCMap->GetTransform().SetWorldMove(CenterPointOfMap);

	mpPlayer = CreateActor<Player>(OBJECTORDER::Character);
	float4 StartPoint = float4{260.f, -760.f, 0.f, 0.f};
	mpPlayer->GetTransform().SetWorldMove(StartPoint);

	mpPortalToNext = CreateActor<Portal>(OBJECTORDER::Character);

	mpStateBar = CreateActor<StateBar>(OBJECTORDER::UIBackGround);
	
	mpVeil = CreateActor<Veil>(OBJECTORDER::UI);
}

void TempleOfTime0::OnEvent()
{
	Veil::SetVeilEffect(VEIL_EFFECT::FADE_IN);
}

void TempleOfTime0::Update(float _DeltaTime)
{
	mpPortalToNext->GetRenderer()->GetTransform().SetWorldPosition(float4{ 2000.f, -132.f, OBJECTORDER::Character, 1.f });
	if (true == ContentsCore::IsCameraFollowingOn())
	{
		mpCamera->GetTransform().SetWorldPosition(mpPlayer->GetTransform().GetWorldPosition());
	}
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

	LimitCameraMoving(GetMapSize());

	float4 pos = mpCamera->GetTransform().GetWorldPosition();
	pos.z = OBJECTORDER::Alpha;
	mpVeil->GetTransform().SetWorldPosition(pos);

	if (PortalCollisionType::NEXT == IsPortalCollided())
	{
		if (true == GameEngineInput::GetInst()->IsPress("PlayerUp"))
		{
			mfVeilStartSecond = GetAccTime();
			Veil::SetVeilEffect(VEIL_EFFECT::FADE_OUT);		
		}
	}

	if (-1.f != mfVeilStartSecond && 1.f <= GetAccTime() - mfVeilStartSecond)
	{
		mfVeilStartSecond = -1.f;
		GEngine::ChangeLevel("TempleOfTime1");
	}

	if (true == GameEngineInput::GetInst()->IsDown("PCMapOnOffToggle"))
	{
		mpPCMap->GetRenderer()->OnOffSwitch();
	}

	GameEngineDebug::OutPutString(std::to_string(pos.x) + ", " + std::to_string(pos.y));

	/*
	GameEngineDebug::OutPutString(
		std::to_string(mpPlayer->GetRenderer()->GetTransform().GetWorldPosition().x) + "  " +
		std::to_string(mpPlayer->GetRenderer()->GetTransform().GetWorldPosition().y) + "  " +
		std::to_string(mpPortalToNext->GetRenderer()->GetTransform().GetWorldPosition().x) + "  " +
		std::to_string(mpPortalToNext->GetRenderer()->GetTransform().GetWorldPosition().y));

    */
}

void TempleOfTime0::End()
{
	Veil::SetVeilEffect(VEIL_EFFECT::FADE_OUT);
}
