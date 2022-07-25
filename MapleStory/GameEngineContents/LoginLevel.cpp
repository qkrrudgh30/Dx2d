// <hide/>

// LoginLevel.cpp

#include "PreCompile.h"
#include "LoginLevel.h"
#include "GlobalContentsValue.h"
#include "LoginBackground.h"
#include "LoginButton.h"
#include "ExitButton.h"
#include "Veil.h"

#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GameEngineCameraActor.h>

LoginLevel::LoginLevel() 
    : mpExitButton(nullptr)
    , mpLoginButton(nullptr)
    , mpLoginBackground(nullptr)
{
}

LoginLevel::~LoginLevel() 
{
}

void LoginLevel::OnEvent()
{
    Veil::SetVeilEffect(VEIL_EFFECT::FADE_IN);
}

void LoginLevel::Start()
{
    if (false == GameEngineInput::GetInst()->IsKey("MouseLButtonDown"))
    {
        GameEngineInput::GetInst()->CreateKey("MouseLButtonDown", VK_LBUTTON);
    }

    GameEngineCameraActor* actor = CreateActor<GameEngineCameraActor>();
    actor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
    actor->GetTransform().SetWorldPosition({ 0.0f, 0.0f, -500.0f });
    
    mpLoginBackground = CreateActor<LoginBackground>(OBJECTORDER::BackGround);
    mpLoginButton = CreateActor<LoginButton>(OBJECTORDER::UI);
    mpExitButton = CreateActor<ExitButton>(OBJECTORDER::UI);

    mpVeil = CreateActor<Veil>(OBJECTORDER::UI);
    // GameEngineSound::SoundPlayOneShot("BGM.mp3");
}

void LoginLevel::Update(float _DeltaTime)
{
    if (true == mpLoginButton->IsLoginButtonClicked())
    {
        Veil::SetVeilEffect(VEIL_EFFECT::FADE_OUT);
        mfVeilStartSecond = GetAccTime();
        mpLoginButton->SetLoginButton(false);
    }

    if (-1 != mfVeilStartSecond && 1.f <= GetAccTime() - mfVeilStartSecond)
    {
        GEngine::ChangeLevel("TempleOfTime0");
    }

    

    // GameEngineDebug::OutPutString(std::to_string(GetMainCamera()->GetScreenPosition().x) + "  " + std::to_string(GetMainCamera()->GetScreenPosition().y));
}

void LoginLevel::End()
{
}
