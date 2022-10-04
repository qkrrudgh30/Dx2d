// <hide/>

// LoginLevel.cpp

#include "PreCompile.h"
#include "LoginLevel.h"
#include "GlobalContentsValue.h"
#include "LoginBackground.h"
#include "LoginButton.h"
#include "ExitButton.h"
#include "Veil.h"
#include "Player.h"
#include "QuickSlot.h"

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

void LoginLevel::LevelStartEvent()
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
    
    mpLoginBackground = CreateActor<LoginBackground>(OBJECTORDER::UI);
    mpLoginButton = CreateActor<LoginButton>(OBJECTORDER::UI);
    mpExitButton = CreateActor<ExitButton>(OBJECTORDER::UI);

    mpVeil = CreateActor<Veil>(OBJECTORDER::UI);    
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
        mfVeilStartSecond = -1;
    }

    if (nullptr == mpPlayer)
    {
        mpPlayer = Player::GetPlayer();
        return;
    }

    if (nullptr == mpQuickSlot)
    {
        mpQuickSlot = QuickSlot::GetQuickSlot();
        return;
    }
    mpQuickSlot->Off();
    mpPlayer->Off();
    // GameEngineDebug::OutPutString(std::to_string(GetMainCamera()->GetScreenPosition().x) + "  " + std::to_string(GetMainCamera()->GetScreenPosition().y));
}

void LoginLevel::End()
{
    // GameEngineSound::SoundPlayControl("BGM.mp3", );
    mpQuickSlot->On();
    mpPlayer->On();
}
