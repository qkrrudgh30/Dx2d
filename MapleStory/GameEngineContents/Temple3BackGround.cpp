// <hide/>

// Temple3BackGround.cpp

#include "PreCompile.h"
#include "Temple3BackGround.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

Temple3BackGround::Temple3BackGround()
    : mpRenderer(nullptr)
    , mfWidth(0)
    , mfHeight(0)
    , mfPositionX(0)
    , mfPositionY(0)
{
}

Temple3BackGround::~Temple3BackGround()
{
}

void Temple3BackGround::Start()
{
    mfWidth = 2327.f;
    mfHeight = 935.f;
    mpRenderer = CreateComponent<GameEngineTextureRenderer>();
    // mpRenderer->GetTransform().SetLocalScale({ mfWidth, mfHeight, 1 });

    mpRenderer->SetTexture("Temple3BackGround.png", 0);
    mpRenderer->ScaleToTexture();
}

void Temple3BackGround::Update(float _DeltaTime)
{
}

void Temple3BackGround::End()
{
}
