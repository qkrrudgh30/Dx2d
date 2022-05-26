// <hide/>

// GameEngineActor.cpp

#include "GameEngineActor.h"
#include "GameEngineComponent.h"

GameEngineActor::GameEngineActor() 
{
}

GameEngineActor::~GameEngineActor() 
{
    for (GameEngineComponent* Com : AllComList)
    {
        delete Com;
    }
}

void GameEngineActor::ComponentUpdate(float _ScaleDeltaTime, float _DeltaTime)
{
    for (GameEngineComponent* Com : AllComList)
    {
        Com->AddAccTime(_DeltaTime);
        Com->Update(_ScaleDeltaTime);
    }
}

