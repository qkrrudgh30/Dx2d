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
    mpRenderer->GetTransform().SetWorldPosition(float4{ 0.f, 0.f, OBJECTORDER::UI, 1.f });
    // mpRenderer->GetTransform().SetWorldScale({ mfWidth, mfHeight, 1 });

    mpRenderer->SetTexture("Temple3BackGround.png", 0);
    mpRenderer->ScaleToTexture();
    mfPrevCameraPosition = GetLevel()->GetMainCameraActorTransform().GetWorldPosition();
}

void Temple3BackGround::Update(float _DeltaTime)
{
    float4 fCurCameraPosition = GetLevel()->GetMainCameraActorTransform().GetWorldPosition();
    float4 fCurCameraDir = (fCurCameraPosition - mfPrevCameraPosition).NormalizeReturn();

    // mpRenderer->GetTransform().SetWorldMove(fCurCameraDir * float4{ 1.f, 0.01f, 1.f, 1.f } *_DeltaTime * 80.f);

    mfPrevCameraPosition = fCurCameraPosition;
}

void Temple3BackGround::End()
{
}
