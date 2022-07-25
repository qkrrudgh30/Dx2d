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
#include "Temple2Monster.h"

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
	mpCamera->GetTransform().SetWorldPosition({ 0.0f, 0.0f, -500.0f });

	Temple2BackGround* NewBackGround = CreateActor<Temple2BackGround>(OBJECTORDER::BackGround);
	Temple2Tile* NewTile = CreateActor<Temple2Tile>(OBJECTORDER::Tile);
	Temple2Cloud* NewCloud = CreateActor<Temple2Cloud>(OBJECTORDER::Cloud);
	SetMapSize(float4{ 1982.f, 846.f });
	
	float4 MapHalfSize = float4{ GetMapSize().x / 2.f, -(GetMapSize().y / 2.f), OBJECTORDER::BackGround, 1.f };
	NewBackGround->GetTransform().SetWorldPosition(MapHalfSize);
	MapHalfSize = float4{ GetMapSize().x / 2.f, -(GetMapSize().y / 2.f), OBJECTORDER::Tile, 1.f };
	NewTile->GetTransform().SetWorldPosition(MapHalfSize);
	MapHalfSize = float4{ GetMapSize().x / 2.f, -(GetMapSize().y / 2.f), OBJECTORDER::Cloud, 1.f };
	NewCloud->GetTransform().SetWorldPosition(MapHalfSize);
	
	MapHalfSize = float4{ GetMapSize().x / 2.f, -(GetMapSize().y / 2.f), OBJECTORDER::Mob, 1.f };
	Temple2Monster* mpMonster = CreateActor<Temple2Monster>(OBJECTORDER::Mob);

	mpPlayer = CreateActor<Player>(OBJECTORDER::Character);
	MapHalfSize = float4{ GetMapSize().x / 2.f, -(GetMapSize().y / 2.f), OBJECTORDER::Character, 1.f };
	mpPlayer->GetTransform().SetWorldPosition(MapHalfSize);
	
	mpPortalToPrevious = CreateActor<Portal>(OBJECTORDER::UI);
	
	mpPortalToNext = CreateActor<Portal>(OBJECTORDER::UI);
	

	mpVeil = CreateActor<Veil>(OBJECTORDER::UI);
	MapHalfSize = float4{ GetMapSize().x / 2.f, -(GetMapSize().y / 2.f), OBJECTORDER::Alpha, 1.f };
	mpVeil->GetTransform().SetWorldPosition(MapHalfSize);
}

void TempleOfTime2::Update(float _DeltaTime)
{
	mpPortalToPrevious->GetTransform().SetWorldPosition(float4{ 165.f, -533.f, OBJECTORDER::Character, 1.f });
	mpPortalToNext->GetTransform().SetWorldPosition(float4{ 1860.f, -533.f, OBJECTORDER::Character, 1.f });
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
			GEngine::ChangeLevel("TempleOfTime1");
		}
		if (PortalCollisionType::NEXT == IsPortalCollided())
		{
			GEngine::ChangeLevel("TempleOfTime3");
		}
	}

	// GameEngineDebug::OutPutString(std::to_string(mpPlayer->GetTransform().GetLocalPosition().x) + "  " + std::to_string(mpPlayer->GetTransform().GetLocalPosition().y));
}

void TempleOfTime2::End()
{
}
