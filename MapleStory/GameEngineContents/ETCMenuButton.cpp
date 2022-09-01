#include "PreCompile.h"
#include "ETCMenuButton.h"
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

ETCMenuButton::ETCMenuButton()
	: mpRenderer(nullptr)
	, mbToggle(false)
{
}

ETCMenuButton::~ETCMenuButton()
{
}

void ETCMenuButton::Start()
{
	mpRenderer = CreateComponent<GameEngineUIRenderer>();
	mpRenderer->GetTransform().SetLocalScale(float4{ 22.f, 18.f, 1.f, 1.f });

	mpRenderer->SetTexture("ETCMenu.png", 0);
}

void ETCMenuButton::Update(float _DeltaTime)
{
	mf4MousePos = GetLevel()->GetUICamera()->GetMouseWorldPosition();
	mf4ButtonPos = mpRenderer->GetTransform().GetWorldPosition();
	if (mf4ButtonPos.x - (mfWidth / 2) <= mf4MousePos.x && mf4MousePos.x <= mf4ButtonPos.x + (mfWidth / 2)
		&& mf4ButtonPos.y - (mfHeight / 2) <= mf4MousePos.y && mf4MousePos.y <= mf4ButtonPos.y + (mfHeight / 2))
	{
		if (true == GameEngineInput::GetInst()->IsDown("MouseLButtonDown"))
		{
			mpRenderer->SetFrame(1);
		}
	}
	else
	{
		mpRenderer->SetFrame(0);
	}
}
