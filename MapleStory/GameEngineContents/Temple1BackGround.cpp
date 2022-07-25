// <hide/>

// Temple1BackGround.cpp

#include "PreCompile.h"
#include "Temple1BackGround.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

Temple1BackGround::Temple1BackGround()
    : mpRenderer(nullptr)
    , mfWidth(0)
    , mfHeight(0)
    , mfPositionX(0)
    , mfPositionY(0)
{
}

Temple1BackGround::~Temple1BackGround()
{
}

void Temple1BackGround::Start()
{
    mfWidth = 2327.f;
    mfHeight = 935.f;
    mpRenderer = CreateComponent<GameEngineTextureRenderer>();
    // mpRenderer->GetTransform().SetWorldScale({ mfWidth, mfHeight, 1 });
    mpRenderer->GetTransform().SetWorldPosition(float4{ 0.f, 0.f, OBJECTORDER::BackGround, 1.f });

    mpRenderer->SetTexture("Temple1BackGround.png", 0);
    mpRenderer->ScaleToTexture();
}

void Temple1BackGround::Update(float _DeltaTime)
{
}

void Temple1BackGround::End()
{
}
