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
    mpRenderer->GetTransform().SetWorldPosition(float4{ 0.f, 0.f, OBJECTORDER::UI, 1.f });
    mpRenderer->SetTexture("Temple2BackGround.png", 0);
    mpRenderer->ScaleToTexture();
    mfPrevCameraPosition = GetLevel()->GetMainCameraActorTransform().GetWorldPosition();

}

void Temple2BackGround::Update(float _DeltaTime)
{
    float4 fCurCameraPosition = GetLevel()->GetMainCameraActorTransform().GetWorldPosition();
    float4 fCurCameraDir = (fCurCameraPosition - mfPrevCameraPosition).NormalizeReturn();

    // mpRenderer->GetTransform().SetWorldMove(fCurCameraDir * float4{ 1.f, 0.01f, 1.f, 1.f } *_DeltaTime * 80.f);

    mfPrevCameraPosition = fCurCameraPosition;
}

void Temple2BackGround::End()
{
}
