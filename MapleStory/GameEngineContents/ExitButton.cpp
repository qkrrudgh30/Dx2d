#include "PreCompile.h"
#include "ExitButton.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

ExitButton::ExitButton() 
	: mpRenderer(nullptr)
    , mfWidth(0)
    , mfHeight(0)
    , mfPositionX(0)
    , mfPositionY(0)
{
}

ExitButton::~ExitButton() 
{
}

void ExitButton::Start()
{
	GetTransform().SetWorldPosition(float4{ 0.f, 0.f, OBJECTORDER::UI, 1.f });

	mfWidth = 81 * 2;
	mfHeight = 34 * 2;
	mpRenderer = CreateComponent<GameEngineTextureRenderer>();
	mpRenderer->GetTransform().SetWorldScale(float4{ mfWidth, mfHeight, 1 });
    mfPositionX = -(GameEngineWindow::GetScale().x / 2.f) + (mfWidth / 2.f);
    mfPositionY = -(GameEngineWindow::GetScale().y / 2.f) + (mfHeight / 2.f) + 40.f;
    mpRenderer->GetTransform().SetWorldPosition({ mfPositionX, mfPositionY, 1});
	mpRenderer->SetTexture("ExitButton.png", 0);
}

void ExitButton::Update(float _DeltaTime)
{
	mf4MousePos = GetLevel()->GetMainCamera()->GetMouseWorldPosition();

	if (mfPositionX - (mfWidth / 2) <= mf4MousePos.x && mf4MousePos.x <= mfPositionX + (mfWidth / 2)
		&& mfPositionY - (mfHeight / 2) <= mf4MousePos.y && mf4MousePos.y <= mfPositionY + (mfHeight / 2))
	{
		mpRenderer->SetFrame(1);

		if (true == GameEngineInput::GetInst()->IsPress("MouseLButtonDown"))
		{
			mpRenderer->SetFrame(2);
			DestroyWindow(GameEngineWindow::GetHWND());
		}
	}
	else
	{
		mpRenderer->SetFrame(0);
	}
}

void ExitButton::End()
{
}
