// <hide/>

// Veil.cpp

#include "PreCompile.h"
#include "Veil.h"

#include <GameEngineCore/GameEngineDefaultRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

VEIL_EFFECT                Veil::meVeilEffect;
std::queue<VEIL_EFFECT>    Veil::mqVeilEffectJobQueue;

Veil::Veil() 
    : mpRenderer(nullptr)
    , mf4Size()
    , mf4Color(float4{ 0.f, 0.f, 0.f, 1.f })
{
}

Veil::~Veil() 
{
}

void Veil::Start()
{
    float4 windowSize = GameEngineWindow::GetScale();
    mpRenderer = CreateComponent<GameEngineDefaultRenderer>();
    mpRenderer->GetActor()->GetLevel()->PushRendererToMainCamera(mpRenderer);
    mpRenderer->SetPipeLine("Color");
    mpRenderer->ShaderResources.SetConstantBufferLink("ResultColor", mf4Color);
    mpRenderer->GetTransform().SetWorldScale({ windowSize.x, windowSize.y, 1.f, 1.f });
    GetTransform().SetWorldPosition(float4{ 0.f, 0.f, OBJECTORDER::Alpha, 1.f });
}

void Veil::Update(float _DeltaTime)
{
    if (true == mqVeilEffectJobQueue.empty())
    {
        return;
    }
    meVeilEffect = mqVeilEffectJobQueue.front();
    
    if (VEIL_EFFECT::FADE_IN == meVeilEffect)
    {
        mf4Color.a -= 1.f * _DeltaTime;
        if (mf4Color.a <= 0.f) 
        { 
            mf4Color.a = 0.f;
            mqVeilEffectJobQueue.pop();
        }
    }
    if (VEIL_EFFECT::FADE_OUT == meVeilEffect)
    {
        mf4Color.a += 1.f * _DeltaTime;
        if (1.f <= mf4Color.a) 
        { 
            mf4Color.a = 1.f; 
            mqVeilEffectJobQueue.pop();
        }
    }
}

void Veil::End()
{
}
