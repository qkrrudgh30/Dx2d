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
	mpCamera->GetTransform().SetWorldPosition({ 0.0f, 0.0f, -500.0f });

	Temple1BackGround* NewBackGround = CreateActor<Temple1BackGround>(OBJECTORDER::BackGround);
	Temple1Tile* NewTile = CreateActor<Temple1Tile>(OBJECTORDER::Tile);
	Temple1Cloud* NewCloud = CreateActor<Temple1Cloud>(OBJECTORDER::Cloud);
	SetMapSize(float4{ 4371.f, 780.f });

	float4 MapHalfSize = float4{ GetMapSize().x / 2.f, -(GetMapSize().y / 2.f) };
	NewBackGround->GetTransform().SetWorldMove(MapHalfSize);
	NewTile->GetTransform().SetWorldMove(MapHalfSize);
	NewCloud->GetTransform().SetWorldMove(MapHalfSize);

	mpPlayer = CreateActor<Player>(OBJECTORDER::Character);
	mpPlayer->GetTransform().SetWorldMove(MapHalfSize);

	mpPortalToPrevious = CreateActor<Portal>(OBJECTORDER::UI);
	mpPortalToPrevious->GetTransform().SetWorldMove(float4{ 165.f, -489.f, 1.f, 1.f });
	mpPortalToNext = CreateActor<Portal>(OBJECTORDER::UI);	
	mpPortalToNext->GetTransform().SetWorldMove(float4{ 2160.f, -480.f, 1.f, 1.f });

	mpVeil = CreateActor<Veil>(OBJECTORDER::UI);
}

void TempleOfTime1::Update(float _DeltaTime)
{
	mpPortalToPrevious->GetTransform().SetWorldPosition(float4{ 165.f, -489.f, OBJECTORDER::Character, 1.f });
	mpPortalToNext->GetTransform().SetWorldPosition(float4{ 2160.f, -480.f, OBJECTORDER::Character, 1.f });
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
			GEngine::ChangeLevel("TempleOfTime2");
		}
	}	


	// GameEngineDebug::OutPutString(std::to_string(mpPlayer->GetTransform().GetLocalPosition().x) + "  " + std::to_string(mpPlayer->GetTransform().GetLocalPosition().y));
}

void TempleOfTime1::End()
{
}
