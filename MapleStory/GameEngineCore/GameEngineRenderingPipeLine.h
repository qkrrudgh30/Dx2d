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
public:
    static GameEngineRenderingPipeLine* Create(const std::string& _Name);

public:
    // constrcuter destructer
    GameEngineRenderingPipeLine();
    ~GameEngineRenderingPipeLine();

    // delete Function
    GameEngineRenderingPipeLine(const GameEngineRenderingPipeLine& _Other) = delete;
    GameEngineRenderingPipeLine(GameEngineRenderingPipeLine&& _Other) noexcept = delete;
    GameEngineRenderingPipeLine& operator=(const GameEngineRenderingPipeLine& _Other) = delete;
    GameEngineRenderingPipeLine& operator=(GameEngineRenderingPipeLine&& _Other) noexcept = delete;

    void SetInputAssembler1VertexBuffer(const std::string& _Name);

    void SetVertexShader(const std::string& _Name);

    void SetInputAssembler2IndexBuffer(const std::string& _Name);

    void SetRasterizer(const std::string& _Name);

    void SetPixelShader(const std::string& _Name);

    void Rendering();

protected:

private:
    // 정점 입력 관련
    GameEngineVertexBuffer*  VertexBuffer; 
    GameEngineInputLayOut*   InputLayOut;

    // 정점 처리 관련
    GameEngineVertexShader*  VertexShader;    
    GameEngineIndexBuffer*   IndexBuffer; 
    D3D11_PRIMITIVE_TOPOLOGY Topology;
    GameEngineRasterizer*    Rasterizer;
    GameEnginePixelShader*   PixelShader;

    // 정점에 의해 건져진 픽셀 처리 관련
    void InputAssembler1VertexBufferSetting();

    void VertexShaderSetting();

    void InputAssembler2IndexBufferSetting();

    void RasterizerSetting();

    void PixelShaderSetting();

    void Draw();

};

