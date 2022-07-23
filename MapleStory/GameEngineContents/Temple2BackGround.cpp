// <hide/>

// Temple2BackGround.cpp

#include "PreCompile.h"
#include "Temple2BackGround.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

Temple2BackGround::Temple2BackGround()
    : mpRenderer(nullptr)
    , mfWidth(0)
    , mfHeight(0)
    , mfPositionX(0)
    , mfPositionY(0)
{
}

Temple2BackGround::~Temple2BackGround()
{
}

void Temple2BackGround::Start()
{
    mfWidth = 2327.f;
    mfHeight = 935.f;
    mpRenderer = CreateComponent<GameEngineTextureRenderer>();
    // mpRenderer->GetTransform().SetWorldScale({ mfWidth, mfHeight, 1 });
    mpRenderer->GetTransform().SetWorldPosition(float4{ 0.f, 0.f, OBJECTORDER::BackGround, 1.f });
    mpRenderer->SetTexture("Temple2BackGround.png", 0);
    mpRenderer->ScaleToTexture();

}

void Temple2BackGround::Update(float _DeltaTime)
{
}

void Temple2BackGround::End()
{
}
