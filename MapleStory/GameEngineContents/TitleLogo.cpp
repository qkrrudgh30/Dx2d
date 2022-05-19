#include "TitleLogo.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineRenderer.h>

TitleLogo::TitleLogo() 
{
}

TitleLogo::~TitleLogo() 
{
}

void TitleLogo::Start()
{
	CreateComponent<GameEngineRenderer>();
}

void TitleLogo::Update(float _DeltaTime)
{
}

void TitleLogo::End()
{
}

