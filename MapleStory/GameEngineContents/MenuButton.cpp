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
#include <GameEngineCore/GameEngineUIRenderer.h>
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
	mpRenderer = CreateComponent<GameEngineUIRenderer>();
	mfHeight = 35.f;
	mfWidth = GameEngineWindow::GetScale().x * 0.09125f;
	mpRenderer->GetTransform().SetLocalScale(float4{ GameEngineWindow::GetScale().x * 0.09125f, 35.f, 1.f, 1.f });
	mpRenderer->GetTransform().SetLocalPosition(float4{ 462.f, -GameEngineWindow::GetScale().y / 2.f + 17.f, OBJECTORDER::UIBackGround, 1.f });

	mpRenderer->SetTexture("MenuButton.png", 0);

	mpPopupMenu = GetLevel()->CreateActor<PopupMenu>();
	mpPopupMenu->GetTransform().SetLocalPosition(float4{ 455.f, -GameEngineWindow::GetScale().y / 2.f + 130.f, OBJECTORDER::UIBackGround, 1.f });
}

void MenuButton::Update(float _DeltaTime)
{
	mf4MousePos = GetLevel()->GetUICamera()->GetMouseWorldPosition();
	mf4ButtonPos = mpRenderer->GetTransform().GetWorldPosition();
	if (mf4ButtonPos.x - (mfWidth / 2) <= mf4MousePos.x && mf4MousePos.x <= mf4ButtonPos.x + (mfWidth / 2)
		&& mf4ButtonPos.y - (mfHeight / 2) <= mf4MousePos.y && mf4MousePos.y <= mf4ButtonPos.y + (mfHeight / 2))
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
}
