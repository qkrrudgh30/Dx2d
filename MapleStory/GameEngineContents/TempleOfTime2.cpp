#include "PreCompile.h"
#include "TempleOfTime2.h"
#include "GlobalContentsValue.h"
#include "Player.h"
#include "Temple2BackGround.h"
#include "Temple2Tile.h"
#include "Temple2Cloud.h"
#include "PixelCollisionMap.h"
#include "Portal.h"
#include "Veil.h"
#include "Temple2Monster.h"
#include "StateBar.h"

#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineWindow.h>

TempleOfTime2::TempleOfTime2() 
{
}

TempleOfTime2::~TempleOfTime2() 
{
}

void TempleOfTime2::OnEvent()
{
	if (nullptr == Player::GetPlayer())
	{
		Player* NewPlayer = CreateActor<Player>(OBJECTORDER::Character);
		NewPlayer->SetLevelOverOn();
	}
	mpPlayer = Player::GetPlayer();
	mpPlayer->SetParentLevel(dynamic_cast<ContentsLevel*>(this));
	Veil::SetVeilEffect(VEIL_EFFECT::FADE_IN);
}

void TempleOfTime2::Start()
{
	mpCamera = GetMainCameraActor();
	mpCamera->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
	mpCamera->GetTransform().SetWorldPosition({ 0.0f, 0.0f, -500.0f });
	// GetMainCameraActor()->FreeCameraModeOnOff();

	SetMapSize(float4{ 1982.f, 846.f });
	mpBackGround = CreateActor<Temple2BackGround>(OBJECTORDER::UI);
	mpTile = CreateActor<Temple2Tile>(OBJECTORDER::UI);
	mpCloud = CreateActor<Temple2Cloud>(OBJECTORDER::UI);
	mpPCMap = CreateActor<PixelCollisionMap>(OBJECTORDER::UI);
	mpPCMap->SetInfo("Temple2TileP.png");
	mpPCMap->GetRenderer()->OnOffSwitch();

	float4 CenterPointOfMap = float4{ GetMapSize().x / 2.f, -(GetMapSize().y / 2.f), OBJECTORDER::UI, 1.f };
	mpBackGround->GetTransform().SetLocalPosition(CenterPointOfMap);
	mpTile->GetTransform().SetLocalPosition(CenterPointOfMap);
	mpCloud->GetTransform().SetLocalPosition(CenterPointOfMap);
	mpPCMap->GetTransform().SetLocalPosition(CenterPointOfMap);

    float4 StartPoint = float4{ 396.f, -318.f, OBJECTORDER::Character, 1.f };
	Temple2Monster* mpMonster2 = CreateActor<Temple2Monster>(OBJECTORDER::Mob);
	mpMonster2->GetTransform().SetWorldPosition(StartPoint);

	StartPoint = float4{ 1130.f, -318.f, OBJECTORDER::Character, 1.f };
	Temple2Monster* mpMonster3 = CreateActor<Temple2Monster>(OBJECTORDER::Mob);
	mpMonster3->GetTransform().SetWorldPosition(StartPoint);

	StartPoint = float4{ 1660.f, -318.f, OBJECTORDER::Character, 1.f };
	Temple2Monster* mpMonster4 = CreateActor<Temple2Monster>(OBJECTORDER::Mob);
	mpMonster4->GetTransform().SetWorldPosition(StartPoint);

	StartPoint = float4{ 512.f, -664.f, OBJECTORDER::Character, 1.f };
	Temple2Monster* mpMonster5 = CreateActor<Temple2Monster>(OBJECTORDER::Mob);
	mpMonster5->GetTransform().SetWorldPosition(StartPoint);

	StartPoint = float4{ 1010.f, -664.f, OBJECTORDER::Character, 1.f };
	Temple2Monster* mpMonster6 = CreateActor<Temple2Monster>(OBJECTORDER::Mob);
	mpMonster6->GetTransform().SetWorldPosition(StartPoint);

	StartPoint = float4{ 1330.f, -664.f, OBJECTORDER::Character, 1.f };
	Temple2Monster* mpMonster7 = CreateActor<Temple2Monster>(OBJECTORDER::Mob);
	mpMonster7->GetTransform().SetWorldPosition(StartPoint);

	StartPoint = float4{ 1640.f, -664.f, OBJECTORDER::Character, 1.f };
	Temple2Monster* mpMonster8 = CreateActor<Temple2Monster>(OBJECTORDER::Mob);
	mpMonster8->GetTransform().SetWorldPosition(StartPoint);

	mpPortalToPrevious = CreateActor<Portal>(OBJECTORDER::UI);
	mpPortalToPrevious->GetTransform().SetWorldPosition(float4{ 165.f, -660.f, OBJECTORDER::Character, 1.f });
	mpPortalToNext = CreateActor<Portal>(OBJECTORDER::UI);
	mpPortalToNext->GetTransform().SetWorldPosition(float4{ 1860.f, -660.f, OBJECTORDER::Character, 1.f });

	mpStateBar = CreateActor<StateBar>(OBJECTORDER::UI);

	mpVeil = CreateActor<Veil>(OBJECTORDER::UI);
}

void TempleOfTime2::Update(float _DeltaTime)
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

	if (-1.f != mfVeilStartSecond && 1.0f <= GetAccTime() - mfVeilStartSecond)
	{
		mfVeilStartSecond = -1.f;
		if (PortalCollisionType::PREVIOUS == IsPortalCollided())
		{
			mpPlayer = Player::GetPlayer();
			float4 StartPoint = float4{ 2200.f, -598.f, OBJECTORDER::Character, 1.f };
			mpPlayer->GetTransform().SetWorldPosition(StartPoint);
			GEngine::ChangeLevel("TempleOfTime1");
		}
		if (PortalCollisionType::NEXT == IsPortalCollided())
		{
			mpPlayer = Player::GetPlayer();
			float4 StartPoint = float4{ 990.f, -1060.f, OBJECTORDER::Character, 1.f };
			mpPlayer->GetTransform().SetWorldPosition(StartPoint);
			GEngine::ChangeLevel("TempleOfTime3");
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


	// GameEngineDebug::OutPutString(std::to_string(mpPlayer->GetTransform().GetLocalPosition().x) + "  " + std::to_string(mpPlayer->GetTransform().GetLocalPosition().y));
}

void TempleOfTime2::End()
{
}
