#include "PreCompile.h"
#include "TempleOfTime3.h"
#include "GlobalContentsValue.h"
#include "Player.h"
#include "Temple3BackGround.h"
#include "Temple3Tile.h"
#include "Temple3Cloud.h"
#include "PixelCollisionMap.h"
#include "Portal.h"
#include "Veil.h"
#include "Temple3Monster.h"
#include "Temple3Boss.h"
#include "StateBar.h"

#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineWindow.h>

TempleOfTime3::TempleOfTime3()
    : mpBackGround(nullptr)
    , mpTile(nullptr)
    , mpCloud(nullptr)
{
}

TempleOfTime3::~TempleOfTime3() 
{
}

void TempleOfTime3::LevelStartEvent()
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

void TempleOfTime3::Start()
{
    mpCamera = GetMainCameraActor();
    mpCamera->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
    mpCamera->GetTransform().SetWorldPosition({ 0.0f, 0.0f, -500.0f });
    // GetMainCameraActor()->FreeCameraModeOnOff();

    SetMapSize(float4{ 1988.f, 1248.f });
    mpBackGround = CreateActor<Temple3BackGround>(OBJECTORDER::UI);
    mpTile = CreateActor<Temple3Tile>(OBJECTORDER::UI);
    mpCloud = CreateActor<Temple3Cloud>(OBJECTORDER::UI);
    mpPCMap = CreateActor<PixelCollisionMap>(OBJECTORDER::UI);
    mpPCMap->SetInfo("Temple3TileP.png");
    mpPCMap->GetRenderer()->OnOffSwitch();

    float4 CenterPointOfMap = float4{ GetMapSize().x / 2.f, -(GetMapSize().y / 2.f), OBJECTORDER::UI, 0.f };
    mpBackGround->GetTransform().SetWorldPosition(CenterPointOfMap);
    mpTile->GetTransform().SetWorldPosition(CenterPointOfMap);
    mpCloud->GetTransform().SetWorldPosition(CenterPointOfMap + float4{ 0.f, 30.f, 0.f, 0.f });
    mpPCMap->GetTransform().SetWorldPosition(CenterPointOfMap);

    mpPortalToPrevious = CreateActor<Portal>(OBJECTORDER::UI);
    mpPortalToPrevious->GetTransform().SetWorldPosition(float4{ 969.f, -1067.f, OBJECTORDER::Character, 1.f });

    float4 StartPoint = float4{ 1212.f, -1064.f, OBJECTORDER::Character, 1.f };
    Temple3Monster* mpMonster1 = CreateActor<Temple3Monster>(OBJECTORDER::Mob);
    mpMonster1->GetTransform().SetWorldPosition(StartPoint);

    StartPoint = float4{ 706.f, -1064.f, OBJECTORDER::Character, 1.f };
    Temple3Monster* mpMonster2 = CreateActor<Temple3Monster>(OBJECTORDER::Mob);
    mpMonster2->GetTransform().SetWorldPosition(StartPoint);

    StartPoint = float4{ 1212.f, -1064.f, OBJECTORDER::Character, 1.f };
    Temple3Monster* mpMonster3 = CreateActor<Temple3Monster>(OBJECTORDER::Mob);
    mpMonster3->GetTransform().SetWorldPosition(StartPoint);

    StartPoint = float4{ 1632.f, -1064.f, OBJECTORDER::Character, 1.f };
    Temple3Monster* mpMonster4 = CreateActor<Temple3Monster>(OBJECTORDER::Mob);
    mpMonster4->GetTransform().SetWorldPosition(StartPoint);

    StartPoint = float4{ 1100.f, -709.f, OBJECTORDER::Character, 1.f };
    Temple3Monster* mpMonster5 = CreateActor<Temple3Monster>(OBJECTORDER::Mob);
    mpMonster5->GetTransform().SetWorldPosition(StartPoint);

    StartPoint = float4{ 1664.f, -709.f, OBJECTORDER::Character, 1.f };
    Temple3Monster* mpMonster6 = CreateActor<Temple3Monster>(OBJECTORDER::Mob);
    mpMonster6->GetTransform().SetWorldPosition(StartPoint);

    StartPoint = float4{ 291.f, -709.f, OBJECTORDER::Character, 1.f };
    Temple3Monster* mpMonster7 = CreateActor<Temple3Monster>(OBJECTORDER::Mob);
    mpMonster7->GetTransform().SetWorldPosition(StartPoint);

    StartPoint = float4{ 1069.f, -366.f, OBJECTORDER::Character, 1.f };
    Temple3Boss* mpBoss = CreateActor<Temple3Boss>(OBJECTORDER::Mob);
    mpBoss->GetTransform().SetWorldPosition(StartPoint);

    mpStateBar = CreateActor<StateBar>(OBJECTORDER::UI);

    mpVeil = CreateActor<Veil>(OBJECTORDER::UI);
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

    if (true == mbLimitCameraMoving)
    {
        LimitCameraMoving(GetMapSize());
    }
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

        mpPlayer = Player::GetPlayer();
        float4 StartPoint = float4{ 1841.f, -660.f, OBJECTORDER::Character, 1.f };
        mpPlayer->GetTransform().SetWorldPosition(StartPoint);
        GEngine::ChangeLevel("TempleOfTime2");
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

void TempleOfTime3::End()
{
}
