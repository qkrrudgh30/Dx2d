// <hide/>

// GameEngineRenderingPipeLine.h

#pragma once

#include "GameEngineRes.h"

// 설명 :
class GameEngineVertexBuffer;
class GameEngineInputLayOut;
class GameEngineVertexShader;
class GameEngineIndexBuffer;
class GameEngineRasterizer;
class GameEnginePixelShader;
class GameEngineRenderingPipeLine : public GameEngineRes<GameEngineRenderingPipeLine>
{
private:
    // 정점 입력 관련
    GameEngineVertexBuffer* VertexBuffer;
    GameEngineInputLayOut*  InputLayOut;

    // 정점 처리 관련
    GameEngineVertexShader*  VertexShader;
    GameEngineIndexBuffer*   IndexBuffer;
    D3D11_PRIMITIVE_TOPOLOGY Topology;

    // 정점에 의해 건져진 픽셀 처리 관련
    GameEngineRasterizer*    Rasterizer;
    GameEnginePixelShader*   PixelShader;

public:
    // constrcuter destructer
    GameEngineRenderingPipeLine();
    ~GameEngineRenderingPipeLine();

    // delete Function
    GameEngineRenderingPipeLine(const GameEngineRenderingPipeLine& _Other) = delete;
    GameEngineRenderingPipeLine(GameEngineRenderingPipeLine&& _Other) noexcept = delete;
    GameEngineRenderingPipeLine& operator=(const GameEngineRenderingPipeLine& _Other) = delete;
    GameEngineRenderingPipeLine& operator=(GameEngineRenderingPipeLine&& _Other) noexcept = delete;

    static GameEngineRenderingPipeLine* Create(const std::string& _Name);

    // 랜더링 파이프라인 개체에 리소스들을 저장하는 함수.
    void SetInputAssembler1VertexBuffer(const std::string& _Name);

    void SetVertexShader(const std::string& _Name);

    void SetInputAssembler2IndexBuffer(const std::string& _Name);

    void SetRasterizer(const std::string& _Name);

    void SetPixelShader(const std::string& _Name);

    // 그래픽 카드에 꽂힌 리소스들을 이용해서 그리는 함수.
    void Rendering();

private:
    // 랜더링 파이프라인에 저장된 리소스들을 그래픽 카드에 꽂는 함수.(즉, 이 함수가 호출된 뒤로 실효)
    void InputAssembler1VertexBufferSetting();

    void VertexShaderSetting();

    void InputAssembler2IndexBufferSetting();

    void RasterizerSetting();

    void PixelShaderSetting();

    void Draw();

};

