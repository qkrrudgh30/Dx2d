#include "PreCompile.h"
#include "Temple3Monster.h"

Temple3Monster::Temple3Monster() 
{
}

Temple3Monster::~Temple3Monster() 
{
}

void Temple3Monster::Start()
{
	mpRenderer = CreateComponent<GameEngineTextureRenderer>();
	mpRenderer->GetTransform().SetWorldScale({ 154, 212, 1 });
	mpRenderer->GetTransform().SetWorldPosition(float4{ 0.f, 0.f, OBJECTORDER::Mob, 1.f });
	mpRenderer->CreateFrameAnimation("Temple3MonsterStand", FrameAnimation_DESC("Temple3MonsterStand.png", 0, 11, 0.2f));
	mpRenderer->CreateFrameAnimation("Temple3MonsterMove", FrameAnimation_DESC("Temple3MonsterMove.png", 0, 5, 0.5f));
	mpRenderer->CreateFrameAnimation("Temple3MonsterHitting1", FrameAnimation_DESC("Temple3MonsterHitting1.png", 0, 3, 0.5f));
	mpRenderer->CreateFrameAnimation("Temple3MonsterHitting2", FrameAnimation_DESC("Temple3MonsterHitting2.png", 0, 6, 0.5f));
	mpRenderer->CreateFrameAnimation("Temple3MonsterDie", FrameAnimation_DESC("Temple3MonsterDie.png", 0, 11, 0.5f));
	mpRenderer->CreateFrameAnimation("Temple3MonsterAttack1", FrameAnimation_DESC("Temple3MonsterAttack1.png", 0, 16, 0.5f));
	mpRenderer->CreateFrameAnimation("Temple3MonsterAttack2", FrameAnimation_DESC("Temple3MonsterAttack2.png", 0, 16, 0.5f));
	mpRenderer->CreateFrameAnimation("Temple3MonsterHitted", FrameAnimation_DESC("Temple3MonsterHitted.png", 0, 0, 0.2f));
	mpRenderer->SetPivot(PIVOTMODE::BOT);
}

void Temple3Monster::Update(float _DeltaTime)
{
	mpRenderer->ChangeFrameAnimation("Temple3MonsterStand");
}

void Temple3Monster::End()
{
}
