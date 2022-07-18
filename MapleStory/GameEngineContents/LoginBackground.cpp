#include "PreCompile.h"
#include "LoginBackground.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>


LoginBackground::LoginBackground() 
	: mpRenderer(nullptr)
	, mfWidth(0)
	, mfHeight(0)
	, mfPositionX(0)
	, mfPositionY(0)
{
}

LoginBackground::~LoginBackground() 
{
}

void LoginBackground::Start()
{
	mfWidth = GameEngineWindow::GetScale().x;
	mfHeight = GameEngineWindow::GetScale().y;

	mpRenderer = CreateComponent<GameEngineTextureRenderer>();
	mpRenderer->GetTransform().SetLocalScale({ mfWidth, mfHeight, 1});
	mpRenderer->SetTexture("LoginBackground.png", 0);
}

void LoginBackground::Update(float _DeltaTime)
{
}

void LoginBackground::End()
{
}
