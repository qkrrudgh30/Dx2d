#include "PreCompile.h"
#include "TempleOfTime2.h"
#include "GlobalContentsValue.h"
#include "Player.h"
#include "Monster.h"
#include "Temple2BackGround.h"
#include "Temple2Tile.h"
#include "Temple2Cloud.h"
#include "Portal.h"
#include "Veil.h"

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
	Veil::SetVeilEffect(VEIL_EFFECT::FADE_IN);
}

void TempleOfTime2::Start()
{
	mpCamera = CreateActor<GameEngineCameraActor>();
	mpCamera->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
	mpCamera->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -500.0f });

	Temple2BackGround* NewBackGround = CreateActor<Temple2BackGround>(OBJECTORDER::BackGround);
	Temple2Tile* NewTile = CreateActor<Temple2Tile>(OBJECTORDER::Tile);
	Temple2Cloud* NewCloud = CreateActor<Temple2Cloud>(OBJECTORDER::Cloud);
	SetMapSize(float4{ 1982.f, 846.f });

	float4 MapHalfSize = float4{ GetMapSize().x / 2.f, -(GetMapSize().y / 2.f) };
	NewBackGround->GetTransform().SetLocalMove(MapHalfSize);
	NewTile->GetTransform().SetLocalMove(MapHalfSize);
	NewCloud->GetTransform().SetLocalMove(MapHalfSize);

	mpPlayer = CreateActor<Player>(OBJECTORDER::Player);
	mpPlayer->GetTransform().SetLocalMove(MapHalfSize);

	mpPortalToPrevious = CreateActor<Portal>(OBJECTORDER::UI);
	mpPortalToPrevious->GetRenderer()->GetTransform().SetLocalPosition(float4{ 165.f, -533.f });
	mpPortalToNext = CreateActor<Portal>(OBJECTORDER::UI);
	mpPortalToNext->GetRenderer()->GetTransform().SetLocalPosition(float4{ 1860.f, -533.f });

	mpVeil = CreateActor<Veil>(OBJECTORDER::UI);
}

void TempleOfTime2::Update(float _DeltaTime)
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
			GEngine::ChangeLevel("TempleOfTime1");
		}
		if (PortalCollisionType::NEXT == IsPortalCollided())
		{
			mfVeilStartSecond = -1.f;
			GEngine::ChangeLevel("TempleOfTime3");
		}
	}

	LimitCameraMoving(GetMapSize());
	mpVeil->GetTransform().SetLocalPosition(mpCamera->GetTransform().GetLocalPosition());

	// GameEngineDebug::OutPutString(std::to_string(mpPlayer->GetTransform().GetLocalPosition().x) + "  " + std::to_string(mpPlayer->GetTransform().GetLocalPosition().y));
}

void TempleOfTime2::End()
{
}
