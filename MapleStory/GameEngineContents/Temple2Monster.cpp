#include "PreCompile.h"
#include "Temple2Monster.h"
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

Temple2Monster::Temple2Monster() 
{
}

Temple2Monster::~Temple2Monster() 
{
}

void Temple2Monster::Start()
{
	mpRenderer = CreateComponent<GameEngineTextureRenderer>();
	mpRenderer->GetTransform().SetWorldScale({ 115, 183, 1 });
	mpRenderer->GetTransform().SetWorldPosition(float4{ 1982.f/2.f, -846.f/2.f, OBJECTORDER::Mob, 1.f});
	mpRenderer->CreateFrameAnimation("Temple2MonsterStand", FrameAnimation_DESC("Temple2MonsterStand.png", 0, 11, 0.2f));
	mpRenderer->CreateFrameAnimation("Temple2MonsterMove", FrameAnimation_DESC("Temple2MonsterMove.png", 0, 5, 0.5f));
	mpRenderer->CreateFrameAnimation("Temple2MonsterHitting1", FrameAnimation_DESC("Temple2MonsterHitting1.png", 0, 3, 0.5f));
	mpRenderer->CreateFrameAnimation("Temple2MonsterHitting2", FrameAnimation_DESC("Temple2MonsterHitting2.png", 0, 6, 0.5f));
	mpRenderer->CreateFrameAnimation("Temple2MonsterDie", FrameAnimation_DESC("Temple2MonsterDie.png", 0, 11, 0.5f));
	mpRenderer->CreateFrameAnimation("Temple2MonsterAttack1", FrameAnimation_DESC("Temple2MonsterAttack1.png", 0, 16, 0.5f));
	mpRenderer->CreateFrameAnimation("Temple2MonsterAttack2", FrameAnimation_DESC("Temple2MonsterAttack2.png", 0, 16, 0.5f));
	mpRenderer->CreateFrameAnimation("Temple2MonsterHitted", FrameAnimation_DESC("Temple2MonsterHitted.png", 0, 0, 0.2f));
}

void Temple2Monster::Update(float _DeltaTime)
{
	mpRenderer->ChangeFrameAnimation("Temple2MonsterStand");
}

void Temple2Monster::End()
{
}
