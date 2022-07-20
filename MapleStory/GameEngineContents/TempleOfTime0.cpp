#include "PreCompile.h"
#include "TempleOfTime0.h"
#include "GlobalContentsValue.h"
#include "Player.h"
#include "Monster.h"
#include "Temple0BackGround.h"
#include "Temple0Tile.h"
#include "Temple0Cloud.h"
#include "Portal.h"
#include "Veil.h"

#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTransform.h>
#include <GameEngineBase/GameEngineDebug.h>

#include <string>

TempleOfTime0::TempleOfTime0()
{
}

TempleOfTime0::~TempleOfTime0()
{
}

void TempleOfTime0::OnEvent()
{
	Veil::SetVeilEffect(VEIL_EFFECT::FADE_IN);
}

void TempleOfTime0::Start()
{
	mpCamera = CreateActor<GameEngineCameraActor>();
	mpCamera->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
	mpCamera->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -500.0f });
	
	Temple0BackGround* NewBackGround = CreateActor<Temple0BackGround>(OBJECTORDER::BackGround);
	Temple0Tile* NewTile = CreateActor<Temple0Tile>(OBJECTORDER::Tile);
	Temple0Cloud* NewCloud = CreateActor<Temple0Cloud>(OBJECTORDER::Cloud);
	SetMapSize(float4{2327.f, 955.f});
	
	float4 MapHalfSize = float4{ GetMapSize().x / 2.f, -(GetMapSize().y / 2.f)};
	NewBackGround->GetTransform().SetLocalMove(MapHalfSize);
	NewTile->GetTransform().SetLocalMove(MapHalfSize);
	NewCloud->GetTransform().SetLocalMove(MapHalfSize);

	mpPlayer = CreateActor<Player>(OBJECTORDER::Player);
	mpPlayer->GetTransform().SetLocalMove(MapHalfSize);

	mpPortalToNext = CreateActor<Portal>(OBJECTORDER::UI);
	// mpPortalToNext->GetTransform().SetLocalPosition(float4{ 2000.f, -217.f});
	mpPortalToNext->GetRenderer()->GetTransform().SetLocalPosition(float4{ 2000.f, -132.f});

	mpVeil = CreateActor<Veil>(OBJECTORDER::UI);
}

void TempleOfTime0::Update(float _DeltaTime)
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

	if (-1.f != mfVeilStartSecond && 2.f <= GetAccTime() - mfVeilStartSecond)
	{
		mfVeilStartSecond = -1.f;
		GEngine::ChangeLevel("TempleOfTime1");
	}

	LimitCameraMoving(GetMapSize());
	mpVeil->GetTransform().SetLocalPosition(mpCamera->GetTransform().GetLocalPosition());

	// GameEngineDebug::OutPutString(std::to_string(mpPlayer->GetTransform().GetLocalPosition().x) + "  " + std::to_string(mpPlayer->GetTransform().GetLocalPosition().y));
	GameEngineDebug::OutPutString(std::to_string(ContentsCore::GetMousePos().x) + "  " + std::to_string(ContentsCore::GetMousePos().y));
}

void TempleOfTime0::End()
{
	Veil::SetVeilEffect(VEIL_EFFECT::FADE_IN);
}
