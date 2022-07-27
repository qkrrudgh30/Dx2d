#include "PreCompile.h"
#include "Player.h"
#include "GlobalContentsValue.h"
#include "ContentsLevel.h"
#include "PixelCollisionMap.h"
#include "RigidBody.h"

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

Player::Player() 
{
	mfSpeed = 400.f;
}

Player::~Player() 
{
}

void Player::Start()
{
	GetTransform().SetWorldPosition(float4{0.f, 0.f, OBJECTORDER::Character, 1.f});
	mpRenderer = CreateComponent<GameEngineTextureRenderer>();
	mpRenderer->GetTransform().SetWorldPosition(float4{ 0.f, 0.f, OBJECTORDER::Character, 1.f });
	mfWidth = 83.f;
	mfHeight = 85.f;
	mpRenderer->GetTransform().SetLocalScale({ mfWidth, mfHeight, 1.f, 1.f });
	mpRenderer->CreateFrameAnimation("CharacterAlert", FrameAnimation_DESC("CharacterAlert.png", 0, 4, 0.5f));		
	mpRenderer->CreateFrameAnimation("CharacterJump", FrameAnimation_DESC("CharacterJump.png", 0, 0, 0.5f));
	mpRenderer->CreateFrameAnimation("CharacterLadder", FrameAnimation_DESC("CharacterLadder.png", 0, 1, 0.5f));
	mpRenderer->CreateFrameAnimation("CharacterStab", FrameAnimation_DESC("CharacterStab.png", 0, 2, 0.5f));
	mpRenderer->CreateFrameAnimation("CharacterStabF", FrameAnimation_DESC("CharacterStabF.png", 0, 3, 0.5f));
	mpRenderer->CreateFrameAnimation("CharacterStand", FrameAnimation_DESC("CharacterStand.png", 0, 4, 0.5f));		
	mpRenderer->CreateFrameAnimation("CharacterSwing", FrameAnimation_DESC("CharacterSwing.png", 0, 2, 0.5f));		
	mpRenderer->CreateFrameAnimation("CharacterSwingF", FrameAnimation_DESC("CharacterSwingF.png", 0, 3, 0.5f));		
	mpRenderer->CreateFrameAnimation("CharacterWalk", FrameAnimation_DESC("CharacterWalk.png", 0, 5, 0.2f));
	mpRenderer->CreateFrameAnimation("CharacterDead", FrameAnimation_DESC("CharacterDead.png", 0, 0, 0.2f));
	mpRenderer->CreateFrameAnimationFolder("WarriorLeap", FrameAnimation_DESC("WarriorLeap", 0.1f));
	mpRenderer->SetPivot(PIVOTMODE::BOT);

	mpParentLevel = GetLevel<ContentsLevel>();

	SetGround(false);
	RigidBody* rigid = CreateComponent<RigidBody>();

	StateManager.CreateStateMember("Idle", this, &Player::IdleUpdate, &Player::IdleStart, &Player::IdleEnd);
	StateManager.CreateStateMember("Move", this, &Player::MoveUpdate, &Player::MoveStart, &Player::MoveEnd);
	StateManager.CreateStateMember("Dead", this, &Player::DeadUpdate, &Player::DeadStart, &Player::DeadEnd);
	StateManager.CreateStateMember("Attack1", this, &Player::Attack1Update, &Player::Attack1Start, &Player::Attack1End);
	StateManager.CreateStateMember("Attack2", this, &Player::Attack2Update, &Player::Attack2Start, &Player::Attack2End);
	StateManager.CreateStateMember("Alert", this, &Player::AlertUpdate, &Player::AlertStart, &Player::AlertEnd);
	StateManager.CreateStateMember("Jump", this, &Player::JumpUpdate, &Player::JumpStart, &Player::JumpEnd);
	StateManager.CreateStateMember("Ladder", this, &Player::LadderUpdate, &Player::LadderStart, &Player::LadderEnd);
	StateManager.CreateStateMember("FinalAttack1", this, &Player::FinalAttack1Update, &Player::FinalAttack1Start, &Player::FinalAttack1End);
	StateManager.CreateStateMember("FinalAttack2", this, &Player::FinalAttack2Update, &Player::FinalAttack2Start, &Player::FinalAttack2End);
}

