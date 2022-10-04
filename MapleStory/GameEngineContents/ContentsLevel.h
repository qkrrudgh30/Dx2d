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
class StateBar;
class MenuButton;
class PopupMenu;
class QuickSlot;
class PixelCollisionMap;
class GameEngineSoundPlayer;
class ContentsLevel : public GameEngineLevel
{
protected: // 자식 레벨들이 사용할 수 있게끔 접근제어자 protected.
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
    QuickSlot*             mpQuickSlot;
    PixelCollisionMap*     mpPCMap;
    bool                   mbLimitCameraMoving;
    GameEngineSoundPlayer  mSoundPlayer;

    

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
    void PrintDescription();
    void PrintPixelColor();
    void PrintPlayerWorldPosition();
    void FreeCameraOnOff();
    void LimitCameraMovingOnOff();
    

};
