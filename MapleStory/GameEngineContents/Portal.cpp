#include "PreCompile.h"
#include "Portal.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

Portal::Portal()
	: mpRenderer(nullptr)
	, mfWidth(0)
	, mfHeight(0)
	, mfPositionX(0)
	, mfPositionY(0)
{
}

Portal::~Portal()
{
}

void Portal::Start()
{
	mfWidth = 89.f;
	mfHeight = 257.f;
	mpRenderer = CreateComponent<GameEngineTextureRenderer>();
	mpRenderer->GetTransform().SetLocalScale({ mfWidth, mfHeight, 1 });

	mpRenderer->SetTexture("Portal.png", 0);
	mpRenderer->CreateFrameAnimation("Portal", FrameAnimation_DESC("Portal.png", 0, 7, 0.1f));
}

void Portal::Update(float _DeltaTime)
{
	mpRenderer->ChangeFrameAnimation("Portal");
}

void Portal::End()
{
}
