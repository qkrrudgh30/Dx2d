// <hide/>

// GameEngineRenderingPipeLine.cpp

#include "PreCompile.h"
#include "GameEngineRenderingPipeLine.h"

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine() 
{
}

GameEngineRenderingPipeLine::~GameEngineRenderingPipeLine() 
{
}

GameEngineRenderingPipeLine* GameEngineRenderingPipeLine::Create(const std::string& _Name)
{
    return CreateResName(_Name);
}

void GameEngineRenderingPipeLine::Draw()
{
}
