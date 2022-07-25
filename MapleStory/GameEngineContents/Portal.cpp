#include "PreCompile.h"
#include "Portal.h"
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

Portal::Portal()
	: mpRenderer(nullptr)
	, mfWidth(0)
	, mfHeight(0)
{
}

Portal::~Portal()
{
}

void Portal::Start()
{
	mfWidth = 89.f;
	mfHeight = 257.f;

	mpRenderer = CreateComponent<GameEngineTextureRenderer>();
	mpRenderer->GetTransform().SetWorldScale({ mfWidth, mfHeight, 1 });
	mpRenderer->CreateFrameAnimation("Portal", FrameAnimation_DESC("Portal.png", 0, 7, 0.1f));
	mpRenderer->ChangeFrameAnimation("Portal");
}

void Portal::Update(float _DeltaTime)
{
    
}

void Portal::End()
{
}
