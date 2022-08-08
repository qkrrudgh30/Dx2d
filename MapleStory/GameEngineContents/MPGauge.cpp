#include "PreCompile.h"
#include "MPGauge.h"
#include <GameEngineCore/GameEngineTextureRenderer.h>

MPGauge::MPGauge() 
	: mpUIRenderer(nullptr)
{
}

MPGauge::~MPGauge() 
{
}

void MPGauge::Start()
{
	mpUIRenderer = CreateComponent<GameEngineUIRenderer>();
	mpUIRenderer->SetTexture("MPGauge.png");
	mpUIRenderer->GetTransform().SetLocalScale(float4{ GameEngineWindow::GetScale().x * 0.135f, 18.f, 1.f, 1.f });
	mpUIRenderer->SetPivot(PIVOTMODE::LEFTTOP); // GetTransform().SetLocalPosition(_Value);
}

void MPGauge::Update(float _DeltaTime)
{
	Player* pPlayer = Player::GetPlayer();
	mpUIRenderer->GetTransform().SetLocalScale(float4{ GameEngineWindow::GetScale().x * 0.135f * ((pPlayer->GetMP()) / 100.f), 18.f, 1.f, 1.f });
	mpUIRenderer->SetPivot(PIVOTMODE::LEFTTOP); // GetTransform().SetLocalPosition(zero);
}

