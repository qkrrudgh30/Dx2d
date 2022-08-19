#include "PreCompile.h"
#include "Player.h"
#include "GlobalContentsValue.h"
#include "ContentsLevel.h"
#include "PixelCollisionMap.h"
#include "RigidBody.h"
#include <functional>

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineFontRenderer.h>

Player* Player::spPlayer = nullptr;

Player::Player()
	: mf4PixelData()
	, mStateManager()
	, mbOnAboveGround(false)
	, mpRigidBody(nullptr)
{
	mfSpeed = 400.f;
	spPlayer = this;
	mfHP = 50.f;
	mfMP = 100.f;
}

Player::~Player()
{
}

void Player::Start()
{
	mpCollision = CreateComponent<GameEngineCollision>("PlayerCollision");
	mpCollision->GetTransform().SetLocalScale(float4{ mfWidth, mfHeight, 1.f, 1.f });
	// mpCollision->GetTransform().SetLocalMove(float4{0.f, 0.f, -100.f, 1.f});
	mpCollision->ChangeOrder(OBJECTORDER::Character);
	mpCollision->SetDebugSetting(CollisionType::CT_AABB, float4{1.f, 0.f, 0.f, 0.5f});

	mpRenderer = CreateComponent<GameEngineTextureRenderer>();
	mfWidth = 83.f;
	mfHeight = 85.f;
	mpRenderer->GetTransform().SetLocalScale({ mfWidth, mfHeight, 1.f, 1.f });
	// mpRenderer->ScaleToTexture();
	mpRenderer->CreateFrameAnimationCutTexture("CharacterAlert", FrameAnimation_DESC("CharacterAlert.png", 0, 4, 0.5f));
	mpRenderer->CreateFrameAnimationCutTexture("CharacterJump", FrameAnimation_DESC("CharacterJump.png", 0, 0, 0.5f));
	mpRenderer->CreateFrameAnimationCutTexture("CharacterLadderIdle", FrameAnimation_DESC("CharacterLadderIdle.png", 0, 0, 0.5f));
	mpRenderer->CreateFrameAnimationCutTexture("CharacterLadderMove", FrameAnimation_DESC("CharacterLadderMove.png", 0, 1, 0.5f));
	mpRenderer->CreateFrameAnimationCutTexture("CharacterStab", FrameAnimation_DESC("CharacterStab.png", 0, 2, 0.2f, false));
	mpRenderer->AnimationBindEnd("CharacterStab", std::bind(&Player::EndAttack1, this, std::placeholders::_1));
	mpRenderer->CreateFrameAnimationCutTexture("CharacterStabF", FrameAnimation_DESC("CharacterStabF.png", 0, 3, 0.2f, false));
	mpRenderer->AnimationBindEnd("CharacterStabF", std::bind(&Player::EndFinalAttack1, this));
	mpRenderer->CreateFrameAnimationCutTexture("CharacterStand", FrameAnimation_DESC("CharacterStand.png", 0, 4, 0.5f));
	mpRenderer->CreateFrameAnimationCutTexture("CharacterSwing", FrameAnimation_DESC("CharacterSwing.png", 0, 2, 0.2f, false));
	mpRenderer->AnimationBindEnd("CharacterSwing", std::bind(&Player::EndAttack2, this));
	mpRenderer->CreateFrameAnimationCutTexture("CharacterSwingF", FrameAnimation_DESC("CharacterSwingF.png", 0, 3, 0.2f, false));
	mpRenderer->AnimationBindEnd("CharacterSwingF", std::bind(&Player::EndFinalAttack2, this));
	mpRenderer->CreateFrameAnimationCutTexture("CharacterWalk", FrameAnimation_DESC("CharacterWalk.png", 0, 5, 0.2f));
	mpRenderer->CreateFrameAnimationCutTexture("CharacterDead", FrameAnimation_DESC("CharacterDead.png", 0, 0, 0.2f));
	mpRenderer->SetScaleModeImage();
	
	SetGround(false);
	mpRigidBody = CreateComponent<RigidBody>();

	mStateManager.CreateStateMember("Stand", 
		std::bind(& Player::StandUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(& Player::StandStart, this, std::placeholders::_1),
		std::bind(& Player::StandEnd, this, std::placeholders::_1));

	mStateManager.CreateStateMember("Walk",
		std::bind(&Player::WalkUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Player::WalkStart, this, std::placeholders::_1),
		std::bind(&Player::WalkEnd, this, std::placeholders::_1));

	mStateManager.CreateStateMember("Dead",
		std::bind(&Player::DeadUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Player::DeadStart, this, std::placeholders::_1),
		std::bind(&Player::DeadEnd, this, std::placeholders::_1));

	mStateManager.CreateStateMember("Attack",
		std::bind(&Player::AttackUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Player::AttackStart, this, std::placeholders::_1),
		std::bind(&Player::AttackEnd, this, std::placeholders::_1));

	mStateManager.CreateStateMember("Jump",
		std::bind(&Player::JumpUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Player::JumpStart, this, std::placeholders::_1),
		std::bind(&Player::JumpEnd, this, std::placeholders::_1));

	mStateManager.CreateStateMember("Ladder",
		std::bind(&Player::LadderUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Player::LadderStart, this, std::placeholders::_1),
		std::bind(&Player::LadderEnd, this, std::placeholders::_1));

	mStateManager.CreateStateMember("Alert",
		std::bind(&Player::AlertUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Player::AlertStart, this, std::placeholders::_1),
		std::bind(&Player::AlertEnd, this, std::placeholders::_1));

    mStateManager.ChangeState("Stand");

	GameEngineFontRenderer* Font = CreateComponent<GameEngineFontRenderer>();
	Font->SetText("안녕하세요", "메이플스토리");
	Font->SetColor({ 0.0f, 0.0f, 0.0f });
	Font->SetScreenPostion({ 100.0f, 100.0f, -460.f, 1.f });
}

void Player::Update(float _DeltaTime)
{
	mfAccTime += _DeltaTime;
	mpRenderer->SetPivot(PIVOTMODE::BOT);

	SetVincibleAfterSecond();

	mStateManager.Update(_DeltaTime);

	/*if (true == GameEngineInput::GetInst()->IsDown("PlayerDoubleJump"))
	{
		mfMP -= 10.f;
		mpRenderer->ChangeFrameAnimation("WarriorLeap");
	}*/

	mpCollision->IsCollision(CollisionType::CT_AABB2D, static_cast<int>(OBJECTORDER::Mob), CollisionType::CT_AABB2D,
		[=](GameEngineCollision* _This, GameEngineCollision* _Other)
		{
			ContentsActor* mpThis = dynamic_cast<ContentsActor*>(_This->GetActor());

			if (false == mbInvincible)
			{
				mpThis->SetHitted(true);
				mpThis->SetHP(mpThis->GetHP() - 10.f);
			}

			return true;
		}
	);

#pragma region PixelCollision
	if (nullptr != mpParentLevel)
	{
		mf4PixelData = mpParentLevel->GetPCMap()->GetRenderer()->GetCurTexture()->GetPixelToFloat4(
			static_cast<int>(GetTransform().GetWorldPosition().x), 
			static_cast<int>(-(GetTransform().GetWorldPosition().y + 5.f)));
		mf4HeadPixelData = mpParentLevel->GetPCMap()->GetRenderer()->GetCurTexture()->GetPixelToFloat4(
			static_cast<int>(GetTransform().GetWorldPosition().x),
			static_cast<int>(-(GetTransform().GetWorldPosition().y + 80.f)));
		mf4PixelDataOnRightSide = mpParentLevel->GetPCMap()->GetRenderer()->GetCurTexture()->GetPixelToFloat4(
			static_cast<int>(GetTransform().GetWorldPosition().x + 25.f), 
			static_cast<int>(-(GetTransform().GetWorldPosition().y + 5.f)));
		mf4PixelDataOnLeftSide = mpParentLevel->GetPCMap()->GetRenderer()->GetCurTexture()->GetPixelToFloat4(
			static_cast<int>(GetTransform().GetWorldPosition().x - 25.f), 
			static_cast<int>(-(GetTransform().GetWorldPosition().y + 5.f)));
	}

	if (true == mf4PixelData.CompareInt4D(float4::MAGENTA) ||
		true == mf4PixelData.CompareInt4D(float4::CYAN) ||
		true == mf4PixelDataOnLeftSide.CompareInt4D(float4::CYAN) ||
		true == mf4PixelDataOnRightSide.CompareInt4D(float4::CYAN)
		)
	{
		mbOnGround = true;
	}
	else
	{
		mbOnGround = false;
	}

	//if (true == mf4PixelData.CompareInt4D(float4::YELLOW))
	//{
	//	mbOnLadder = true;
	//}
	//else
	//{
	//	mbOnLadder = false;
	//}

	if (true == mf4PixelDataOnLeftSide.CompareInt4D(float4::CYAN) ||
		true == mf4PixelDataOnRightSide.CompareInt4D(float4::CYAN))
	{
		mbOnAboveGround = true;
	}
	else
	{
		mbOnAboveGround = false;
	}
#pragma endregion

}

void Player::End()
{
}

void Player::EndAttack1(const FrameAnimation_DESC& _Info)
{
	int nRandomNumber = GameEngineRandom::MainRandom.RandomInt(1, 100);
	if (nRandomNumber <= 60)
	{
		mbInvincible = true;
		mfBeforeAccTimeForVincible = GetAccTime();
		mpRenderer->ChangeFrameAnimation("CharacterStabF");
	}
	else
	{
		mStateManager.ChangeState("Stand");
	}
}

void Player::EndAttack2()
{
	int nRandomNumber = GameEngineRandom::MainRandom.RandomInt(1, 100);
	if (nRandomNumber <= 60)
	{
		mbInvincible = true;
		mfBeforeAccTimeForVincible = GetAccTime();
		mpRenderer->ChangeFrameAnimation("CharacterSwingF");
	}
	else
	{
		mStateManager.ChangeState("Stand");
	}
}

void Player::EndFinalAttack1()
{
	GameEngineCollision* AttackCollision = CreateComponent<GameEngineCollision>("AttackCollision");
	AttackCollision->GetTransform().SetLocalScale(float4{ 200.f, 100.f, 1.f, 1.f });
	float PreviousDirectionX = PreviousDirection().x;
	AttackCollision->GetTransform().SetLocalMove(float4{ -PreviousDirectionX * 40.f, 0.f, 0.f, 0.f });
	AttackCollision->ChangeOrder(OBJECTORDER::CharacterAttack);
	AttackCollision->Death(0.5f);
	mStateManager.ChangeState("Stand");
}

void Player::EndFinalAttack2()
{
	GameEngineCollision* AttackCollision = CreateComponent<GameEngineCollision>("AttackCollision");
	AttackCollision->GetTransform().SetLocalScale(float4{ 200.f, 100.f, 1.f, 1.f });
	float PreviousDirectionX = PreviousDirection().x;
	AttackCollision->GetTransform().SetLocalMove(float4{ -PreviousDirectionX * 40.f, 0.f, 0.f, 0.f });
	AttackCollision->ChangeOrder(OBJECTORDER::CharacterAttack);
	AttackCollision->Death(0.5f);
	mStateManager.ChangeState("Stand");
}

void Player::StandStart(const StateInfo& _Info)
{
	mpRenderer->ChangeFrameAnimation("CharacterStand");
}

void Player::StandUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// [D]Jump
	if (false == GameEngineInput::GetInst()->IsPress("PlayerDown") && true == GameEngineInput::GetInst()->IsDown("PlayerJump"))
	{
		GetTransform().SetWorldMove(GetTransform().GetUpVector() * 80.f);
		mStateManager.ChangeState("Jump");
		return;
	}

	if (false == mbOnGround)
	{
		mStateManager.ChangeState("Jump");
		return;
	}

	// [D]Walk
	if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft"))
	{
		mpRenderer->GetTransform().PixLocalPositiveX();
		mStateManager.ChangeState("Walk");
		return;
	}
	if (true == GameEngineInput::GetInst()->IsPress("PlayerRight"))
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

	// [S]Attack1
	if (true == GameEngineInput::GetInst()->IsPress("PlayerAttack1"))
	{
		mStateManager.ChangeState("Attack");
		mpRenderer->ChangeFrameAnimation("CharacterStab");
		// mpRenderer->CurAnimationReset();
		return;
	}
	// [S]Attack2
	if (true == GameEngineInput::GetInst()->IsPress("PlayerAttack2"))
	{
		mStateManager.ChangeState("Attack");
		mpRenderer->ChangeFrameAnimation("CharacterSwing");
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerDown") && true == GameEngineInput::GetInst()->IsDown("PlayerJump"))
	{
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * 30.f);
	}
}

