#include "PreCompile.h"
#include "Temple3Boss.h"

Temple3Boss::Temple3Boss()
{
}

Temple3Boss::~Temple3Boss()
{
}

void Temple3Boss::Start()
{
	mfWidth = 264.f;
	mfHeight = 188.f;
	mpRenderer = CreateComponent<GameEngineTextureRenderer>();
	mpRenderer->GetTransform().SetWorldScale(float4{ mfWidth, mfHeight, 1.f, 1.f });
	mpRenderer->GetTransform().SetWorldPosition(float4{ 0.f, 0.f, OBJECTORDER::Mob, 1.f });
	mpRenderer->CreateFrameAnimationCutTexture("Temple3BossStand", FrameAnimation_DESC("Temple3BossStand.png", 0, 7, 0.2f));
	mpRenderer->CreateFrameAnimationCutTexture("Temple3BossMove", FrameAnimation_DESC("Temple3BossMove.png", 0, 5, 0.5f));
	mpRenderer->CreateFrameAnimationCutTexture("Temple3BossHitting1", FrameAnimation_DESC("Temple3BossHitting1.png", 0, 3, 0.5f));
	mpRenderer->CreateFrameAnimationCutTexture("Temple3BossHitting2", FrameAnimation_DESC("Temple3BossHitting2.png", 0, 6, 0.5f));
	mpRenderer->CreateFrameAnimationCutTexture("Temple3BossDie", FrameAnimation_DESC("Temple3BossDie.png", 0, 11, 0.5f));
	mpRenderer->CreateFrameAnimationCutTexture("Temple3BossAttack1", FrameAnimation_DESC("Temple3BossAttack1.png", 0, 16, 0.5f));
	mpRenderer->CreateFrameAnimationCutTexture("Temple3BossAttack2", FrameAnimation_DESC("Temple3BossAttack2.png", 0, 16, 0.5f));
	mpRenderer->CreateFrameAnimationCutTexture("Temple3BossHitted", FrameAnimation_DESC("Temple3BossHitted.png", 0, 0, 0.2f));
	mpRenderer->SetPivot(PIVOTMODE::BOT);
}

void Temple3Boss::Update(float _DeltaTime)
{
	mpRenderer->ChangeFrameAnimation("Temple3BossStand");
}

void Temple3Boss::End()
{
}
