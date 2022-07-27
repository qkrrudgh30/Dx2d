#include "PreCompile.h"
#include "EXPGauge.h"
#include <GameEngineCore/GameEngineTextureRenderer.h>

EXPGauge::EXPGauge() 
	: mpUIRenderer(nullptr)
{
}

EXPGauge::~EXPGauge() 
{
}

void EXPGauge::Start()
{
	mpUIRenderer = CreateComponent<GameEngineUIRenderer>();
	mpUIRenderer->SetTexture("EXPGauge.png");
	mpUIRenderer->GetTransform().SetLocalScale(float4{ GameEngineWindow::GetScale().x * 0.14875f * 0.5f, 18.f, 1.f, 1.f });
	mpUIRenderer->SetPivot(PIVOTMODE::LEFTTOP);
}

void EXPGauge::Update(float _DeltaTime)
{
}