void Player::WalkStart(const StateInfo& _Info)
{
	mpRenderer->ChangeFrameAnimation("CharacterWalk");
}

void Player::WalkUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// [D]Stand
	if (true == GameEngineInput::GetInst()->IsFree("PlayerLeft") &&
		true == GameEngineInput::GetInst()->IsFree("PlayerRight") &&
		true == GameEngineInput::GetInst()->IsFree("PlayerUp"))
	{
		mStateManager.ChangeState("Stand");
		return;
	}

	// [D]Jump
	if (true == GameEngineInput::GetInst()->IsDown("PlayerJump"))
	{
		if (0 <= PreviousDirection().x) { GetTransform().SetWorldMove(GetTransform().GetUpVector() * 40.f + GetTransform().GetLeftVector() * 40.f); }
		else { GetTransform().SetWorldMove(GetTransform().GetUpVector() * 40.f + GetTransform().GetRightVector() * 40.f); }
		mStateManager.ChangeState("Jump");

		return;
	}

	// [D]Alert
	if (true == mbHitted && false == mbInvincible)
	{
		mStateManager.ChangeState("Alert");
		return;
	}

	// [D]Attack1
	if (true == GameEngineInput::GetInst()->IsDown("PlayerAttack1"))
	{
		mpRenderer->ChangeFrameAnimation("CharacterStab");
		mStateManager.ChangeState("Attack");
		return;
	}
	// [D]Attack2
	if (true == GameEngineInput::GetInst()->IsDown("PlayerAttack2"))
	{
		mpRenderer->ChangeFrameAnimation("CharacterSwing");
		mStateManager.ChangeState("Attack");
		return;
	}
	
	// [D]Move (Recursive)
	if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft"))
	{
		mpRenderer->GetTransform().PixLocalPositiveX();
		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * mfSpeed * _DeltaTime);
		return;
	}
	if (true == GameEngineInput::GetInst()->IsPress("PlayerRight"))
	{
		mpRenderer->GetTransform().PixLocalNegativeX();
		GetTransform().SetWorldMove(GetTransform().GetRightVector() * mfSpeed * _DeltaTime);
		return;
	}
}

