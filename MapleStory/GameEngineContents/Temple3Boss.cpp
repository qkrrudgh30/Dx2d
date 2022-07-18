#include "PreCompile.h"
#include "Temple3Boss.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

Temple3Boss::Temple3Boss()
	: mpRenderer(nullptr)
	, mfWidth(0)
	, mfHeight(0)
	, mfPositionX(0)
	, mfPositionY(0)
{
}

Temple3Boss::~Temple3Boss()
{
}

void Temple3Boss::Start()
{
	mfWidth = 2327.f;
	mfHeight = 935.f;
	mpRenderer = CreateComponent<GameEngineTextureRenderer>();
	mpRenderer->GetTransform().SetLocalScale({ mfWidth, mfHeight, 1 });

	mpRenderer->SetTexture("Temple3Boss.png", 0);
}

void Temple3Boss::Update(float _DeltaTime)
{
}

void Temple3Boss::End()
{
}
