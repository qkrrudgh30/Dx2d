// <hide/>

// GameEngineRenderer.h

#pragma once
#include "GameEngineTransformComponent.h"

// 설명 :
class GameEngineRenderer : public GameEngineTransformComponent
{
    friend class GameEngineCamera;

public:
    // constrcuter destructer
    GameEngineRenderer();
    ~GameEngineRenderer();

    // delete Function
    GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
    GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
    GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
    GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

    // float4x4 ViewPort; 뷰포트는 Rasterizer 단계에서 할 예정.

protected:
    virtual void Start();
    virtual void Update(float _DeltaTime) {}
    virtual void End() {}

private:
    virtual void Render(float _DeltaTime) = 0; // 이제 GameEngineRenderer 클래스는 랜더러 관련 최상위 부모 클래스 역할.

};

