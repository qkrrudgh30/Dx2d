// <hide/>

// GameEngineLevel.h

#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineUpdateObject.h>

// 설명 :
class GameEngineLevel :
    public GameEngineNameObject,
    public GameEngineUpdateObject
{
    friend class GameEngineCore; // 레벨이 현재까지 몇시간 동안 켜져 있었는지 시간을 잴 수 있게 함.

public:
    // constrcuter destructer
    GameEngineLevel();
    ~GameEngineLevel();

    // delete Function
    GameEngineLevel(const GameEngineLevel& _Other) = delete;
    GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
    GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
    GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

protected:
    virtual void UserStart() = 0;
    virtual void UserUpdate() = 0;
    virtual void UserEnd() = 0;

    virtual void OnEvent() {}
    virtual void OffEvent() {}

private:

};

