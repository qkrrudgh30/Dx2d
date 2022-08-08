#include "PreCompile.h"
#include "Temple2Monster.h"
#include "GlobalContentsValue.h"
#include "ContentsLevel.h"
#include "PixelCollisionMap.h"
#include "RigidBody.h"
#include "Player.h"

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>

Temple2Monster::Temple2Monster() 
{
	mfSpeed = 100.f;
	mfHP = 50.f;
	mfMP = 100.f;
}

Temple2Monster::~Temple2Monster() 
{
}

void Temple2Monster::Start()
{
	Monster::Start();

	mfWidth = 115.f;
	mfHeight = 183.f;
	mpCollision->GetTransform().SetLocalScale(float4{mfWidth, mfHeight, 1.f, 1.f});
	
	mpRenderer->GetTransform().SetLocalScale(float4{ mfWidth, mfHeight, 1.f, 1.f });
	mpRenderer->GetTransform().SetWorldPosition(float4{ 0.f, 0.f, OBJECTORDER::Mob, 1.f});
	mpRenderer->CreateFrameAnimationCutTexture("Temple2MonsterStand", FrameAnimation_DESC("Temple2MonsterStand.png", 0, 11, 0.2f));
	mpRenderer->CreateFrameAnimationCutTexture("Temple2MonsterMove", FrameAnimation_DESC("Temple2MonsterMove.png", 0, 5, 0.5f));
	mpRenderer->CreateFrameAnimationCutTexture("Temple2MonsterHitting1", FrameAnimation_DESC("Temple2MonsterHitting1.png", 0, 3, 0.5f));
	mpRenderer->CreateFrameAnimationCutTexture("Temple2MonsterHitting2", FrameAnimation_DESC("Temple2MonsterHitting2.png", 0, 6, 0.5f));
	mpRenderer->CreateFrameAnimationCutTexture("Temple2MonsterDie", FrameAnimation_DESC("Temple2MonsterDie.png", 0, 11, 0.5f));
	mpRenderer->CreateFrameAnimationCutTexture("Temple2MonsterAttack1", FrameAnimation_DESC("Temple2MonsterAttack1.png", 0, 16, 0.5f));
	mpRenderer->AnimationBindEnd("Temple2MonsterAttack1", std::bind(&Temple2Monster::EndAttack1, this));
	mpRenderer->CreateFrameAnimationCutTexture("Temple2MonsterAttack2", FrameAnimation_DESC("Temple2MonsterAttack2.png", 0, 16, 0.5f));
	mpRenderer->AnimationBindEnd("Temple2MonsterAttack1", std::bind(&Temple2Monster::EndAttack1, this));
	mpRenderer->CreateFrameAnimationCutTexture("Temple2MonsterHitted", FrameAnimation_DESC("Temple2MonsterHitted.png", 0, 0, 0.2f));
	

	mStateManager.CreateStateMember("Stand",
		std::bind(&Temple2Monster::StandUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Temple2Monster::StandStart, this, std::placeholders::_1),
		std::bind(&Temple2Monster::StandEnd, this, std::placeholders::_1));

	mStateManager.CreateStateMember("Walk",
		std::bind(&Temple2Monster::WalkUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Temple2Monster::WalkStart, this, std::placeholders::_1),
		std::bind(&Temple2Monster::WalkEnd, this, std::placeholders::_1));

	mStateManager.CreateStateMember("Dead",
		std::bind(&Temple2Monster::DeadUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Temple2Monster::DeadStart, this, std::placeholders::_1),
		std::bind(&Temple2Monster::DeadEnd, this, std::placeholders::_1));

	mStateManager.CreateStateMember("Attack1",
		std::bind(&Temple2Monster::Attack1Update, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Temple2Monster::Attack1Start, this, std::placeholders::_1),
		std::bind(&Temple2Monster::Attack1End, this, std::placeholders::_1));

	mStateManager.CreateStateMember("Attack2",
		std::bind(&Temple2Monster::Attack2Update, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Temple2Monster::Attack2Start, this, std::placeholders::_1),
		std::bind(&Temple2Monster::Attack2End, this, std::placeholders::_1));

	mStateManager.CreateStateMember("Alert",
		std::bind(&Temple2Monster::AlertUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Temple2Monster::AlertStart, this, std::placeholders::_1),
		std::bind(&Temple2Monster::AlertEnd, this, std::placeholders::_1));

	mStateManager.ChangeState("Stand");

}

