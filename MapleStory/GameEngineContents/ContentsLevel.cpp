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
    , mbStart(false)
    , mf4CameraPosition{}
    , mf4MapSize{}
    , mf4WindowSize{}
{
}

ContentsLevel::~ContentsLevel()
{
}

void ContentsLevel::LimitCameraMoving()
{
    if (nullptr == mpCamera) { return; }

    float4 f4NextCameraPosition;
    mf4WindowSize = GameEngineWindow::GetScale();
    mf4CameraPosition = mpCamera->GetTransform().GetLocalPosition();
    f4NextCameraPosition = mpCamera->GetTransform().GetLocalPosition();
    if (mf4CameraPosition.x <= -(mf4MapSize.x / 2.f) + (mf4WindowSize.x / 2.f) + 10.f)
    {
        f4NextCameraPosition.x = -(mf4MapSize.x / 2.f) + (mf4WindowSize.x / 2.f) + 10.f;
        mpCamera->GetTransform().SetLocalPosition(f4NextCameraPosition);
    }
    if ((mf4MapSize.x / 2.f) - (mf4WindowSize.x / 2.f) - 10.f <= mf4CameraPosition.x)
    {
        f4NextCameraPosition.x = (mf4MapSize.x / 2.f) - (mf4WindowSize.x / 2.f) - 10.f;
        mpCamera->GetTransform().SetLocalPosition(f4NextCameraPosition);
    }
    if (mf4CameraPosition.y <= -(mf4MapSize.y / 2.f) + (mf4WindowSize.y / 2.f) + 10.f)
    {
        f4NextCameraPosition.y = -(mf4MapSize.y / 2.f) + (mf4WindowSize.y / 2.f) + 10.f;
        mpCamera->GetTransform().SetLocalPosition(f4NextCameraPosition);
    }
    if ((mf4MapSize.y / 2.f) - (mf4WindowSize.y / 2.f) - 10.f <= mf4CameraPosition.y)
    {
        f4NextCameraPosition.y = (mf4MapSize.y / 2.f) - (mf4WindowSize.y / 2.f) - 10.f;
        mpCamera->GetTransform().SetLocalPosition(f4NextCameraPosition);
    }
}

PortalCollisionType ContentsLevel::IsPortalCollided()
{
    if (nullptr == mpPlayer || nullptr == mpPortalToNext) { return PortalCollisionType::NOTREADY; }
    if (true == GameEngineTransform::OBBToOBB(mpPlayer->GetRenderer()->GetTransform(), mpPortalToNext->GetRenderer()->GetTransform()))
    {
        return PortalCollisionType::NEXT;
    }

    if (nullptr == mpPortalToPrevious) { return PortalCollisionType::NOTREADY; }
    if (true == GameEngineTransform::OBBToOBB(mpPlayer->GetRenderer()->GetTransform(), mpPortalToPrevious->GetRenderer()->GetTransform()))
    {
        return PortalCollisionType::PREVIOUS;
    }
}
