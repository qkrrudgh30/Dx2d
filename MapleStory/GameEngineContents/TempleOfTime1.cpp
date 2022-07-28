#include "PreCompile.h"
#include "TempleOfTime1.h"
#include "GlobalContentsValue.h"
#include "Player.h"
#include "Temple1BackGround.h"
#include "Temple1Tile.h"
#include "Temple1Cloud.h"
#include "PixelCollisionMap.h"
#include "Portal.h"
#include "Veil.h"
#include "StateBar.h"

#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineWindow.h>

TempleOfTime1::TempleOfTime1() 
{
}

TempleOfTime1::~TempleOfTime1() 
{
}

void TempleOfTime1::OnEvent()
{
	Veil::SetVeilEffect(VEIL_EFFECT::FADE_IN);
}

void TempleOfTime1::Start()
{
	mpCamera = GetMainCameraActor();
	mpCamera->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
	mpCamera->GetTransform().SetWorldPosition({ 0.0f, 0.0f, -500.0f });
	// GetMainCameraActor()->FreeCameraModeOnOff();

	SetMapSize(float4{ 4371.f, 780.f });
	mpBackGround = CreateActor<Temple1BackGround>(OBJECTORDER::UI);
	mpTile = CreateActor<Temple1Tile>(OBJECTORDER::UI);
	mpCloud = CreateActor<Temple1Cloud>(OBJECTORDER::UI);
	mpPCMap = CreateActor<PixelCollisionMap>(OBJECTORDER::UI);
	mpPCMap->SetInfo("Temple1TileP.png");
	mpPCMap->GetRenderer()->OnOffSwitch();

	float4 CenterPointOfMap = float4{ GetMapSize().x / 2.f, -(GetMapSize().y / 2.f), OBJECTORDER::UI, 0.f };
	mpBackGround->GetTransform().SetWorldPosition(CenterPointOfMap);
	mpTile->GetTransform().SetWorldPosition(CenterPointOfMap);
	mpCloud->GetTransform().SetWorldPosition(CenterPointOfMap);
	mpPCMap->GetTransform().SetWorldPosition(CenterPointOfMap);

	

	mpPortalToPrevious = CreateActor<Portal>(OBJECTORDER::UI);
	mpPortalToPrevious->GetTransform().SetWorldPosition(float4{ 165.f, -605.f, OBJECTORDER::Character, 1.f });
	mpPortalToNext = CreateActor<Portal>(OBJECTORDER::UI);	
	mpPortalToNext->GetTransform().SetWorldPosition(float4{ 2160.f, -605.f, OBJECTORDER::Character, 1.f });

	mpStateBar = CreateActor<StateBar>(OBJECTORDER::UI);

	mpVeil = CreateActor<Veil>(OBJECTORDER::UI);
}

void TempleOfTime1::Update(float _DeltaTime)
{
	if (true == ContentsCore::IsCameraFollowingOn())
	{
		mpCamera->GetTransform().SetWorldPosition(mpPlayer->GetTransform().GetLocalPosition());
	}

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
	if (PortalCollisionType::PREVIOUS == IsPortalCollided())
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
		if (PortalCollisionType::PREVIOUS == IsPortalCollided())
		{
			GEngine::ChangeLevel("TempleOfTime0");
		}
		if (PortalCollisionType::NEXT == IsPortalCollided())
		{
			mpPlayer = Player::GetPlayer();
			float4 StartPoint = float4{ 165.f, -660.f, OBJECTORDER::Character, 1.f };
			mpPlayer->GetTransform().SetWorldPosition(StartPoint);
			GEngine::ChangeLevel("TempleOfTime2");
		}
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
#pragma endregion


	// GameEngineDebug::OutPutString(std::to_string(mpPlayer->GetTransform().GetLocalPosition().x) + "  " + std::to_string(mpPlayer->GetTransform().GetLocalPosition().y));
}

void TempleOfTime1::End()
{
}