void Player::DeadStart(const StateInfo& _Info)
{
	mbInvincible = true;
	mfBeforeAccTimeForVincible = GetAccTime();
	mpRenderer->ChangeFrameAnimation("CharacterDead");
}

void Player::DeadUpdate(float _DeltaTime, const StateInfo& _Info)
{
	mbInvincible = true;
	if (1.f <= _Info.StateTime)
	{
		mfHP = 100.f;
		mStateManager.ChangeState("Stand");
		GEngine::ChangeLevel("LoginLevel");
	}
}

void Player::AttackStart(const StateInfo& _Info)
{
	mbInvincible = true;
	mfBeforeAccTimeForVincible = GetAccTime();

	float4 fPreviousScale = PreviousDirection();
	GameEngineCollision* AttackCollision = CreateComponent<GameEngineCollision>("AttackCollision");
	AttackCollision->GetTransform().SetLocalScale(float4{ 200.f, 100.f, 1.f, 1.f });
	float PreviousDirectionX = PreviousDirection().x;
	AttackCollision->GetTransform().SetLocalMove(float4{ -PreviousDirectionX * 40.f, 0.f, 0.f, 0.f });
	AttackCollision->ChangeOrder(OBJECTORDER::CharacterAttack);
	AttackCollision->Death(0.5f);

	mpRenderer->GetTransform().SetWorldScale(fPreviousScale * float4{ 140.f, 68.f, 1.f, 1.f });
	mpRenderer->ChangeFrameAnimation("CharacterStab");
}

