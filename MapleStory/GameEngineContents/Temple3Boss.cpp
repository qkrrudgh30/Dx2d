#include "PreCompile.h"
#include "Temple3Boss.h"
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

Temple3Boss::Temple3Boss()
{
	mfWidth = 243.f;
	mfHeight = 212.f;
}

Temple3Boss::~Temple3Boss()
{
}

void Temple3Boss::Start()
{
	Monster::Start();

	mpCollision->GetTransform().SetLocalScale(float4{ mfWidth, mfHeight, 1.f, 1.f });

	mpRenderer->GetTransform().SetLocalScale(float4{ mfWidth, mfHeight, 1.f, 1.f });
	mpRenderer->GetTransform().SetWorldPosition(float4{ 0.f, 0.f, OBJECTORDER::Mob, 1.f });
	mpRenderer->CreateFrameAnimationCutTexture("Temple3BossStand", FrameAnimation_DESC("Temple3BossStand.png", 0, 11, 0.2f));
	mpRenderer->CreateFrameAnimationCutTexture("Temple3BossMove", FrameAnimation_DESC("Temple3BossMove.png", 0, 5, 0.2f));
	mpRenderer->CreateFrameAnimationCutTexture("Temple3BossHitting1", FrameAnimation_DESC("Temple3BossHitting1.png", 0, 3, 0.5f));
	mpRenderer->CreateFrameAnimationCutTexture("Temple3BossHitting2", FrameAnimation_DESC("Temple3BossHitting2.png", 0, 6, 0.5f));
	mpRenderer->CreateFrameAnimationCutTexture("Temple3BossDie", FrameAnimation_DESC("Temple3BossDie.png", 0, 11, 0.2f, false));
	mpRenderer->CreateFrameAnimationCutTexture("Temple3BossAttack1", FrameAnimation_DESC("Temple3BossAttack1.png", 0, 12, 0.1f));
	mpRenderer->AnimationBindEnd("Temple3BossAttack1", std::bind(&Temple3Boss::EndAttack1, this));
	mpRenderer->CreateFrameAnimationCutTexture("Temple3BossAttack2", FrameAnimation_DESC("Temple3BossAttack2.png", 0, 14, 0.1f));
	mpRenderer->AnimationBindEnd("Temple3BossAttack2", std::bind(&Temple3Boss::EndAttack2, this));
	mpRenderer->CreateFrameAnimationCutTexture("Temple3BossHitted", FrameAnimation_DESC("Temple3BossHitted.png", 0, 0, 0.2f));
	mpRenderer->ChangeFrameAnimation("Temple3BossStand");

	mStateManager.CreateStateMember("Stand",
		std::bind(&Temple3Boss::StandUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Temple3Boss::StandStart, this, std::placeholders::_1),
		std::bind(&Temple3Boss::StandEnd, this, std::placeholders::_1));

	mStateManager.CreateStateMember("Walk",
		std::bind(&Temple3Boss::WalkUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Temple3Boss::WalkStart, this, std::placeholders::_1),
		std::bind(&Temple3Boss::WalkEnd, this, std::placeholders::_1));

	mStateManager.CreateStateMember("Dead",
		std::bind(&Temple3Boss::DeadUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Temple3Boss::DeadStart, this, std::placeholders::_1),
		std::bind(&Temple3Boss::DeadEnd, this, std::placeholders::_1));

	mStateManager.CreateStateMember("Attack1",
		std::bind(&Temple3Boss::Attack1Update, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Temple3Boss::Attack1Start, this, std::placeholders::_1),
		std::bind(&Temple3Boss::Attack1End, this, std::placeholders::_1));

	mStateManager.CreateStateMember("Attack2",
		std::bind(&Temple3Boss::Attack2Update, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Temple3Boss::Attack2Start, this, std::placeholders::_1),
		std::bind(&Temple3Boss::Attack2End, this, std::placeholders::_1));

	mStateManager.CreateStateMember("Alert",
		std::bind(&Temple3Boss::AlertUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Temple3Boss::AlertStart, this, std::placeholders::_1),
		std::bind(&Temple3Boss::AlertEnd, this, std::placeholders::_1));

	mStateManager.ChangeState("Stand");
}

void Temple3Boss::Update(float _DeltaTime)
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
		mf4PixelDataOnRightSide = mpParentLevel->GetPCMap()->GetRenderer()->GetCurTexture()->GetPixelToFloat4(GetTransform().GetWorldPosition().x + 100.f, -(GetTransform().GetWorldPosition().y + 10.f));
		mf4PixelDataOnLeftSide = mpParentLevel->GetPCMap()->GetRenderer()->GetCurTexture()->GetPixelToFloat4(GetTransform().GetWorldPosition().x - 100.f, -(GetTransform().GetWorldPosition().y + 10.f));
	}
}

void Temple3Boss::End()
{
}

void Temple3Boss::EndAttack1()
{
	mStateManager.ChangeState("Stand");
	// mbAttack = false;
}

void Temple3Boss::EndAttack2()
{
	mStateManager.ChangeState("Stand");
	// mbAttack = false;
}

void Temple3Boss::StandStart(const StateInfo& _Info)
{
	mpRenderer->ChangeFrameAnimation("Temple3BossStand");
}

void Temple3Boss::StandUpdate(float _DeltaTime, const StateInfo& _Info)
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

void Temple3Boss::WalkStart(const StateInfo& _Info)
{
	mpRenderer->ChangeFrameAnimation("Temple3BossMove");
}

void Temple3Boss::WalkUpdate(float _DeltaTime, const StateInfo& _Info)
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

void Temple3Boss::DeadStart(const StateInfo& _Info)
{
	SetInvincible(true);
	mpRenderer->ChangeFrameAnimation("Temple3BossDie");
	Death(2.f);
}

void Temple3Boss::DeadUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Temple3Boss::Attack1Start(const StateInfo& _Info)
{
	mpRenderer->ChangeFrameAnimation("Temple3BossAttack1");
}

void Temple3Boss::Attack1Update(float _DeltaTime, const StateInfo& _Info)
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

void Temple3Boss::Attack2Start(const StateInfo& _Info)
{
	mpRenderer->ChangeFrameAnimation("Temple3BossAttack2");
}

void Temple3Boss::Attack2Update(float _DeltaTime, const StateInfo& _Info)
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

void Temple3Boss::AlertStart(const StateInfo& _Info)
{
	mbInvincible = true;
	mfBeforeAccTimeForVincible = GetAccTime();
	mpRenderer->ChangeFrameAnimation("Temple3BossHitted");
}

void Temple3Boss::AlertUpdate(float _DeltaTime, const StateInfo& _Info)
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
