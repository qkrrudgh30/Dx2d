// <hide/>

// Temple0BackGround.cpp

#include "PreCompile.h"
#include "Temple0BackGround.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

Temple0BackGround::Temple0BackGround()
    : mpRenderer(nullptr)
    , mfWidth(0)
    , mfHeight(0)
    , mfPositionX(0)
    , mfPositionY(0)
{
}

Temple0BackGround::~Temple0BackGround() 
{
}

void Temple0BackGround::Start()
{
    GetTransform().SetWorldPosition(float4{ 0.f, 0.f, OBJECTORDER::UI, 1.f });

    mfWidth = 2327.f;
    mfHeight = 935.f;
    mpRenderer = CreateComponent<GameEngineTextureRenderer>();
    mpRenderer->GetTransform().SetWorldPosition(float4{ 0.f, 0.f, OBJECTORDER::UI, 1.f });

    mpRenderer->SetTexture("Temple0BackGround.png", 0);
    mpRenderer->GetTransform().SetWorldScale({ mfWidth, mfHeight, 1 });
}

void Temple0BackGround::Update(float _DeltaTime)
{
}

void Temple0BackGround::End()
{
}