void Player::JumpStart(const StateInfo& _Info)
{
	mpRenderer->ChangeFrameAnimation("CharacterJump");
}

void Player::JumpUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == mbOnGround)
	{
		mStateManager.ChangeState("Stand");
		return;
	}

	//// Stand
	//if (
	//	true == mf4PixelData.CompareInt4D(float4::CYAN) ||
	//	true == mf4PixelData.CompareInt4D(float4::MAGENTA) ||
	//	(true == mf4PixelData.CompareInt4D(float4::YELLOW) && 
	//	(mf4PixelDataOnLeftSide.CompareInt4D(float4::CYAN) || mf4PixelDataOnRightSide.CompareInt4D(float4::CYAN)))
	//	)
	//{
	//	mStateManager.ChangeState("Stand");
	//	return;
	//}

	// Alert
	if (true == mbHitted && false == mbInvincible)
	{
		mStateManager.ChangeState("Alert");
		
		
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerUp") &&
		true == mf4HeadPixelData.CompareInt4D(float4::YELLOW))
    {
		mbOnLadder = true;
		mStateManager.ChangeState("Ladder");
		return;
    }
}

void Player::LadderStart(const StateInfo& _Info)
{
	mpRenderer->ChangeFrameAnimation("CharacterLadderIdle");
}

