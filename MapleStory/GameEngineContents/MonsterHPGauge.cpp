#include "PreCompile.h"
#include "MonsterHPGauge.h"
#include "ContentsActor.h"
#include <GameEngineCore/GameEngineTextureRenderer.h>

MonsterHPGauge::MonsterHPGauge() 
	: mpBackgroundRenderer(nullptr)
	, mpGaugeRenderer(nullptr)
	, mfWidth(0.f)
	, mfHeight(0.f)
{

}

MonsterHPGauge::~MonsterHPGauge() 
{
}

void MonsterHPGauge::Start()
{
	mpGaugeRenderer = CreateComponent<GameEngineTextureRenderer>("MonsterHPGauge");
	mpGaugeRenderer->SetTexture("HPGauge.png");
	mpGaugeRenderer->GetTransform().SetLocalScale(float4{ 60.f, 10.f, 1.f, 1.f });
	mpGaugeRenderer->SetPivot(PIVOTMODE::LEFTTOP);

	mpBackgroundRenderer = CreateComponent<GameEngineTextureRenderer>("MonsterHPBackground");
	mpBackgroundRenderer->SetTexture("MonsterHPBackground.png");
	mpBackgroundRenderer->GetTransform().SetLocalScale(float4{ 60.f, 10.f, 1.f, 1.f });
	mpBackgroundRenderer->SetPivot(PIVOTMODE::LEFTTOP);

	
}

void MonsterHPGauge::Update(float _DeltaTime)
{
	if (nullptr == mpParentMonster) { return; }
	if (true == mpParentMonster->IsDeath()) { Death(); }
	mpGaugeRenderer->GetTransform().SetLocalScale(float4{ 60.f * (1.f - (mpParentMonster->GetMaxHP() - mpParentMonster->GetHP()) / mpParentMonster->GetMaxHP()), 10.f, 1.f, 1.f });
	mpGaugeRenderer->SetPivot(PIVOTMODE::LEFTTOP);
	// mpRenderer->GetTransform().SetLocalMove(float4{mpParentMonster->GetTransform().GetLocalPosition());
}

