#include "PreCompile.h"
#include "LoginButton.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

LoginButton::LoginButton() 
	: mpRenderer(nullptr)
	, mfWidth(0)
	, mfHeight(0)
	, mfPositionX(0)
	, mfPositionY(0)
	, mbClicked(false)
{
}

LoginButton::~LoginButton() 
{
}

void LoginButton::Start()
{
	GetTransform().SetWorldPosition(float4{ 0.f, 0.f, OBJECTORDER::UI, 1.f });
	mfWidth = 278.f;
	mfHeight = 53.f;
	mpRenderer = CreateComponent<GameEngineTextureRenderer>();
	mpRenderer->GetTransform().SetWorldScale({ mfWidth, mfHeight, 1 });
	// mpRenderer->SetFolderTextureToIndex("LoginButton.png", 0);
	mpRenderer->SetTexture("LoginButton.png", 0);
}

void LoginButton::Update(float _DeltaTime)
{
	mf4MousePos = ContentsCore::GetMousePos();
	if (mfPositionX - (mfWidth / 2) <= mf4MousePos.x && mf4MousePos.x <= mfPositionX + (mfWidth / 2)
	 && mfPositionY - (mfHeight / 2) <= mf4MousePos.y && mf4MousePos.y <= mfPositionY + (mfHeight / 2))
	{
		mpRenderer->SetFrame(1);

		if (true == GameEngineInput::GetInst()->IsPress("MouseLButtonDown"))
		{
			mpRenderer->SetFrame(2);
			mbClicked = true;
		}
	}
	else
	{
		mpRenderer->SetFrame(0);
	}
}

void LoginButton::End()
{
}
