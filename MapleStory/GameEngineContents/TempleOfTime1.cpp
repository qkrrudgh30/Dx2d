#include "PreCompile.h"
#include "TempleOfTime1.h"
#include "GlobalContentsValue.h"
#include "Player.h"
#include "Monster.h"
#include "Temple1BackGround.h"
#include "Temple1Tile.h"
#include "Temple1Cloud.h"
#include "Portal.h"
#include "Veil.h"

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
	mpCamera = CreateActor<GameEngineCameraActor>();
	mpCamera->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
	mpCamera->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -500.0f });

	Temple1BackGround* NewBackGround = CreateActor<Temple1BackGround>(OBJECTORDER::BackGround);
	Temple1Tile* NewTile = CreateActor<Temple1Tile>(OBJECTORDER::Tile);
	Temple1Cloud* NewCloud = CreateActor<Temple1Cloud>(OBJECTORDER::Cloud);
	SetMapSize(float4{ 4371.f, 780.f });

	float4 MapHalfSize = float4{ GetMapSize().x / 2.f, -(GetMapSize().y / 2.f) };
	NewBackGround->GetTransform().SetLocalMove(MapHalfSize);
	NewTile->GetTransform().SetLocalMove(MapHalfSize);
	NewCloud->GetTransform().SetLocalMove(MapHalfSize);

	mpPlayer = CreateActor<Player>(OBJECTORDER::Player);
	mpPlayer->GetTransform().SetLocalMove(MapHalfSize);

	mpPortalToPrevious = CreateActor<Portal>(OBJECTORDER::UI);
	mpPortalToPrevious->GetRenderer()->GetTransform().SetLocalPosition(float4{ 165.f, -489.f });
	mpPortalToNext = CreateActor<Portal>(OBJECTORDER::UI);	
	mpPortalToNext->GetRenderer()->GetTransform().SetLocalPosition(float4{ 2160.f, -480.f });

	mpVeil = CreateActor<Veil>(OBJECTORDER::UI);
}

void TempleOfTime1::Update(float _DeltaTime)
{
	if (true == ContentsCore::IsCameraFollowingOn())
	{
		mpCamera->GetTransform().SetLocalPosition(mpPlayer->GetTransform().GetLocalPosition());
	}

	if (true == GameEngineInput::GetInst()->IsPress("CamLeft"))
	{
		GetMainCameraActorTransform().SetLocalMove(-GetMainCameraActorTransform().GetRightVector() * 100 * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("CamRight"))
	{
		GetMainCameraActorTransform().SetLocalMove(GetMainCameraActorTransform().GetRightVector() * 100 * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("CamUp"))
	{
		GetMainCameraActorTransform().SetLocalMove(GetMainCameraActorTransform().GetUpVector() * 100 * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("CamDown"))
	{
		GetMainCameraActorTransform().SetLocalMove(-GetMainCameraActorTransform().GetUpVector() * 100 * _DeltaTime);
	}

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

	if (-1.f != mfVeilStartSecond && 2.f <= GetAccTime() - mfVeilStartSecond)
	{
		if (PortalCollisionType::PREVIOUS == IsPortalCollided())
		{
			mfVeilStartSecond = -1.f;
			GEngine::ChangeLevel("TempleOfTime0");
		}
		if (PortalCollisionType::NEXT == IsPortalCollided())
		{
			mfVeilStartSecond = -1.f;
			GEngine::ChangeLevel("TempleOfTime2");
		}
	}	

	LimitCameraMoving(GetMapSize());
	mpVeil->GetTransform().SetLocalPosition(mpCamera->GetTransform().GetLocalPosition());

	// GameEngineDebug::OutPutString(std::to_string(mpPlayer->GetTransform().GetLocalPosition().x) + "  " + std::to_string(mpPlayer->GetTransform().GetLocalPosition().y));
}

void TempleOfTime1::End()
{
}
