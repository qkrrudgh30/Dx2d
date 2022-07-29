#include "PreCompile.h"
#include "Button.h"

Button::Button() 
{
}

Button::~Button() 
{
}

void Button::Update(float _DeltaTime)
{
	GetCursorPos(&mptMousePos);
	ScreenToClient(GameEngineWindow::GetHWND(), &mptMousePos);
	mf4MousePos = GetLevel()->GetMainCamera()->GetMouseWorldPositionToActor();
	if (mfPositionX - (mfWidth / 2) <= mf4MousePos.x && mf4MousePos.x <= mfPositionX + (mfWidth / 2)
		&& mfPositionY - (mfHeight / 2) <= mf4MousePos.y && mf4MousePos.y <= mfPositionY + (mfHeight / 2))
	{
		mpRenderer->SetFrame(1);
		if (true == GameEngineInput::GetInst()->IsPress("MouseLButtonDown"))
		{
			mpRenderer->SetFrame(2);
		}
	}
	else
	{
		mpRenderer->SetFrame(0);
	}
}

