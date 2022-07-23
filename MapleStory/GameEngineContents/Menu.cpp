#include "PreCompile.h"
#include "Menu.h"
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

Menu::Menu() 
	: mpRenderer(nullptr)
	, mbToggle(false)
{
}

Menu::~Menu() 
{
}

void Menu::Start()
{
	mpRenderer = CreateComponent<GameEngineTextureRenderer>();
	mpRenderer->SetTexture("MenuButton.png");
	mfHeight = 35.f;
	mfWidth = GameEngineWindow::GetScale().x * 0.09125f;
	mpRenderer->GetTransform().SetWorldScale(float4{ GameEngineWindow::GetScale().x * 0.09125f, 35.f, 1.f, 1.f });
	mpRenderer->SetFrame(0);

	mpPopupMenu = GetLevel()->CreateActor<PopupMenu>();
}

void Menu::Update(float _DeltaTime)
{
	mf4MousePos = GetLevel()->GetMainCamera()->GetMouseWorldPositionToActor();
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

	// GameEngineDebug::OutPutString(std::to_string(mf4MousePos.x) + "  " + std::to_string(mf4MousePos.y) + " " + std::to_string(mfPositionX) + " " + std::to_string(mfPositionY));
}
