#include "PreCompile.h"
#include "Portal.h"

Portal::Portal()
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
	mpRenderer->GetTransform().SetWorldScale({ mfWidth, mfHeight, 1 });
	mpRenderer->CreateFrameAnimationCutTexture("Portal", FrameAnimation_DESC("Portal.png", 0, 7, 0.1f));
	mpRenderer->ChangeFrameAnimation("Portal");
	mpRenderer->SetPivot(PIVOTMODE::BOT);
}

void Portal::Update(float _DeltaTime)
{
    
}

void Portal::End()
{
}
