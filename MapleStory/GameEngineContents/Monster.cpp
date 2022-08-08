#include "PreCompile.h"
#include "Monster.h"
#include "GlobalContentsValue.h"
#include "ContentsLevel.h"
#include "PixelCollisionMap.h"
#include "RigidBody.h"

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>

Player* Monster::spPlayer = nullptr;

Monster::Monster() 
	: mState()
	, mfPreAccTime(0.f)
{
}

Monster::~Monster() 
{
}

void Monster::Start()
{
	// mpParentLevel = GetLevel();
	
	mpCollision = CreateComponent<GameEngineCollision>();
	mpCollision->ChangeOrder(OBJECTORDER::Mob);
	mpRenderer = CreateComponent<GameEngineTextureRenderer>();
	mfPreAccTime = GetAccTime();

	if (nullptr != Player::GetPlayer())
	{
		spPlayer = Player::GetPlayer();
	}
}

void Monster::Update(float _DeltaTime)
{
	SetParentLevel(GetLevel());

	if (
		true == mf4PixelDataOnRightSide.CompareInt4D(float4{ 1.f, 1.f, 1.f, 0.f }) ||
		true == mf4PixelDataOnRightSide.CompareInt4D(float4{ 0.f, 0.f, 0.f, 0.f }) 
		)
	{
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
