#pragma once
#include <GameEngineCore/GameEngineLevel.h>

enum class PortalCollisionType
{
    NOTREADY,
    NEXT,
    PREVIOUS,
};

// ���� :
class GameEngineCameraActor;
class Player;
class Portal;
class Veil;
class StateBar;
class MenuButton;
class PopupMenu;
class PixelCollisionMap;
class ContentsLevel : public GameEngineLevel
{
protected: // �ڽ� �������� ����� �� �ְԲ� ���������� protected.
    GameEngineCameraActor* mpCamera;
    Player*                mpPlayer;
    Portal*                mpPortalToNext;
    Portal*                mpPortalToPrevious;
    Veil*                  mpVeil;
    float                  mfVeilStartSecond;
    bool                   mbStart;
    float4                 mf4CameraPosition;
    float4                 mf4MapSize;
    float4                 mf4WindowSize;
    StateBar*              mpStateBar;
    MenuButton*            mpMenuButton;
    PopupMenu*             mpPopupMenu;
    PixelCollisionMap*     mpPCMap;

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

    void SetPCMap(PixelCollisionMap* _pPCMap) { mpPCMap = _pPCMap; }
    PixelCollisionMap* GetPCMap() { return mpPCMap; }

protected:
    void LimitCameraMoving(float4 _f4MapSize);
    PortalCollisionType IsPortalCollided();
    void ChangeLevelWithSecond(std::string _Name, float _Second);

};
