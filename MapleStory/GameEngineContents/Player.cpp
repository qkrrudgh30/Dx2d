#include "PreCompile.h"
#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>
#include <iostream>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineContents/GlobalContentsValue.h>
#include <GameEngineCore/GameEngineDefaultRenderer.h>
#include <GameEngineCore/GameEngineRenderingPipeLine.h>
#include <GameEngineCore/GameEngineVertexShader.h>
#include <GameEngineCore/GameEngineConstantBuffer.h>
#include <GameEngineCore/GameEngineDevice.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

Player::Player() 
	: Speed(300.0f)
{
}

Player::~Player() 
{
}

void Player::Start()
{
	GetTransform().SetWorldPosition(float4{0.f, 0.f, OBJECTORDER::Character, 1.f});
	{
		mpRenderer = CreateComponent<GameEngineTextureRenderer>();
		mpRenderer->GetTransform().SetLocalScale({ 83.f, 85.f, 1.f, 1.f });
		mpRenderer->CreateFrameAnimation("CharacterAlert", FrameAnimation_DESC("CharacterAlert.png", 0, 4, 0.5f));		
		mpRenderer->CreateFrameAnimation("CharacterStand", FrameAnimation_DESC("CharacterStand.png", 0, 4, 0.5f));		
		mpRenderer->CreateFrameAnimation("CharacterWalk", FrameAnimation_DESC("CharacterWalk.png", 0, 5, 0.2f));
		mpRenderer->CreateFrameAnimation("CharacterJump", FrameAnimation_DESC("CharacterJump.png", 0, 6, 0.5f));		
		mpRenderer->CreateFrameAnimationFolder("WarriorLeap", FrameAnimation_DESC("WarriorLeap", 0.1f));
	}	 
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
		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerRight"))
	{
		mpRenderer->GetTransform().PixLocalNegativeX();
		mpRenderer->ChangeFrameAnimation("CharacterWalk");
		GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("PlayerUp"))
	{
		mpRenderer->ChangeFrameAnimation("CharacterStand");
		GetTransform().SetWorldMove(GetTransform().GetUpVector() * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("PlayerDown"))
	{
		mpRenderer->ChangeFrameAnimation("CharacterStand");
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("PlayerJump"))
	{
		mpRenderer->ChangeFrameAnimation("CharacterJump");
	}
	if (true == GameEngineInput::GetInst()->IsPress("PlayerDoubleJump"))
	{
		mpRenderer->ChangeFrameAnimation("WarriorLeap");
	}
}

void Player::End()
{
}
