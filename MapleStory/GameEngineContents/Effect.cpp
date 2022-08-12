#include "PreCompile.h"
#include "Effect.h"

Effect::Effect() 
	: mpRenderer(nullptr)
{
}

Effect::~Effect() 
{
}

void Effect::Start()
{
	mpRenderer->CreateFrameAnimationFolder("WarriorLeap", FrameAnimation_DESC("WarriorLeap", 0.1f));
}

void Effect::Update(float _DeltaTime)
{
}

void Effect::End()
{
}
