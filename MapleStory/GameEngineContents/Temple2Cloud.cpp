#include "PreCompile.h"
#include "Temple2Cloud.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

Temple2Cloud::Temple2Cloud()
	: mpRenderer(nullptr)
	, mfWidth(0)
	, mfHeight(0)
	, mfPositionX(0)
	, mfPositionY(0)
{
}

Temple2Cloud::~Temple2Cloud()
{
}

void Temple2Cloud::Start()
{
	mfWidth = 2327.f;
	mfHeight = 935.f;
	mpRenderer = CreateComponent<GameEngineTextureRenderer>();
	mpRenderer->SetTexture("Temple2Cloud.png", 0);
	mpRenderer->GetTransform().SetWorldPosition(float4{ 0.f, 0.f, OBJECTORDER::Cloud, 1.f });
	mpRenderer->ScaleToTexture();
	// mpRenderer->GetTransform().SetWorldScale({ mfWidth, mfHeight, 1 });
}

void Temple2Cloud::Update(float _DeltaTime)
{
}

void Temple2Cloud::End()
{
}
