#include "PreCompile.h"
#include "PopupMenu.h"
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
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCamera.h>

PopupMenu::PopupMenu() 
	: mbVisible(false)
{
}

PopupMenu::~PopupMenu() 
{
}

void PopupMenu::Start()
{
	mpRenderer = CreateComponent<GameEngineUIRenderer>();
	mpRenderer->SetTexture("PopupMenuBackGround.png", 0);
	mfWidth = GameEngineWindow::GetScale().x * 0.11625f;
	mfHeight = 167.f;
	mpRenderer->GetTransform().SetLocalScale(float4{ mfWidth, mfHeight, 1.f, 1.f });
	// mpRenderer->GetTransform().SetLocalPosition(float4{ 455.f, -GameEngineWindow::GetScale().y / 2.f + 130.f, OBJECTORDER::UIBackGround, 1.f });
}

void PopupMenu::Update(float _DeltaTime)
{
	if (false == mbVisible)
	{
		mpRenderer->GetTransform().SetWorldScale(float4{ 0.f, 0.f, 1.f, 1.f });
		return;
	}
	else
	{
		mpRenderer->GetTransform().SetWorldScale(float4{ mfWidth, mfHeight, 1.f, 1.f });
	}

	float4 mf4MousePos = GetLevel()->GetUICamera()->GetMouseWorldPosition();
	float4 mf4ButtonPos = mpRenderer->GetTransform().GetWorldPosition();
	if (mf4ButtonPos.x - (mfWidth / 2) <= mf4MousePos.x && mf4MousePos.x <= mf4ButtonPos.x + (mfWidth / 2)
		&& mf4ButtonPos.y - (mfHeight / 2) <= mf4MousePos.y && mf4MousePos.y <= mf4ButtonPos.y + (mfHeight / 2))
	{
		mpRenderer->SetFrame(1);
		if (true == GameEngineInput::GetInst()->IsDown("MouseLButtonDown"))
		{
			mpRenderer->SetFrame(2);
			DestroyWindow(GameEngineWindow::GetHWND());
		}
	}
	else
	{
		mpRenderer->SetFrame(0);
	}
	// GameEngineDebug::OutPutString(std::to_string(mpRenderer->GetTransform().GetLocalPosition().x) + "  " + std::to_string(mpRenderer->GetTransform().GetLocalPosition().y));
}
