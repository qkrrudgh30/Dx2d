#include "PreCompile.h"
#include "MenuButton.h"
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
#include <GameEngineCore/GameEngineCamera.h>

#include "PopupMenu.h"

MenuButton::MenuButton() 
	: mpRenderer(nullptr)
	, mbToggle(false)
	, mpPopupMenu(nullptr)
{
}

MenuButton::~MenuButton() 
{
}

void MenuButton::Start()
{
	mpRenderer = CreateComponent<GameEngineTextureRenderer>();
	mfHeight = 35.f;
	mfWidth = GameEngineWindow::GetScale().x * 0.09125f;
	mpRenderer->GetTransform().SetWorldScale(float4{ GameEngineWindow::GetScale().x * 0.09125f, 35.f, 1.f, 1.f });
	mpRenderer->SetTexture("MenuButton.png", 0);

	mpPopupMenu = GetLevel()->CreateActor<PopupMenu>();
	mpPopupMenu->GetTransform().SetWorldPosition(float4{});
}

void MenuButton::Update(float _DeltaTime)
{
	mf4MousePos = GetLevel()->GetMainCamera()->GetMouseWorldPosition();
	if (mfPositionX - (mfWidth / 2) <= mf4MousePos.x && mf4MousePos.x <= mfPositionX + (mfWidth / 2)
		&& mfPositionY - (mfHeight / 2) <= mf4MousePos.y && mf4MousePos.y <= mfPositionY + (mfHeight / 2))
	{
		mpRenderer->SetFrame(1);
		if (true == GameEngineInput::GetInst()->IsDown("MouseLButtonDown"))
		{
			mpRenderer->SetFrame(2);
			mbToggle = !mbToggle;
			mpPopupMenu->SetVisible(mbToggle);
		}
	}
	else
	{
		mpRenderer->SetFrame(0);
	}

	GameEngineDebug::OutPutString(std::to_string(mf4MousePos.x) + "  " + std::to_string(mf4MousePos.y) + " " + std::to_string(mfPositionX) + " " + std::to_string(mfPositionY));
}
