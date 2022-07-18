#include "PreCompile.h"
#include "Temple3Monster.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

Temple3Monster::Temple3Monster()
	: mpRenderer(nullptr)
	, mfWidth(0)
	, mfHeight(0)
	, mfPositionX(0)
	, mfPositionY(0)
{
}

Temple3Monster::~Temple3Monster()
{
}

void Temple3Monster::Start()
{
	mfWidth = 2327.f;
	mfHeight = 935.f;
	mpRenderer = CreateComponent<GameEngineTextureRenderer>();
	mpRenderer->GetTransform().SetLocalScale({ mfWidth, mfHeight, 1 });

	mpRenderer->SetTexture("Temple3Monster.png", 0);
}

void Temple3Monster::Update(float _DeltaTime)
{
}

void Temple3Monster::End()
{
}
