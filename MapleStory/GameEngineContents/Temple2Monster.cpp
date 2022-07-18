#include "PreCompile.h"
#include "Temple2Monster.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

Temple2Monster::Temple2Monster()
	: mpRenderer(nullptr)
	, mfWidth(0)
	, mfHeight(0)
	, mfPositionX(0)
	, mfPositionY(0)
{
}

Temple2Monster::~Temple2Monster()
{
}

void Temple2Monster::Start()
{
	mfWidth = 2327.f;
	mfHeight = 935.f;
	mpRenderer = CreateComponent<GameEngineTextureRenderer>();
	mpRenderer->GetTransform().SetLocalScale({ mfWidth, mfHeight, 1 });

	mpRenderer->SetTexture("Temple2Monster.png", 0);
}

void Temple2Monster::Update(float _DeltaTime)
{
}

void Temple2Monster::End()
{
}
