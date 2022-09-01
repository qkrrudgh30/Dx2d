#include "PreCompile.h"
#include "Meso.h"

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>

Meso::Meso() 
{
	mfWidth = 32.f;
	mfHeight = 31.f;
}

Meso::~Meso() 
{
}

void Meso::Start()
{
	Item::Start();
	mpRenderer->CreateFrameAnimationCutTexture("MesoPeny", FrameAnimation_DESC("MesoPeny.png", 0, 3, 0.2f));
	mpRenderer->CreateFrameAnimationCutTexture("MesoBunch", FrameAnimation_DESC("MesoBunch.png", 0, 3, 0.2f));
	mpRenderer->CreateFrameAnimationCutTexture("MesoBag", FrameAnimation_DESC("MesoBag.png", 0, 3, 0.2f));

	mpCollision->GetTransform().SetLocalScale(float4{ mfWidth, mfHeight, 1.f, 1.f });
	mnOrder = OBJECTORDER::MesoItem;

	switch (GetOrder())
	{
	case static_cast<int>(OBJECTORDER::Meso1):
		muAmount = static_cast<unsigned int>(GameEngineRandom::MainRandom.RandomInt(1, 99));
		mpRenderer->ChangeFrameAnimation("MesoPeny");
		break;

	case static_cast<int>(OBJECTORDER::Meso2):
		
		muAmount = static_cast<unsigned int>(GameEngineRandom::MainRandom.RandomInt(100, 999));
		mpRenderer->ChangeFrameAnimation("MesoBunch");
		break;

	case static_cast<int>(OBJECTORDER::Meso3):
		
		muAmount = static_cast<unsigned int>(GameEngineRandom::MainRandom.RandomInt(1000, 9999));
		mpRenderer->ChangeFrameAnimation("MesoBag");
		break;

	default:
		mpRenderer->SetTexture("NSet.png");
		break;
	}

	mpRenderer->SetPivot(PIVOTMODE::BOT);
	mpRenderer->GetTransform().SetLocalScale(float4{mfWidth, mfHeight, 1.f, 1.f});
}

void Meso::Update(float _fDeltaTime)
{
	Item::Update(_fDeltaTime);
}

void Meso::End()
{
	Item::End();
}
