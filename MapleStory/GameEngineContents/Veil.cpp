#include "PreCompile.h"
#include "Veil.h"

#include <GameEngineBase/GameEngineWindow.h>

Veil::Veil() 
	: mpRenderer(nullptr)
	, mf4Size()
{
}

Veil::~Veil() 
{
}

void Veil::Start()
{
	float4 windowSize = GameEngineWindow::GetScale();
	mpRenderer = CreateComponent<GameEngineTextureRenderer>();
	mpRenderer->GetTransform().SetLocalScale({ windowSize.x, windowSize.y, 1 });
	mpRenderer->SetTexture("Vail.png", 0);
}

void Veil::Update(float _DeltaTime)
{
}

void Veil::End()
{
}
