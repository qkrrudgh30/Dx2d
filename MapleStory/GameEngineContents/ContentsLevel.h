#pragma once
#include <GameEngineCore/GameEngineLevel.h>

enum class PortalCollisionType
{
    NOTREADY,
    NEXT,
    PREVIOUS,
};

// 설명 :
class GameEngineCameraActor;
class Player;
class Portal;
class Veil;
class ContentsLevel : public GameEngineLevel
{
protected: // 자식 레벨들이 사용할 수 있게끔 접근제어자 protected.
    GameEngineCameraActor* mpCamera;
    Player*                mpPlayer;
    Portal*                mpPortalToNext;
    Portal*                mpPortalToPrevious;
    Veil*                  mpVeil;
    bool                   mbStart;
    float4                 mf4CameraPosition;
    float4                 mf4MapSize;
    float4                 mf4WindowSize;

public:
    // constrcuter destructer
    ContentsLevel();
    ~ContentsLevel();

    // delete Function
    ContentsLevel(const ContentsLevel& _Other) = delete;
    ContentsLevel(ContentsLevel&& _Other) noexcept = delete;
    ContentsLevel& operator=(const ContentsLevel& _Other) = delete;
    ContentsLevel& operator=(ContentsLevel&& _Other) noexcept = delete;

    void SetMapSize(float4 _mf4MapSize)
    {
        mf4MapSize = _mf4MapSize;
    }

    float4 GetMapSize()
    {
        return mf4MapSize;
    }

protected:
    void LimitCameraMoving();
    PortalCollisionType IsPortalCollided();

};
