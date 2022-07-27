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
	mpRenderer->SetTexture("PopupMenuBackGround.png");
	mfWidth = GameEngineWindow::GetScale().x * 0.11625f;
	mfHeight = 167.f;
	mpRenderer->GetTransform().SetLocalScale(float4{ mfWidth, mfHeight, 1.f, 1.f });
	mpRenderer->GetTransform().SetLocalPosition(float4{ 452.f, -GameEngineWindow::GetScale().y / 2.f + 35.f, OBJECTORDER::UIBackBoard, 1.f });
	// mpRenderer->GetTransform().SetLocalPosition(float4{ 452.f, -GameEngineWindow::GetScale().y / 2.f + 35.f, 1.f, 1.f });
}

void PopupMenu::Update(float _DeltaTime)
{
	if (false == mbVisible)
	{
		mpRenderer->GetTransform().SetWorldScale(float4{ 0.f, 0.f, 1.f, 1.f });
	}
	else
	{
		mpRenderer->GetTransform().SetWorldScale(float4{ mfWidth, mfHeight, 1.f, 1.f });
	}
	mf4CameraPos = GetLevel()->GetMainCameraActorTransform().GetLocalPosition();
	mpRenderer->GetTransform().SetWorldPosition(float4{ GameEngineWindow::GetScale().x * 0.09125f + mf4CameraPos.x + 350.f, mf4CameraPos.y - GameEngineWindow::GetScale().y / 2.f + 17.f + 100.f, 1.f, 1.f });
	// GameEngineDebug::OutPutString(std::to_string(mpRenderer->GetTransform().GetLocalPosition().x) + "  " + std::to_string(mpRenderer->GetTransform().GetLocalPosition().y));
}
