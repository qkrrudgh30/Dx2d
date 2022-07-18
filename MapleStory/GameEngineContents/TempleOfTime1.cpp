#include "PreCompile.h"
#include "TempleOfTime1.h"

#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineWindow.h>

TempleOfTime1::TempleOfTime1() 
{
}

TempleOfTime1::~TempleOfTime1() 
{
}

void TempleOfTime1::Start()
{
	mpCamera = CreateActor<GameEngineCameraActor>();
	mpCamera->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
	mpCamera->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -500.0f });

	if (false == GameEngineInput::GetInst()->IsKey("CamLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("CamLeft", VK_DELETE);
		GameEngineInput::GetInst()->CreateKey("CamRight", VK_NEXT);
		GameEngineInput::GetInst()->CreateKey("CamUp", VK_HOME);
		GameEngineInput::GetInst()->CreateKey("CamDown", VK_END);
	}
}

void TempleOfTime1::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsPress("CamLeft"))
	{
		GetMainCameraActorTransform().SetLocalMove(-GetMainCameraActorTransform().GetRightVector() * 100 * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("CamRight"))
	{
		GetMainCameraActorTransform().SetLocalMove(GetMainCameraActorTransform().GetRightVector() * 100 * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("CamUp"))
	{
		GetMainCameraActorTransform().SetLocalMove(GetMainCameraActorTransform().GetUpVector() * 100 * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("CamDown"))
	{
		GetMainCameraActorTransform().SetLocalMove(-GetMainCameraActorTransform().GetUpVector() * 100 * _DeltaTime);
	}

	LimitCameraMoving();
}

void TempleOfTime1::End()
{
}
