// <hide/>

// LoginLevel.h

#pragma once
#include "ContentsLevel.h"

// ���� :
class LoginBackground;
class LoginButton;
class ExitButton;
class LoginLevel : public ContentsLevel
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
    void OnEvent() override;
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    LoginBackground* mpLoginBackground;
    LoginButton*     mpLoginButton;
    ExitButton*      mpExitButton;
};

