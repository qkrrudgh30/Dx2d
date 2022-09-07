#include "PreCompile.h"
#include "Effect.h"

enum { DAMAGENUMBERCOUNT = 3 };

Effect::Effect() 
{
	mvDamageFonts.reserve(DAMAGENUMBERCOUNT);
}

Effect::~Effect() 
{
}

void Effect::Start()
{
	// mpParent = dynamic_cast<ContentsActor*>();

	GameEngineTextureRenderer* Temp;
	for (size_t i = 0; i < DAMAGENUMBERCOUNT; ++i)
	{
		Temp = CreateComponent<GameEngineTextureRenderer>();
		Temp->SetTexture("Clear.png");
		Temp->GetTransform().SetWorldScale(float4{37.f, 38.f, 1.f, 1.f});
		// Temp->GetTransform().SetWorldMove(float4{37.f * -i, 0.f, 0.f, 0.f});
		mvDamageFonts.push_back(Temp);
	}
}

void Effect::Update(float _DeltaTime)
{
}

void Effect::End()
{
}
