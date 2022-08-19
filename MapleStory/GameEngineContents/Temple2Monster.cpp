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
	mfWidth = 115.f;
	mfHeight = 183.f;
}

Temple2Monster::~Temple2Monster()
{
}

void Temple2Monster::Start()
{
	Monster::Start();

	mpCollision->GetTransform().SetLocalScale(float4{ mfWidth, mfHeight, 1.f, 1.f });

	mpRenderer->GetTransform().SetLocalScale(float4{ mfWidth, mfHeight, 1.f, 1.f });
	mpRenderer->GetTransform().SetWorldPosition(float4{ 0.f, 0.f, OBJECTORDER::Mob, 1.f });
	mpRenderer->CreateFrameAnimationCutTexture("Temple2MonsterStand", FrameAnimation_DESC("Temple2MonsterStand.png", 0, 11, 0.2f));
	mpRenderer->CreateFrameAnimationCutTexture("Temple2MonsterMove", FrameAnimation_DESC("Temple2MonsterMove.png", 0, 5, 0.2f));
	mpRenderer->CreateFrameAnimationCutTexture("Temple2MonsterHitting1", FrameAnimation_DESC("Temple2MonsterHitting1.png", 0, 3, 0.5f));
	mpRenderer->CreateFrameAnimationCutTexture("Temple2MonsterHitting2", FrameAnimation_DESC("Temple2MonsterHitting2.png", 0, 6, 0.5f));
	mpRenderer->CreateFrameAnimationCutTexture("Temple2MonsterDie", FrameAnimation_DESC("Temple2MonsterDie.png", 0, 11, 0.2f, false));
	mpRenderer->CreateFrameAnimationCutTexture("Temple2MonsterAttack1", FrameAnimation_DESC("Temple2MonsterAttack1.png", 0, 16, 0.1f));
	mpRenderer->AnimationBindEnd("Temple2MonsterAttack1", std::bind(&Temple2Monster::EndAttack1, this));
	mpRenderer->CreateFrameAnimationCutTexture("Temple2MonsterAttack2", FrameAnimation_DESC("Temple2MonsterAttack2.png", 0, 16, 0.1f));
	mpRenderer->AnimationBindEnd("Temple2MonsterAttack2", std::bind(&Temple2Monster::EndAttack2, this));
	mpRenderer->CreateFrameAnimationCutTexture("Temple2MonsterHitted", FrameAnimation_DESC("Temple2MonsterHitted.png", 0, 0, 0.2f));
	mpRenderer->ChangeFrameAnimation("Temple2MonsterStand");

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
	// Update()에서는 boolean update만.
	// State::update()에서는 boolean에 따른 상태 변화.
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
		mf4PixelDataOnRightSide = mpParentLevel->GetPCMap()->GetRenderer()->GetCurTexture()->GetPixelToFloat4(
			static_cast<int>(GetTransform().GetWorldPosition().x + 100.f),
			static_cast<int>(-(GetTransform().GetWorldPosition().y + 10.f)));
		mf4PixelDataOnLeftSide = mpParentLevel->GetPCMap()->GetRenderer()->GetCurTexture()->GetPixelToFloat4(
			static_cast<int>(GetTransform().GetWorldPosition().x - 100.f),
			static_cast<int>(-(GetTransform().GetWorldPosition().y + 10.f)));
	}
}

void Temple2Monster::End()
{
}

void Temple2Monster::EndAttack1()
{
	mStateManager.ChangeState("Stand");
	// mbAttack = false;
}

void Temple2Monster::EndAttack2()
{
	mStateManager.ChangeState("Stand");
	// mbAttack = false;
}

void Temple2Monster::StandStart(const StateInfo& _Info)
{
	mpRenderer->ChangeFrameAnimation("Temple2MonsterStand");
}

void Temple2Monster::StandUpdate(float _DeltaTime, const StateInfo& _Info)
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

void Temple2Monster::DeadStart(const StateInfo& _Info)
{
	// SetInvincible(true);
	mbInvincible = true;
	mpRenderer->ChangeFrameAnimation("Temple2MonsterDie");
	Death(2.f);
}

void Temple2Monster::DeadUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Temple2Monster::Attack1Start(const StateInfo& _Info)
{
	mpRenderer->ChangeFrameAnimation("Temple2MonsterAttack1");
}

void Temple2Monster::Attack1Update(float _DeltaTime, const StateInfo& _Info)
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

void Temple2Monster::Attack2Start(const StateInfo& _Info)
{
	mpRenderer->ChangeFrameAnimation("Temple2MonsterAttack2");
}

void Temple2Monster::Attack2Update(float _DeltaTime, const StateInfo& _Info)
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

void Temple2Monster::AlertStart(const StateInfo& _Info)
{
	mbInvincible = true;
	mfBeforeAccTimeForVincible = GetAccTime();
	mpRenderer->ChangeFrameAnimation("Temple2MonsterHitted");
}

void Temple2Monster::AlertUpdate(float _DeltaTime, const StateInfo& _Info)
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
