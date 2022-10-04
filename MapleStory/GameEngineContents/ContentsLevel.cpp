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
    GameEngineDebug::OutPutString("F1: Ű ���� ���");
    GameEngineDebug::OutPutString("");
    GameEngineDebug::OutPutString("F2: ī�޶��� �÷��̾� �i�� On/Off");
    GameEngineDebug::OutPutString("");
    GameEngineDebug::OutPutString("F3: �ȼ� �浹 �� On/Off");
    GameEngineDebug::OutPutString("");
    GameEngineDebug::OutPutString("F4: �÷��̾� �߹� �ȼ��÷� ���");
    GameEngineDebug::OutPutString("");
    GameEngineDebug::OutPutString("F5: �÷��̾� ���� ��ġ ���(BOTTOM PIVOT)");
    GameEngineDebug::OutPutString("");
    GameEngineDebug::OutPutString("F6: ���� ī�޶� On/Off");
    GameEngineDebug::OutPutString("");
    GameEngineDebug::OutPutString("F7: ī�޶� �̵� ���� On/Off");
    GameEngineDebug::OutPutString("");
    GameEngineDebug::OutPutString("����Ű: �÷��̾� �̵�");
    GameEngineDebug::OutPutString("");
    GameEngineDebug::OutPutString("���� ī�޶� �̵� ���(�÷��̾� �i�⸦ �������� ����.)");
    GameEngineDebug::OutPutString("    Home: ��, End:  ��");
    GameEngineDebug::OutPutString("    Del:  ��, PgDn: ��");
}

void ContentsLevel::PrintPixelColor()
{
    float4 f4PixelData = mpPlayer->GetPixelData();
    GameEngineDebug::OutPutString("");
    GameEngineDebug::OutPutString("�÷��̾� �߹�(-(y+5)) �ȼ� ����[R, G, B, A]");
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
    GameEngineDebug::OutPutString("�÷��̾� ���� ��ġ [X, Y, Z, W]");
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
