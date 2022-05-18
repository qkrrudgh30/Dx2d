// LoginLevel.h

#pragma once

#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class LoginLevel : public GameEngineLevel
{
public:
    // constrcuter destructer
    LoginLevel();
    ~LoginLevel();

    // delete Function
    LoginLevel(const LoginLevel& _Other) = delete;
    LoginLevel(LoginLevel&& _Other) noexcept = delete;
    LoginLevel& operator=(const LoginLevel& _Other) = delete;
    LoginLevel& operator=(LoginLevel&& _Other) noexcept = delete;

protected:

private:
    virtual void UserStart() {}
    virtual void UserUpdate() {}
    virtual void UserEnd() {}

};

