#include "PreCompile.h"
#include "Temple3Monster.h"
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

Temple3Monster::Temple3Monster() 
{
	mfWidth = 141.f;
	mfHeight = 208.f;
}

Temple3Monster::~Temple3Monster() 
{
}

void Temple3Monster::Start()
{
	Monster::Start();

	mpCollision->GetTransform().SetLocalScale(float4{ mfWidth, mfHeight, 1.f, 1.f });

	mpRenderer->GetTransform().SetLocalScale(float4{ mfWidth, mfHeight, 1.f, 1.f });
	mpRenderer->GetTransform().SetWorldPosition(float4{ 0.f, 0.f, OBJECTORDER::Mob, 1.f });
	mpRenderer->CreateFrameAnimationCutTexture("Temple3MonsterStand", FrameAnimation_DESC("Temple3MonsterStand.png", 0, 11, 0.2f));
	mpRenderer->CreateFrameAnimationCutTexture("Temple3MonsterMove", FrameAnimation_DESC("Temple3MonsterMove.png", 0, 11, 0.2f));
	mpRenderer->CreateFrameAnimationCutTexture("Temple3MonsterHitting1", FrameAnimation_DESC("Temple3MonsterHitting1.png", 0, 3, 0.5f));
	mpRenderer->CreateFrameAnimationCutTexture("Temple3MonsterHitting2", FrameAnimation_DESC("Temple3MonsterHitting2.png", 0, 6, 0.5f));
	mpRenderer->CreateFrameAnimationCutTexture("Temple3MonsterDie", FrameAnimation_DESC("Temple3MonsterDie.png", 0, 16, 0.2f, false));
	mpRenderer->CreateFrameAnimationCutTexture("Temple3MonsterAttack1", FrameAnimation_DESC("Temple3MonsterAttack1.png", 0, 34, 0.1f));
	mpRenderer->AnimationBindEnd("Temple3MonsterAttack1", std::bind(&Temple3Monster::EndAttack1, this));
	mpRenderer->CreateFrameAnimationCutTexture("Temple3MonsterAttack2", FrameAnimation_DESC("Temple3MonsterAttack2.png", 0, 22, 0.1f));
	mpRenderer->AnimationBindEnd("Temple3MonsterAttack2", std::bind(&Temple3Monster::EndAttack2, this));
	mpRenderer->CreateFrameAnimationCutTexture("Temple3MonsterHitted", FrameAnimation_DESC("Temple3MonsterHitted.png", 0, 0, 0.2f));
	mpRenderer->ChangeFrameAnimation("Temple3MonsterStand");

	mStateManager.CreateStateMember("Stand",
		std::bind(&Temple3Monster::StandUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Temple3Monster::StandStart, this, std::placeholders::_1),
		std::bind(&Temple3Monster::StandEnd, this, std::placeholders::_1));

	mStateManager.CreateStateMember("Walk",
		std::bind(&Temple3Monster::WalkUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Temple3Monster::WalkStart, this, std::placeholders::_1),
		std::bind(&Temple3Monster::WalkEnd, this, std::placeholders::_1));

	mStateManager.CreateStateMember("Dead",
		std::bind(&Temple3Monster::DeadUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Temple3Monster::DeadStart, this, std::placeholders::_1),
		std::bind(&Temple3Monster::DeadEnd, this, std::placeholders::_1));

	mStateManager.CreateStateMember("Attack1",
		std::bind(&Temple3Monster::Attack1Update, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Temple3Monster::Attack1Start, this, std::placeholders::_1),
		std::bind(&Temple3Monster::Attack1End, this, std::placeholders::_1));

	mStateManager.CreateStateMember("Attack2",
		std::bind(&Temple3Monster::Attack2Update, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Temple3Monster::Attack2Start, this, std::placeholders::_1),
		std::bind(&Temple3Monster::Attack2End, this, std::placeholders::_1));

	mStateManager.CreateStateMember("Alert",
		std::bind(&Temple3Monster::AlertUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Temple3Monster::AlertStart, this, std::placeholders::_1),
		std::bind(&Temple3Monster::AlertEnd, this, std::placeholders::_1));

	mStateManager.ChangeState("Stand");
}

void Temple3Monster::Update(float _DeltaTime)
{
	mfAccTime += _DeltaTime;
	mpRenderer->SetPivot(PIVOTMODE::BOT);
	Monster::Update(_DeltaTime);
	mStateManager.Update(_DeltaTime);

	mpCollision->IsCollision(CollisionType::CT_AABB2D, static_cast<int>(OBJECTORDER::CharacterAttack), CollisionType::CT_AABB2D,
		[=](GameEngineCollision* _This, GameEngineCollision* _Other)
		{
			ContentsActor* mpThis = dynamic_cast<ContentsActor*>(_This->GetActor());
			if (false == mpThis->IsInvincible())
			{
				SetHitted(true);
				SetInvincible(true);
				mbAttack = true;
				mfBeforeAccTimeForHit = GetAccTime();
				SetHP(GetHP() - 10.f);
				mStateManager.ChangeState("Alert");
			}

			return true;
		}
	);

	if (nullptr != mpParentLevel)
	{
		mf4PixelDataOnRightSide = mpParentLevel->GetPCMap()->GetRenderer()->GetCurTexture()->GetPixelToFloat4(GetTransform().GetWorldPosition().x + 100.f, -(GetTransform().GetWorldPosition().y + 10.f));
		mf4PixelDataOnLeftSide = mpParentLevel->GetPCMap()->GetRenderer()->GetCurTexture()->GetPixelToFloat4(GetTransform().GetWorldPosition().x - 100.f, -(GetTransform().GetWorldPosition().y + 10.f));
	}
}

