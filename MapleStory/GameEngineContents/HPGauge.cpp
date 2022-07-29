#include "PreCompile.h"
#include "HPGauge.h"
#include <GameEngineCore/GameEngineUIRenderer.h>

HPGauge::HPGauge() 
	: mpUIRenderer(nullptr)
{
}

HPGauge::~HPGauge() 
{
}

void HPGauge::Start()
{
	mpUIRenderer = CreateComponent<GameEngineUIRenderer>();
	mpUIRenderer->SetTexture("HPGauge.png");
	mpUIRenderer->GetTransform().SetLocalScale(float4{ GameEngineWindow::GetScale().x * 0.13625f * 0.6f, 18.f, 1.f, 1.f });
	mpUIRenderer->SetPivot(PIVOTMODE::LEFTTOP);
}

void HPGauge::Update(float _DeltaTime)
{
}
