#include "PreCompile.h"
#include "ContentsActor.h"
#include "GlobalContentsValue.h"
#include <GameEngineCore/GameEngineTextureRenderer.h>

ContentsActor::ContentsActor()
	: mpRenderer(nullptr)
	, mfSpeed(0.f)
	, mfHP(0.f)
	, mfMP(0.f)
	, muPADamage(0u)
	, mfPASpeed(0.f)
	, muMADamage(0u)
	, mfMASpeed(0.f)
	, mfWidth(0.f)
	, mfHeight(0.f)
	, mbOnGround(false)
	, mbOnLadder(false)
	, mbHitted(false)
	, mbInvincible(false)
	, mStates{}
{
}

ContentsActor::~ContentsActor()
{
}

