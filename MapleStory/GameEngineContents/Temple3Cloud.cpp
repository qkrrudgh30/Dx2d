#include "PreCompile.h"
#include "Temple3Cloud.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

Temple3Cloud::Temple3Cloud()
	: mpRenderer(nullptr)
	, mfWidth(0)
	, mfHeight(0)
	, mfPositionX(0)
	, mfPositionY(0)
{
}

Temple3Cloud::~Temple3Cloud()
{
}

void Temple3Cloud::Start()
{
	mfWidth = 2327.f;
	mfHeight = 935.f;
	mpRenderer = CreateComponent<GameEngineTextureRenderer>();
	mpRenderer->SetTexture("Temple3Cloud.png", 0);
	mpRenderer->ScaleToTexture();
	// mpRenderer->GetTransform().SetLocalScale({ mfWidth, mfHeight, 1 });
}

void Temple3Cloud::Update(float _DeltaTime)
{
}

void Temple3Cloud::End()
{
}
