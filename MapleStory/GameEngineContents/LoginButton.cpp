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
{
}

LoginButton::~LoginButton() 
{
}

void LoginButton::Start()
{
	mfWidth = 278.f;
	mfHeight = 53.f;
	mpRenderer = CreateComponent<GameEngineTextureRenderer>();
	mpRenderer->GetTransform().SetLocalScale({ mfWidth, mfHeight, 1 });
	// mpRenderer->GetTransform().SetLocalScale({ 10, 10, 1 });
	
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
			// 알파블랜딩 추가하고 싶음.
			GEngine::ChangeLevel("TempleOfTime0");
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
