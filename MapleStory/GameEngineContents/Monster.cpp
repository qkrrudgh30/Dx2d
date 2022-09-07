#include "PreCompile.h"
#include "Monster.h"
#include "GlobalContentsValue.h"
#include "ContentsLevel.h"
#include "PixelCollisionMap.h"
#include "RigidBody.h"
#include "MonsterHPGauge.h"

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>

Player* Monster::spPlayer = nullptr;

enum { DAMAGENUMBERCOUNT = 3 };

Monster::Monster() 
	: mState()
	, mfPreAccTime(0.f)
	, mbAttack(false)
	, mfDistanceFromPlayer(0.f)
	, mpMonsterHP(nullptr)
	, mpEffect(nullptr)
	, muHittedDamage(0u)
{
	mfSpeed = 100.f;
	mfMaxHP = 50.f;
	mfHP = 50.f;
	mfMaxMP = 100.f;
	mfMP = 100.f;
}

Monster::~Monster() 
{
}

void Monster::SetDamageFont(unsigned int _nDamage)
{
	for (size_t i = 0; ; ++i)
	{
		int n = _nDamage % 10;
		_nDamage /= 10;
		mvDamageFonts[i]->SetTexture(std::to_string(n) + ".png");
		mvDamageFonts[i]->GetTransform().SetWorldPosition(float4{-36.f * i, 170.f, 0.f, 0.f});
		mvDamageFonts[i]->GetColorData().MulColor.a = 1.f;
		if (_nDamage <= 0) { break; }
	}
}

void Monster::SetDamageFontFading(float _fDeltaTime)
{
	std::string Temp = mvDamageFonts[0]->GetCurTexture()->GetNameCopy();
	if ("CLEAR.PNG" == Temp)
	{ 
		return; 
	}

	for (size_t i = 0; i < mvDamageFonts.size(); ++i)
	{
		mvDamageFonts[i]->GetTransform().SetWorldMove(float4{0.f, 10.f * _fDeltaTime, 0.f, 0.f});
		mvDamageFonts[i]->GetColorData().MulColor.a += -1.f * _fDeltaTime;
	}
}

void Monster::Start()
{
	mpCollision = CreateComponent<GameEngineCollision>();
	mpCollision->ChangeOrder(OBJECTORDER::Mob);
	mpRenderer = CreateComponent<GameEngineTextureRenderer>();
	mfPreAccTime = GetAccTime();

	mpMonsterHP = GetLevel()->CreateActor<MonsterHPGauge>();
	mpMonsterHP->SetParentMonster(this);

	mpRenderer->SetScaleModeImage();

	mvDamageFonts.reserve(DAMAGENUMBERCOUNT);
	GameEngineTextureRenderer* Temp;
	for (size_t i = 0; i < DAMAGENUMBERCOUNT; ++i)
	{
		Temp = CreateComponent<GameEngineTextureRenderer>();
		Temp->SetTexture("Clear.png");
		Temp->GetTransform().SetWorldScale(float4{ 37.f, 38.f, 1.f, 1.f });
		Temp->GetTransform().SetWorldMove(float4{ -37.f * i, 170.f, 0.f, 0.f });
		mvDamageFonts.push_back(Temp);
	}
	mf4DamageFontPosition = mvDamageFonts[0]->GetTransform().GetWorldPosition();
}

void Monster::Update(float _DeltaTime)
{
	SetDamageFontFading(_DeltaTime);
	if (nullptr != Player::GetPlayer())
	{
		spPlayer = Player::GetPlayer();
		mf4DirectionToPlayer = (this->GetTransform().GetWorldPosition() - spPlayer->GetTransform().GetWorldPosition()).NormalizeReturn();
		mf4DirectionToPlayer.y = 0.f; mf4DirectionToPlayer.z = 0.f; mf4DirectionToPlayer.w = 0.f;
		mfDistanceFromPlayer = (this->GetTransform().GetWorldPosition() - spPlayer->GetTransform().GetWorldPosition()).Length();
	}

	SetHittedAfterSecond();
	SetVincibleAfterSecond();

	SetParentLevel(GetLevel());
	mpMonsterHP->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition() + float4{ -35.f, 150.f, 0.f, 0.f });

	if (
		true == mf4PixelDataOnRightSide.CompareInt4D(float4{ 1.f, 1.f, 1.f, 0.f }) ||
		true == mf4PixelDataOnRightSide.CompareInt4D(float4{ 0.f, 0.f, 0.f, 0.f }) 
		)
	{
		// if (this->GetNameCopy().)
		mState.AllState = 0;
		mState.mbLeftWalk = true;
		return;
	}

	if (
		true == mf4PixelDataOnLeftSide.CompareInt4D(float4{ 1.f, 1.f, 1.f, 0.f }) ||
		true == mf4PixelDataOnLeftSide.CompareInt4D(float4{ 0.f, 0.f, 0.f, 0.f }) 
		)
	{
		mState.AllState = 0;
		mState.mbRightWalk = true;
		return;
	}

	if (2.f <= GetAccTime() - mfPreAccTime)
	{
		int iRandomNumber = GameEngineRandom::MainRandom.RandomInt(0, 2);
		if (0 == iRandomNumber)
		{
			if (false == mf4PixelDataOnLeftSide.CompareInt4D(float4{ 1.f, 1.f, 1.f, 0.f }) &&
			    false == mf4PixelDataOnLeftSide.CompareInt4D(float4{ 0.f, 0.f, 0.f, 0.f }))
			{
				mState.AllState = 0;
				mState.mbLeftWalk = true;
			}
		}
		else if (1 == iRandomNumber)
		{
			if (false == mf4PixelDataOnRightSide.CompareInt4D(float4{ 1.f, 1.f, 1.f, 0.f }) &&
				false == mf4PixelDataOnRightSide.CompareInt4D(float4{ 0.f, 0.f, 0.f, 0.f }))
			{
				mState.AllState = 0;
				mState.mbRightWalk = true;
			}
		}
		else
		{
			mState.AllState = 0;
			mState.mbStand = true;
		}
		mfPreAccTime = GetAccTime();
	}
}