void Temple3Monster::End()
{
}

void Temple3Monster::EndAttack1()
{
	mStateManager.ChangeState("Stand");
}

void Temple3Monster::EndAttack2()
{
	mStateManager.ChangeState("Stand");
}

void Temple3Monster::StandStart(const StateInfo& _Info)
{
	mpRenderer->ChangeFrameAnimation("Temple3MonsterStand");
}

void Temple3Monster::StandUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// [D]Walk
	/**/

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
}

void Temple3Monster::WalkStart(const StateInfo& _Info)
{
	mpRenderer->ChangeFrameAnimation("Temple3MonsterMove");
}

void Temple3Monster::WalkUpdate(float _DeltaTime, const StateInfo& _Info)
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

	if (false == mbAttack)
	{
		if (true == mState.mbLeftWalk)
		{
			mpRenderer->GetTransform().PixLocalPositiveX();
			GetTransform().SetWorldMove(GetTransform().GetLeftVector() * mfSpeed * _DeltaTime);
			return;
		}
		if (true == mState.mbRightWalk)
		{
			mpRenderer->GetTransform().PixLocalNegativeX();
			GetTransform().SetWorldMove(GetTransform().GetRightVector() * mfSpeed * _DeltaTime);
			return;
		}
	}
	else
	{
		GetTransform().SetWorldMove(-mf4DirectionToPlayer * mfSpeed * _DeltaTime);

		if (-mf4DirectionToPlayer.x <= 0.f)
		{
			mpRenderer->GetTransform().PixLocalPositiveX();
		}
		else
		{
			mpRenderer->GetTransform().PixLocalNegativeX();
		}

		if (mfDistanceFromPlayer <= 400.f)
		{
			// mbAttack = true;
			if (1.f - ((GetMaxHP() - GetHP()) / GetMaxHP()) <= 0.4f)
			{
				mStateManager.ChangeState("Attack1");
				return;
			}
			else
			{
				mStateManager.ChangeState("Attack2");
				return;
			}
		}
	}



}

void Temple3Monster::DeadStart(const StateInfo& _Info)
{
	SetInvincible(true);
	mpRenderer->ChangeFrameAnimation("Temple3MonsterDie");
	Death(2.f);
}

void Temple3Monster::DeadUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Temple3Monster::Attack1Start(const StateInfo& _Info)
{
	mpRenderer->ChangeFrameAnimation("Temple3MonsterAttack1");
}

void Temple3Monster::Attack1Update(float _DeltaTime, const StateInfo& _Info)
{
	if (true == mbAttack)
	{
		if (mfDistanceFromPlayer <= 400.f)
		{
			// mbAttack = true;
			if (1.f - ((GetMaxHP() - GetHP()) / GetMaxHP()) <= 0.4f)
			{
				mStateManager.ChangeState("Attack1");
			}
			else
			{
				mStateManager.ChangeState("Attack2");
			}
		}
		else
		{
			mStateManager.ChangeState("Walk");
		}
	}

}

void Temple3Monster::Attack2Start(const StateInfo& _Info)
{
	mpRenderer->ChangeFrameAnimation("Temple3MonsterAttack2");
}

void Temple3Monster::Attack2Update(float _DeltaTime, const StateInfo& _Info)
{
	if (true == mbAttack)
	{
		if (mfDistanceFromPlayer <= 400.f)
		{
			// mbAttack = true;
			if (1.f - ((GetMaxHP() - GetHP()) / GetMaxHP()) <= 0.4f)
			{
				mStateManager.ChangeState("Attack1");
			}
			else
			{
				mStateManager.ChangeState("Attack2");
			}
		}
		else
		{
			mStateManager.ChangeState("Walk");
		}
	}
}

void Temple3Monster::AlertStart(const StateInfo& _Info)
{
	mbInvincible = true;
	mfBeforeAccTimeForVincible = GetAccTime();
	mpRenderer->ChangeFrameAnimation("Temple3MonsterHitted");
}

void Temple3Monster::AlertUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (GetHP() <= 0.f)
	{
		mStateManager.ChangeState("Dead");
		SetHitted(false);
		return;
	}

	if (_Info.StateTime <= 0.5f)
	{
		return;
	}

	if (mfDistanceFromPlayer <= 400.f)
	{
		mbAttack = true;
		if (1.f - ((GetMaxHP() - GetHP()) / GetMaxHP()) <= 0.4f)
		{
			mStateManager.ChangeState("Attack1");
			SetHitted(false);
			return;
		}
		else
		{
			mStateManager.ChangeState("Attack2");
			SetHitted(false);
			return;
		}
	}
	else
	{
		mStateManager.ChangeState("Walk");
		SetHitted(false);
		return;
	}
}