void Player::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsFree("PlayerLeft") && true == GameEngineInput::GetInst()->IsFree("PlayerRight"))
	{
		mpRenderer->ChangeFrameAnimation("CharacterStand");
	}
	
	if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft"))
	{
		mpRenderer->GetTransform().PixLocalPositiveX();
		mpRenderer->ChangeFrameAnimation("CharacterWalk");
		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * mfSpeed * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerRight"))
	{
		mpRenderer->GetTransform().PixLocalNegativeX();
		mpRenderer->ChangeFrameAnimation("CharacterWalk");
		GetTransform().SetWorldMove(GetTransform().GetRightVector() * mfSpeed * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("PlayerJump"))
	{
		mpRenderer->ChangeFrameAnimation("CharacterJump");
		GetTransform().SetWorldMove(GetTransform().GetUpVector() * mfSpeed * 1.5f * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("PlayerDoubleJump"))
	{
		mpRenderer->ChangeFrameAnimation("WarriorLeap");
	}

	mf4PixelData = mpParentLevel->GetPCMap()->GetRenderer()->GetCurTexture()->GetPixel(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y + 5));

	if (1.f <= mf4PixelData.a) 
	{ 
		mbOnGround = true;
	}
	else
	{ 
		mpRenderer->ChangeFrameAnimation("CharacterJump");
		mbOnGround = false;
	}

}

void Player::End()
{
}

void Player::IdleStart(const StateInfo& _Info)
{
	mpRenderer->ChangeFrameAnimation("CharacterStand");
}

void Player::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// [D]Jump
	// [D]Move
	// [D]Alert
	// [S]Attack1
	// [S]Attack2
}

void Player::MoveStart(const StateInfo& _Info)
{
	mpRenderer->ChangeFrameAnimation("CharacterWalk");
}

void Player::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// [D]Idle
	// [D]Jump
	// [D]Alert
	// [D]Attack1
	// [D]Attack2
}

void Player::DeadStart(const StateInfo& _Info)
{
	mpRenderer->ChangeFrameAnimation("CharacterDead");
	// Start falling tomb effect.
}

void Player::DeadUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// Wait 10 Seconds.
}

void Player::DeadEnd(const StateInfo& _Info)
{
	// Go to login level.
}

void Player::Attack1Start(const StateInfo& _Info)
{
	mpRenderer->ChangeFrameAnimation("CharacterStab");
}

void Player::Attack1Update(float _DeltaTime, const StateInfo& _Info)
{
	// [D]Move
	// [D]Alert
	// [S]FinalAttack1
}

void Player::Attack2Start(const StateInfo& _Info)
{
	mpRenderer->ChangeFrameAnimation("CharacterSwing");
}

void Player::Attack2Update(float _DeltaTime, const StateInfo& _Info)
{
	// [D]Move
	// [D]Alert
	// [S]FinalAttack2
}

void Player::AlertStart(const StateInfo& _Info)
{
	mpRenderer->ChangeFrameAnimation("CharacterAlert");
}

void Player::AlertUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// [D]Idle
	// [D]Jump
	// [D]Move
	// [D]Attack1
	// [D]Attack2
	// [S]Dead
}

void Player::JumpStart(const StateInfo& _Info)
{
	mpRenderer->ChangeFrameAnimation("CharacterJump");
}

void Player::JumpUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// [D]Idle
	// [D]Move
	// [D]Alert
	// [D]Ladder
}

void Player::LadderStart(const StateInfo& _Info)
{
	mpRenderer->ChangeFrameAnimation("CharacterLadder");
}

void Player::LadderUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// [D]Jump
	// [D]Idle
	// [D]Alert
}

void Player::FinalAttack1Start(const StateInfo& _Info)
{
	mpRenderer->ChangeFrameAnimation("CharacterStabF");
}

void Player::FinalAttack1Update(float _DeltaTime, const StateInfo& _Info)
{
	// [S]Idle
	// [S]Alert
}

void Player::FinalAttack2Start(const StateInfo& _Info)
{
	mpRenderer->ChangeFrameAnimation("CharacterSwingF");
}

void Player::FinalAttack2Update(float _DeltaTime, const StateInfo& _Info)
{
	// [S]Idle
	// [S]Alert
}
