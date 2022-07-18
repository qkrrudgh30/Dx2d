#include "PreCompile.h"
#include "TempleOfTime3.h"

TempleOfTime3::TempleOfTime3() 
{
}

TempleOfTime3::~TempleOfTime3() 
{
}

void TempleOfTime3::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("CamLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("CamLeft", VK_DELETE);
		GameEngineInput::GetInst()->CreateKey("CamRight", VK_NEXT);
		GameEngineInput::GetInst()->CreateKey("CamUp", VK_HOME);
		GameEngineInput::GetInst()->CreateKey("CamDown", VK_END);
	}
}

void TempleOfTime3::Update(float _DeltaTime)
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

void TempleOfTime3::End()
{
}
