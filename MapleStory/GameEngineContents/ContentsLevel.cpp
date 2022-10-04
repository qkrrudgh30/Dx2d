#include "PreCompile.h"
#include "ContentsLevel.h"

#include "GlobalContentsValue.h"
#include "Player.h"
#include "Portal.h"
#include "Veil.h"
#include "MenuButton.h"
#include "PopupMenu.h"
#include "QuickSlot.h"

#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTransform.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include "PixelCollisionMap.h"

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
    , mpMenuButton(nullptr)
    , mpPopupMenu(nullptr)
    , mpPCMap(nullptr)
    , mpQuickSlot(nullptr)
    , mbLimitCameraMoving(true)
    , mSoundPlayer()
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

void ContentsLevel::PrintDescription()
{
    GameEngineDebug::OutPutString("F1: 키 설명 출력");
    GameEngineDebug::OutPutString("");
    GameEngineDebug::OutPutString("F2: 카메라의 플레이어 쫒기 On/Off");
    GameEngineDebug::OutPutString("");
    GameEngineDebug::OutPutString("F3: 픽셀 충돌 맵 On/Off");
    GameEngineDebug::OutPutString("");
    GameEngineDebug::OutPutString("F4: 플레이어 발밑 픽셀컬러 출력");
    GameEngineDebug::OutPutString("");
    GameEngineDebug::OutPutString("F5: 플레이어 월드 위치 출력(BOTTOM PIVOT)");
    GameEngineDebug::OutPutString("");
    GameEngineDebug::OutPutString("F6: 프리 카메라 On/Off");
    GameEngineDebug::OutPutString("");
    GameEngineDebug::OutPutString("F7: 카메라 이동 제한 On/Off");
    GameEngineDebug::OutPutString("");
    GameEngineDebug::OutPutString("방향키: 플레이어 이동");
    GameEngineDebug::OutPutString("");
    GameEngineDebug::OutPutString("메인 카메라 이동 방법(플레이어 쫒기를 꺼야지만 가능.)");
    GameEngineDebug::OutPutString("    Home: 상, End:  하");
    GameEngineDebug::OutPutString("    Del:  좌, PgDn: 우");
}

void ContentsLevel::PrintPixelColor()
{
    float4 f4PixelData = mpPlayer->GetPixelData();
    GameEngineDebug::OutPutString("");
    GameEngineDebug::OutPutString("플레이어 발밑(-(y+5)) 픽셀 색상[R, G, B, A]");
    GameEngineDebug::OutPutString(
        "    " +
        std::to_string(f4PixelData.r) + ", " +
        std::to_string(f4PixelData.g) + ", " +
        std::to_string(f4PixelData.b) + ", " +
        std::to_string(f4PixelData.a) + ", "
    );
}

void ContentsLevel::PrintPlayerWorldPosition()
{
    GameEngineDebug::OutPutString("");
    GameEngineDebug::OutPutString("플레이어 월드 위치 [X, Y, Z, W]");
    GameEngineDebug::OutPutString(
        "    " +
        std::to_string(Player::GetPlayer()->GetTransform().GetWorldPosition().x) + ", " +
        std::to_string(Player::GetPlayer()->GetTransform().GetWorldPosition().y) + ", " +
        std::to_string(Player::GetPlayer()->GetTransform().GetWorldPosition().z) + ", " +
        std::to_string(Player::GetPlayer()->GetTransform().GetWorldPosition().w) + ", "
    );
}

void ContentsLevel::FreeCameraOnOff()
{
    GetMainCameraActor()->FreeCameraModeOnOff();
}

void ContentsLevel::LimitCameraMovingOnOff()
{
    mbLimitCameraMoving = !mbLimitCameraMoving;
}
