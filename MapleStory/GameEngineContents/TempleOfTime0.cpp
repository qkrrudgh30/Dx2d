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
#include "StateBar.h"

#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTransform.h>
#include <GameEngineBase/GameEngineDebug.h>

#include <string>

#include "PopupMenu.h"

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
	mpCamera->GetTransform().SetWorldPosition({ 0.0f, 0.0f, -500.0f });
	
	NewBackGround = CreateActor<Temple0BackGround>(OBJECTORDER::BackGround);
	Temple0Tile* NewTile = CreateActor<Temple0Tile>(OBJECTORDER::Tile);
	Temple0Cloud* NewCloud = CreateActor<Temple0Cloud>(OBJECTORDER::Cloud);
	SetMapSize(float4{2327.f, 955.f});
	
	float4 MapHalfSize = float4{ GetMapSize().x / 2.f, -(GetMapSize().y / 2.f)};
	NewBackGround->GetTransform().SetWorldMove(MapHalfSize);
	NewTile->GetTransform().SetWorldMove(MapHalfSize);
	NewCloud->GetTransform().SetWorldMove(MapHalfSize);

	mpPlayer = CreateActor<Player>(OBJECTORDER::Character);
	mpPlayer->GetTransform().SetWorldMove(MapHalfSize);

	mpPortalToNext = CreateActor<Portal>(OBJECTORDER::Character);
	
	// mpPortalToNext->GetRenderer()->GetTransform().SetLocalPosition(float4{ 2000.f, -132.f, OBJECTORDER::UI, 1.f});

	mpStateBar = CreateActor<StateBar>(OBJECTORDER::UI);

	PopupMenu* new1 = CreateActor<PopupMenu>();
	
	mpVeil = CreateActor<Veil>(OBJECTORDER::UI);
}

void TempleOfTime0::Update(float _DeltaTime)
{
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

	mpPortalToNext->GetTransform().SetWorldPosition(float4{ 2000.f, -132.f, OBJECTORDER::UI, 1.f });

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

	GameEngineDebug::OutPutString(
		std::to_string(mpPlayer->GetRenderer()->GetTransform().GetWorldPosition().x) + "  " +
		std::to_string(mpPlayer->GetRenderer()->GetTransform().GetWorldPosition().y) + "  " +
		std::to_string(mpPortalToNext->GetRenderer()->GetTransform().GetWorldPosition().x) + "  " +
		std::to_string(mpPortalToNext->GetRenderer()->GetTransform().GetWorldPosition().y));
	// GameEngineDebug::OutPutString(std::to_string(GetAccTime()));
}

void TempleOfTime0::End()
{
	Veil::SetVeilEffect(VEIL_EFFECT::FADE_IN);
}
