// <hide/>

// GameEngineDefaultRenderer.cpp

#include "PreCompile.h"
#include "GameEngineDefaultRenderer.h"

GameEngineDefaultRenderer::GameEngineDefaultRenderer() 
    :PipeLine(nullptr)
{
}

GameEngineDefaultRenderer::~GameEngineDefaultRenderer() 
{
}

void GameEngineDefaultRenderer::Render(float _DeltaTime)
{
    GameEngineRenderer::Start(); // 사실 이 코드 외에 할일은 없긴 함.
}

void GameEngineDefaultRenderer::Start()
{
    // PipeLine->Draw(); 비슷한 코드가 작성될 예정. 
    // 하나의 개체가 랜더링되려면, 항상 Pipe line의 도움이 필요함.
}

