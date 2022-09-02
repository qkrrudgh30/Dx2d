#include "PreCompile.h"
#include "Portion.h"

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>

Portion::Portion() 
{
	mfWidth = 30.f;
	mfHeight = 31.f;
}

Portion::~Portion() 
{
}

void Portion::Start()
{
	Item::Start();
	mpRenderer->CreateFrameAnimationCutTexture("WhitePortion", FrameAnimation_DESC("WhitePortion.png", 0, 0, 0.2f, false));
	mpRenderer->CreateFrameAnimationCutTexture("BluePortion", FrameAnimation_DESC("BluePortion.png", 0, 0, 0.2f, false));
	mpRenderer->CreateFrameAnimationCutTexture("Elixir", FrameAnimation_DESC("Elixir.png", 0, 0, 0.2f, false));

	mpCollision->GetTransform().SetLocalScale(float4{ mfWidth, mfHeight, 1.f, 1.f });
	mnOrder = static_cast<OBJECTORDER>(GetOrder());

	switch (mnOrder)
	{
	case OBJECTORDER::Portion1:
		muAmount = 10u;
		mpRenderer->ChangeFrameAnimation("WhitePortion");
		break;

	case OBJECTORDER::Portion2:

		muAmount = 10u;
		mpRenderer->ChangeFrameAnimation("BluePortion");
		break;

	case OBJECTORDER::Portion3:
		muAmount = 50u;
		mpRenderer->ChangeFrameAnimation("WhitePortion");
		break;

	default:
		mpRenderer->SetTexture("NSet.png");
		break;
	}

	mpRenderer->SetPivot(PIVOTMODE::BOT);
	mpRenderer->GetTransform().SetLocalScale(float4{ mfWidth, mfHeight, 1.f, 1.f });
}

void Portion::Update(float _fDeltaTime)
{
	Item::Update(_fDeltaTime);
}

void Portion::End()
{
	Item::End();
}
