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
	mpRenderer->CreateFrameAnimationCutTexture("LeapAttack", FrameAnimation_DESC("LeapAttack.png", 0, 7, 0.1f, false));
	mpRenderer->CreateFrameAnimationCutTexture("SlashBlast", FrameAnimation_DESC("SlashBlast.png", 0, 10, 0.1f, false));
}

void Effect::Update(float _DeltaTime)
{
}

void Effect::End()
{
}