void Player::LadderUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsPress("PlayerUp"))
	{
		GetTransform().SetWorldMove(GetTransform().GetUpVector() * 80.f * _DeltaTime);
		mpRenderer->ChangeFrameAnimation("CharacterLadderMove");

		if (true == mf4PixelDataOnLeftSide.CompareInt4D(float4::CYAN) ||
			true == mf4PixelDataOnRightSide.CompareInt4D(float4::CYAN))
		{
			mbOnLadder = false;
			mStateManager.ChangeState("Stand");
		}

		return;
	}
	if (true == GameEngineInput::GetInst()->IsPress("PlayerDown"))
	{
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * 80.f * _DeltaTime);
		mpRenderer->ChangeFrameAnimation("CharacterLadderMove");

		if (true == mf4PixelDataOnLeftSide.CompareInt4D(float4{ 1.f, 1.f, 1.f, 0.f }) &&
			true == mf4PixelDataOnRightSide.CompareInt4D(float4{ 1.f, 1.f, 1.f, 0.f })&&
			true == mf4PixelData.CompareInt4D(float4{ 1.f, 1.f, 1.f, 0.f }))
		{
			mbOnLadder = false;
			mStateManager.ChangeState("Stand");
		}

		return;
	}

	// Alert
	if (true == mbHitted && false == mbInvincible)
	{
		mStateManager.ChangeState("Alert");
		return;
	}

	mpRenderer->ChangeFrameAnimation("CharacterLadderIdle");
	
}

void Player::AlertStart(const StateInfo& _Info)
{
	mbInvincible = true;
	mfBeforeAccTimeForVincible = GetAccTime();
	mpRenderer->ChangeFrameAnimation("CharacterAlert");
}

void Player::AlertUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (GetHP() <= 0.f)
	{
		mStateManager.ChangeState("Dead");
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft"))
	{
		mpRenderer->GetTransform().PixLocalPositiveX();
		mStateManager.ChangeState("Walk");
		mbHitted = false;
		return;
	}
	if (true == GameEngineInput::GetInst()->IsPress("PlayerRight"))
	{
		mpRenderer->GetTransform().PixLocalNegativeX();
		mStateManager.ChangeState("Walk");
		mbHitted = false;
		return;
	}
}
