// <hide/>

// Guardian.cpp

#include "PreCompile.h"
#include "Guardian.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

Guardian::Guardian()
    : mpRenderer(nullptr)
    , mfWidth(0)
    , mfHeight(0)
    , mfPositionX(0)
    , mfPositionY(0)
{
}

Guardian::~Guardian()
{
}

void Guardian::Start()
{
    mfWidth = 2327.f;
    mfHeight = 935.f;
    mpRenderer = CreateComponent<GameEngineTextureRenderer>();
    mpRenderer->GetTransform().SetWorldScale({ mfWidth, mfHeight, 1 });

    mpRenderer->SetTexture("Guardian2.png", 0);
}

void Guardian::Update(float _DeltaTime)
{
}

void Guardian::End()
{
}
