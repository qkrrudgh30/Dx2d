#include "PreCompile.h"
#include "ContentsLevel.h"

#include "GlobalContentsValue.h"
#include "Player.h"
#include "Portal.h"
#include "Veil.h"

#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTransform.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

ContentsLevel::ContentsLevel()
    : mpCamera(nullptr)
    , mpPlayer(nullptr)
    , mpPortalToNext(nullptr)
    , mpPortalToPrevious(nullptr)
    , mpVeil(nullptr)
    , mfVeilStartSecond(-1.f)
    , mbStart(false)
    , mf4CameraPosition{}
    , mf4MapSize{}
    , mf4WindowSize{}
{
    mf4WindowSize = GameEngineWindow::GetScale();
}

ContentsLevel::~ContentsLevel()
{
}

void ContentsLevel::LimitCameraMoving(float4 _f4MapSize)
{
    if (nullptr == mpCamera) { return; }

    mf4CameraPosition = mpCamera->GetTransform().GetLocalPosition();
    float4 f4NextCameraPosition = mpCamera->GetTransform().GetLocalPosition();
    if (mf4CameraPosition.x <= (mf4WindowSize.x / 2.f) + 10.f)
    {
        f4NextCameraPosition.x = (mf4WindowSize.x / 2.f) + 10.f;
        mpCamera->GetTransform().SetWorldPosition(f4NextCameraPosition);
    }
    if (_f4MapSize.x - (mf4WindowSize.x / 2.f) - 10.f <= mf4CameraPosition.x)
    {
        f4NextCameraPosition.x = _f4MapSize.x - (1280.f / 2.f) - 10.f;
        mpCamera->GetTransform().SetWorldPosition(f4NextCameraPosition);
    }
    
    if (-(mf4WindowSize.y / 2.f) - 10.f <= mf4CameraPosition.y)
    {
        f4NextCameraPosition.y = -(mf4WindowSize.y / 2.f) - 10.f;
        mpCamera->GetTransform().SetWorldPosition(f4NextCameraPosition);
    }
    if (mf4CameraPosition.y <= -(_f4MapSize.y) + (mf4WindowSize.y / 2.f) + 10.f)
    {
        f4NextCameraPosition.y = -(_f4MapSize.y) + (mf4WindowSize.y / 2.f) + 10.f;
        mpCamera->GetTransform().SetWorldPosition(f4NextCameraPosition);
    }
}

PortalCollisionType ContentsLevel::IsPortalCollided()
{
    if (nullptr != mpPlayer && nullptr != mpPortalToNext)
    {
        if (true == GameEngineTransform::OBBToOBB(mpPlayer->GetRenderer()->GetTransform(), mpPortalToNext->GetRenderer()->GetTransform()))
        {
            return PortalCollisionType::NEXT;
        }
    }

    if (nullptr != mpPlayer && nullptr != mpPortalToPrevious)
    {
        if (true == GameEngineTransform::OBBToOBB(mpPlayer->GetRenderer()->GetTransform(), mpPortalToPrevious->GetRenderer()->GetTransform()))
        {
            return PortalCollisionType::PREVIOUS;
        }
    }

    return PortalCollisionType::NOTREADY;
}

void ContentsLevel::ChangeLevelWithSecond(std::string _Name, float _Second)
{
    if (_Second <= GetAccTime())
    {
    }
}