#include "PreCompile.h"
#include "Temple3Boss.h"
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

Temple3Boss::Temple3Boss()
{
}

Temple3Boss::~Temple3Boss()
{
}

void Temple3Boss::Start()
{
	mpRenderer = CreateComponent<GameEngineTextureRenderer>();
	mpRenderer->GetTransform().SetWorldScale({ 264, 188, 1 });

	mpRenderer->CreateFrameAnimation("Temple3BossStand", FrameAnimation_DESC("Temple3BossStand.png", 0, 7, 0.2f));
	mpRenderer->CreateFrameAnimation("Temple3BossMove", FrameAnimation_DESC("Temple3BossMove.png", 0, 5, 0.5f));
	mpRenderer->CreateFrameAnimation("Temple3BossHitting1", FrameAnimation_DESC("Temple3BossHitting1.png", 0, 3, 0.5f));
	mpRenderer->CreateFrameAnimation("Temple3BossHitting2", FrameAnimation_DESC("Temple3BossHitting2.png", 0, 6, 0.5f));
	mpRenderer->CreateFrameAnimation("Temple3BossDie", FrameAnimation_DESC("Temple3BossDie.png", 0, 11, 0.5f));
	mpRenderer->CreateFrameAnimation("Temple3BossAttack1", FrameAnimation_DESC("Temple3BossAttack1.png", 0, 16, 0.5f));
	mpRenderer->CreateFrameAnimation("Temple3BossAttack2", FrameAnimation_DESC("Temple3BossAttack2.png", 0, 16, 0.5f));
	mpRenderer->CreateFrameAnimation("Temple3BossHitted", FrameAnimation_DESC("Temple3BossHitted.png", 0, 0, 0.2f));
}

void Temple3Boss::Update(float _DeltaTime)
{
	mpRenderer->ChangeFrameAnimation("Temple3BossStand");
}

void Temple3Boss::End()
{
}