void Temple2Monster::Update(float _DeltaTime)
{
	mfAccTime += _DeltaTime;
	mpRenderer->SetPivot(PIVOTMODE::BOT);
	Monster::Update(_DeltaTime);
	mStateManager.Update(_DeltaTime);
	mpRenderer->ChangeFrameAnimation("Temple2MonsterStand");
	SetVincibleAfterSecond();

	mpCollision->IsCollision(CollisionType::CT_AABB2D, static_cast<int>(OBJECTORDER::CharacterAttack), CollisionType::CT_AABB2D,
		[=](GameEngineCollision* _This, GameEngineCollision* _Other)
		{
			ContentsActor* mpThis = dynamic_cast<ContentsActor*>(_This->GetActor());
			if (false == mbInvincible)
			{
				SetHitted(true);
				SetHP(GetHP() - 10.f);
			}

			mStateManager.ChangeState("Alert");

			return true;
		}
	);

	if (nullptr != mpParentLevel)
	{
		float temp = 0.f;
		mf4PixelDataOnRightSide = mpParentLevel->GetPCMap()->GetRenderer()->GetCurTexture()->GetPixel(GetTransform().GetWorldPosition().x + 100.f, -(GetTransform().GetWorldPosition().y + 10.f));
		temp = mf4PixelDataOnRightSide.r;
		mf4PixelDataOnRightSide.r = mf4PixelDataOnRightSide.b;
		mf4PixelDataOnRightSide.b = temp;
		mf4PixelDataOnLeftSide = mpParentLevel->GetPCMap()->GetRenderer()->GetCurTexture()->GetPixel(GetTransform().GetWorldPosition().x - 100.f, -(GetTransform().GetWorldPosition().y + 10.f));
		temp = mf4PixelDataOnLeftSide.r;
		mf4PixelDataOnLeftSide.r = mf4PixelDataOnLeftSide.b;
		mf4PixelDataOnLeftSide.b = temp;
	}
	
	/*GameEngineDebug::OutPutString(
		std::string("M") + ": " +
		std::to_string(mf4PixelDataOnLeftSide.r) + ", " + 
		std::to_string(mf4PixelDataOnLeftSide.g) + ", " + 
		std::to_string(mf4PixelDataOnLeftSide.b) + ", " + 
		std::to_string(mf4PixelDataOnLeftSide.a) + ", " + 
		std::to_string(mf4PixelDataOnRightSide.r) + ", " +
		std::to_string(mf4PixelDataOnRightSide.g) + ", " +
		std::to_string(mf4PixelDataOnRightSide.b) + ", " +
		std::to_string(mf4PixelDataOnRightSide.a)
	);*/
	
	
	/*GameEngineDebug::OutPutString(
		std::to_string(GetTransform().GetWorldPosition().x) + ", " +
		std::to_string(GetTransform().GetWorldPosition().y) + ", " +
		std::to_string(GetTransform().GetWorldPosition().z)
	);*/
	

	// Check moving available.

}

void Temple2Monster::End()
{
}

void Temple2Monster::EndAttack1()
{
	mStateManager.ChangeState("Stand");
}

void Temple2Monster::EndAttack2()
{
	mStateManager.ChangeState("Stand");
}

void Temple2Monster::StandStart(const StateInfo& _Info)
{
	mpRenderer->ChangeFrameAnimation("Temple2MonsterStand");
}

void Temple2Monster::StandUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// [D]Walk
	if (true == mState.mbLeftWalk)
	{
		mpRenderer->GetTransform().PixLocalPositiveX();
		mStateManager.ChangeState("Walk");
		return;
	}
	if (true == mState.mbRightWalk)
	{
		mpRenderer->GetTransform().PixLocalNegativeX();
		mStateManager.ChangeState("Walk");
		return;
	}

	// [D]Alert
	if (true == mbHitted && false == mbInvincible)
	{
		mStateManager.ChangeState("Alert");
		return;
	}

	//// [S]Attack1
	//if (true == GameEngineInput::GetInst()->IsPress("Temple2MonsterAttack1"))
	//{
	//	mStateManager.ChangeState("Attack1");
	//	return;
	//}
	//// [S]Attack2
	//if (true == GameEngineInput::GetInst()->IsPress("Temple2MonsterAttack2"))
	//{
	//	mStateManager.ChangeState("Attack2");
	//	return;
	//}
}

