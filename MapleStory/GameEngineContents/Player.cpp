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
	{
		mpRenderer = CreateComponent<GameEngineTextureRenderer>();
		mpRenderer->GetTransform().SetLocalScale({ 83, 85, 1 });
		mpRenderer->SetTexture("CharacterAlert.png", 0);
		mpRenderer->CreateFrameAnimation("CharacterAlert", FrameAnimation_DESC("CharacterAlert.png", 0, 4, 0.5f));		
	}
}

void Player::Update(float _DeltaTime)
{
	mpRenderer->ChangeFrameAnimation("CharacterAlert");
	if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft"))
	{
		Color.r += 1.0f * _DeltaTime;

		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerRight"))
	{
		GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("PlayerUp"))
	{
		GetTransform().SetWorldMove(GetTransform().GetUpVector() * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("PlayerDown"))
	{
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerForward"))
	{
		GetTransform().SetWorldMove(GetTransform().GetForwardVector() * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("PlayerBack"))
	{
		GetTransform().SetWorldMove(GetTransform().GetBackVector() * Speed * _DeltaTime);
	}
}