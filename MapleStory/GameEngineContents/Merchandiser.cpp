// <hide/>

// Merchandiser.cpp

#include "PreCompile.h"
#include "Merchandiser.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

Merchandiser::Merchandiser()
    : mpRenderer(nullptr)
    , mfWidth(0)
    , mfHeight(0)
    , mfPositionX(0)
    , mfPositionY(0)
{
}

Merchandiser::~Merchandiser()
{
}

void Merchandiser::Start()
{
    mfWidth = 2327.f;
    mfHeight = 935.f;
    mpRenderer = CreateComponent<GameEngineTextureRenderer>();
    mpRenderer->GetTransform().SetWorldScale({ mfWidth, mfHeight, 1 });

    mpRenderer->SetTexture("Merchandiser2.png", 0);
}

void Merchandiser::Update(float _DeltaTime)
{
}

void Merchandiser::End()
{
}
