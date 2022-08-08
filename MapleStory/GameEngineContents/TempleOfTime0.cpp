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
	mpPCMap->GetRenderer()->OnOffSwitch();
	
	float4 CenterPointOfMap = float4{ GetMapSize().x / 2.f, -(GetMapSize().y / 2.f), OBJECTORDER::UI, 0.f };
	mpBackGround->GetTransform().SetWorldPosition(CenterPointOfMap);
	mpTile->GetTransform().SetWorldPosition(CenterPointOfMap);
	mpCloud->GetTransform().SetWorldPosition(CenterPointOfMap);
	mpPCMap->GetTransform().SetWorldPosition(CenterPointOfMap);	

	float4 StartPoint = float4{ 966.f, -777.f, OBJECTORDER::Mob, 1.f };
	Temple2Monster* mpMonster = CreateActor<Temple2Monster>(OBJECTORDER::Mob);
	StartPoint.x += 200.f;
	mpMonster->GetTransform().SetWorldPosition(StartPoint);

	mpPortalToNext = CreateActor<Portal>(OBJECTORDER::Character);
	mpPortalToNext->GetTransform().SetWorldPosition(float4{ 2000.f, -258.f, OBJECTORDER::Character, 1.f });

	mpStateBar = CreateActor<StateBar>(OBJECTORDER::UI);
	
	mpVeil = CreateActor<Veil>(OBJECTORDER::UI);
}

void TempleOfTime0::OnEvent()
{
	if (nullptr == Player::GetPlayer())
	{
		Player* NewPlayer = CreateActor<Player>(OBJECTORDER::Character);
		NewPlayer->SetLevelOverOn();
		float4 StartPoint = float4{ 260.f, -757.f, OBJECTORDER::Character, 1.f };
		mpPlayer = Player::GetPlayer();
		mpPlayer->GetTransform().SetWorldPosition(StartPoint);
	}
	mpPlayer = Player::GetPlayer();
	mpPlayer->SetParentLevel(this);
	Veil::SetVeilEffect(VEIL_EFFECT::FADE_IN);
}

void TempleOfTime0::Update(float _DeltaTime)
{
	
	if (true == ContentsCore::IsCameraFollowingOn())
	{
		mpCamera->GetTransform().SetWorldPosition(mpPlayer->GetTransform().GetWorldPosition());
	}/*
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
	}*/

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
