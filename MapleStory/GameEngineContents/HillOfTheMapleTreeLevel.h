// HillOfTheMapleTreeLevel.h

#pragma once

#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class HillOfTheMapleTreeLevel : public GameEngineLevel
{
public:
    // constrcuter destructer
    HillOfTheMapleTreeLevel();
    ~HillOfTheMapleTreeLevel();

    // delete Function
    HillOfTheMapleTreeLevel(const HillOfTheMapleTreeLevel& _Other) = delete;
    HillOfTheMapleTreeLevel(HillOfTheMapleTreeLevel&& _Other) noexcept = delete;
    HillOfTheMapleTreeLevel& operator=(const HillOfTheMapleTreeLevel& _Other) = delete;
    HillOfTheMapleTreeLevel& operator=(HillOfTheMapleTreeLevel&& _Other) noexcept = delete;

protected:

private:
    virtual void UserStart() {}
    virtual void UserUpdate() {}
    virtual void UserEnd() {}

};