void Temple2Monster::WalkStart(const StateInfo& _Info)
{
	mpRenderer->ChangeFrameAnimation("Temple2MonsterMove");
}

void Temple2Monster::WalkUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// [D]Stand
	if (true == mState.mbStand)
	{
		mStateManager.ChangeState("Stand");
		return;
	}

	// [D]Alert
	if (true == mbHitted && false == mbInvincible)
	{
		mStateManager.ChangeState("Alert");
		return;
	}

	//// [D]Attack1
	//if (true == GameEngineInput::GetInst()->IsDown("Temple2MonsterAttack1"))
	//{
	//	mStateManager.ChangeState("Attack1");
	//	return;
	//}
	//// [D]Attack2
	//if (true == GameEngineInput::GetInst()->IsDown("Temple2MonsterAttack2"))
	//{
	//	mStateManager.ChangeState("Attack2");
	//	return;
	//}

	// [D]Move (Recursive)
	if (true == mState.mbLeftWalk && false == mState.mbRightWalk)
	{
		mpRenderer->GetTransform().PixLocalPositiveX();
		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * mfSpeed * _DeltaTime);
		return;
	}

	if (true == mState.mbRightWalk && false == mState.mbLeftWalk)
	{
		mpRenderer->GetTransform().PixLocalNegativeX();
		GetTransform().SetWorldMove(GetTransform().GetRightVector() * mfSpeed * _DeltaTime);
		return;
	}
}

void Temple2Monster::DeadStart(const StateInfo& _Info)
{
	mbInvincible = true;
	mpRenderer->ChangeFrameAnimation("Temple2MonsterDie");
}

void Temple2Monster::DeadUpdate(float _DeltaTime, const StateInfo& _Info)
{
	Death(1.f);
}

void Temple2Monster::Attack1Start(const StateInfo& _Info)
{
	mpRenderer->ChangeFrameAnimation("Temple2MonsterAttack1");
}

void Temple2Monster::Attack1Update(float _DeltaTime, const StateInfo& _Info)
{
}

void Temple2Monster::Attack2Start(const StateInfo& _Info)
{
	mpRenderer->ChangeFrameAnimation("Temple2MonsterAttack2");
}

void Temple2Monster::Attack2Update(float _DeltaTime, const StateInfo& _Info)
{
}

void Temple2Monster::AlertStart(const StateInfo& _Info)
{
	mbInvincible = true;
	mfBeforeAccTime = GetAccTime();
	mpRenderer->ChangeFrameAnimation("Temple2MonsterHitted");
}

void Temple2Monster::AlertUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (mfHP <= 0.f)
	{
		mStateManager.ChangeState("Dead");
		return;
	}

	//// [D]Stand
	//if (1.f <= _Info.StateTime)
	//{
	//	mbInvincible = false;
	//	mbHitted = false;
	//	mStateManager.ChangeState("Stand");
	//	return;
	//}
	// [D]Walk
	if (true == mState.mbLeftWalk)
	{
		mpRenderer->GetTransform().PixLocalPositiveX();
		mStateManager.ChangeState("Walk");
		return;
	}
	if (true == mState.mbRightWalk)
	{
		mpRenderer->GetTransform().PixLocalNegativeX();
		mStateManager.ChangeState("Walk");
		return;
	}
	//// [S]Attack1
	//if (true == GameEngineInput::GetInst()->IsPress("Temple2MonsterAttack1"))
	//{
	//	mStateManager.ChangeState("Attack1");
	//	return;
	//}
	//// [S]Attack2
	//if (true == GameEngineInput::GetInst()->IsPress("Temple2MonsterAttack2"))
	//{
	//	mStateManager.ChangeState("Attack2");
	//	return;
	//}
	// [S]Dead
	
}
