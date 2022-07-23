#include "PreCompile.h"
#include "TempleOfTime3.h"
#include "GlobalContentsValue.h"
#include "Player.h"
#include "Monster.h"
#include "Temple3BackGround.h"
#include "Temple3Tile.h"
#include "Temple3Cloud.h"
#include "Portal.h"
#include "Veil.h"
#include "Temple3Monster.h"
#include "Temple3Boss.h"

#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineWindow.h>

TempleOfTime3::TempleOfTime3()
{
}

TempleOfTime3::~TempleOfTime3() 
{
}

void TempleOfTime3::OnEvent()
{
    Veil::SetVeilEffect(VEIL_EFFECT::FADE_IN);
}

void TempleOfTime3::Start()
{
    mpCamera = CreateActor<GameEngineCameraActor>();
    mpCamera->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
    mpCamera->GetTransform().SetWorldPosition({ 0.0f, 0.0f, -500.0f });

    Temple3BackGround* NewBackGround = CreateActor<Temple3BackGround>(OBJECTORDER::BackGround);
    Temple3Tile* NewTile = CreateActor<Temple3Tile>(OBJECTORDER::Tile);
    Temple3Cloud* NewCloud = CreateActor<Temple3Cloud>(OBJECTORDER::Cloud);
    SetMapSize(float4{ 1988.f, 1248.f });

    float4 MapHalfSize = float4{ GetMapSize().x / 2.f, -(GetMapSize().y / 2.f) };
    NewBackGround->GetTransform().SetWorldMove(MapHalfSize);
    NewTile->GetTransform().SetWorldMove(MapHalfSize);
    NewCloud->GetTransform().SetWorldMove(MapHalfSize);

    mpPlayer = CreateActor<Player>(OBJECTORDER::Character);
    mpPlayer->GetTransform().SetWorldMove(MapHalfSize);

    mpPortalToPrevious = CreateActor<Portal>(OBJECTORDER::UI);
    mpPortalToPrevious->GetTransform().SetWorldMove(float4{ 969.f, -940.f });
    
    mpVeil = CreateActor<Veil>(OBJECTORDER::UI);

    Temple3Monster* newMob = CreateActor<Temple3Monster>(OBJECTORDER::Mob);
    newMob->GetTransform().SetWorldPosition(MapHalfSize);

    Temple3Boss* newBoss = CreateActor<Temple3Boss>(OBJECTORDER::Mob);
    newBoss->GetTransform().SetWorldPosition(MapHalfSize);
}

void TempleOfTime3::Update(float _DeltaTime)
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
        GEngine::ChangeLevel("TempleOfTime2");
    }

    
    // GameEngineDebug::OutPutString(std::to_string(mpPlayer->GetTransform().GetLocalPosition().x) + "  " + std::to_string(mpPlayer->GetTransform().GetLocalPosition().y));
}

void TempleOfTime3::End()
{
}
