#include "PreCompile.h"
#include "NPC.h"
#include "Player.h"
#include "GlobalContentsValue.h"
#include "ContentsLevel.h"

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineFontRenderer.h>

NPC::NPC() 
	: mpPlayer(nullptr)
	, mbStoreOn(false)
{
	mfWidth = 86.f;
	mfHeight = 93.f;
}

NPC::~NPC() 
{
}

void NPC::Start()
{
	mpRenderer = CreateComponent<GameEngineTextureRenderer>();
	mpRenderer->SetTexture("JohannaStand.png");
	mpRenderer->GetTransform().SetLocalScale(float4{ mfWidth, mfHeight, 1.f, 1.f });
	mpRenderer->SetPivot(PIVOTMODE::BOT);

	mpRenderer->CreateFrameAnimationCutTexture("JohannaStand", FrameAnimation_DESC("JohannaStand.png", 0, 0, 2.f));
	mpRenderer->AnimationBindEnd("JohannaStand", std::bind(&NPC::EndStand, this, std::placeholders::_1));
	mpRenderer->CreateFrameAnimationCutTexture("JohannaSay", FrameAnimation_DESC("JohannaSay.png", 0, 11, 0.5f));
	mpRenderer->AnimationBindEnd("JohannaSay", std::bind(&NPC::EndSay, this, std::placeholders::_1));
	mpRenderer->CreateFrameAnimationCutTexture("JohannaEye", FrameAnimation_DESC("JohannaEye.png", 0, 6, 0.2f));
	mpRenderer->AnimationBindEnd("JohannaEye", std::bind(&NPC::EndEye, this, std::placeholders::_1));
	mpRenderer->ChangeFrameAnimation("JohannaStand");
}

void NPC::Update(float _DeltaTime)
{
	if (nullptr == mpPlayer)
	{
		mpPlayer = Player::GetPlayer();
		return;
	}

	float4 f4MousePosition = GetLevel()->GetUICamera()->GetMouseWorldPosition() + float4{ GameEngineWindow::GetScale().x / 2.f, -GameEngineWindow::GetScale().y / 2.f, 0.f, 0.f };
	float4 f4NPCPosition = GetTransform().GetWorldPosition();

	if (f4NPCPosition.x - 280.f <= f4MousePosition.x && f4MousePosition.x <= f4NPCPosition.x - 200.f
	    && f4NPCPosition.y + mfHeight / 2.f <= f4MousePosition.y && f4MousePosition.y <= f4NPCPosition.y + mfHeight * 3 / 2.f
		)
	{
		if (false == mbStoreOn && true == GameEngineInput::GetInst()->IsUp("MouseLButtonDown"))
		{
			int a = 100;
			mbStoreOn = true;
		}
	}
}

void NPC::End()
{
}

void NPC::EndStand(const FrameAnimation_DESC& _Info)
{
	int random = GameEngineRandom::MainRandom.RandomInt(0, 2);

	switch (random)
	{
	case 0:
		mpRenderer->ChangeFrameAnimation("JohannaStand");
		break;
	case 1:
		mpRenderer->ChangeFrameAnimation("JohannaSay");
		break;
	case 2:
		mpRenderer->ChangeFrameAnimation("JohannaEye");
		break;

	default:
		break;
	}
}

void NPC::EndSay(const FrameAnimation_DESC& _Info)
{
	int random = GameEngineRandom::MainRandom.RandomInt(0, 2);

	switch (random)
	{
	case 0:
		mpRenderer->ChangeFrameAnimation("JohannaStand");
		break;
	case 1:
		mpRenderer->ChangeFrameAnimation("JohannaSay");
		break;
	case 2:
		mpRenderer->ChangeFrameAnimation("JohannaEye");
		break;

	default:
		break;
	}
}

void NPC::EndEye(const FrameAnimation_DESC& _Info)
{
	int random = GameEngineRandom::MainRandom.RandomInt(0, 2);

	switch (random)
	{
	case 0:
		mpRenderer->ChangeFrameAnimation("JohannaStand");
		break;
	case 1:
		mpRenderer->ChangeFrameAnimation("JohannaSay");
		break;
	case 2:
		mpRenderer->ChangeFrameAnimation("JohannaEye");
		break;

	default:
		break;
	}
}
