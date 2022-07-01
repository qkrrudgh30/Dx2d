// <hide/>

// GameEngineRenderer.cpp

#include "PreCompile.h"
#include "GameEngineRenderer.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineWindow.h>

#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"

GameEngineRenderer::GameEngineRenderer() 
{
}

GameEngineRenderer::~GameEngineRenderer() 
{
}

void GameEngineRenderer::Start() 
{
    GetActor()->GetLevel()->PushRenderer(this);
}
