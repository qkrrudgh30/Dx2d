// <hide/>

// LoginLevel.cpp

#include "PreCompile.h"
#include "LoginLevel.h"
#include "GlobalContentsValue.h"
#include "LoginBackground.h"
#include "LoginButton.h"
#include "ExitButton.h"

#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GameEngineCameraActor.h>

LoginLevel::LoginLevel() 
{
}

LoginLevel::~LoginLevel() 
{
}

void LoginLevel::Start()
{
    if (false == GameEngineInput::GetInst()->IsKey("MouseLButtonDown"))
    {
        GameEngineInput::GetInst()->CreateKey("MouseLButtonDown", VK_LBUTTON);
    }

    GameEngineCameraActor* actor = CreateActor<GameEngineCameraActor>();
    actor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
    actor->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -500.0f });
    
    mpLoginBackground = CreateActor<LoginBackground>(OBJECTORDER::BackGround);
    mpLoginButton = CreateActor<LoginButton>(OBJECTORDER::UI);
    mpExitButton = CreateActor<ExitButton>(OBJECTORDER::UI);
}

void LoginLevel::Update(float _DeltaTime)
{
}

void LoginLevel::End()
{
}
