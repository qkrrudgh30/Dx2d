// <hide/>

// GameEngineCore_Resources.cpp

#include "PreCompile.h"
#include "GameEngineCore.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include "GameEngineLevel.h"
#include <math.h>

// Resources Header
#include "GameEngineVertexs.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineConstantBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineRasterizer.h"
#include "GameEnginePixelShader.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineTexture.h"
#include "GameEngineRenderTarget.h"

void EngineInputLayOut()
{
    GameEngineVertex::LayOut.AddInputLayOut("POSITION", DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT);
    GameEngineVertex::LayOut.AddInputLayOut("COLOR", DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT);
}

void EngineRasterizer()
{
    D3D11_RASTERIZER_DESC Desc = {};

    Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
    Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;

    GameEngineRasterizer::Create("EngineRasterizer", Desc);
}

void EngineMesh()
{
    {
        std::vector<GameEngineVertex> Vertex; // 더이상 float4가 아님.
        Vertex.push_back({ float4(-0.5f, 0.5f), float4() });
        Vertex.push_back({ float4(0.5f, 0.5f), float4() });
        // Vertex.push_back({ float4(0.5f, 0.5f), float4(1.0f, 0.0f, 0.0f, 1.0f) }); 우상단 Red 정점 설정
        Vertex.push_back({ float4(0.5f, -0.5f), float4() });
        Vertex.push_back({ float4(-0.5f, -0.5f), float4() });
        GameEngineVertexBuffer::Create("Rect", Vertex);
    }

    {
        std::vector<int> Index;

        Index.resize(6);

        Index[0] = 0;
        Index[1] = 1;
        Index[2] = 2;

        Index[3] = 0;
        Index[4] = 2;
        Index[5] = 3;

        GameEngineIndexBuffer::Create("Rect", Index);
    }

    {
        std::vector<GameEngineVertex> Vertex;
        Vertex.resize(24);
        // 앞면
        Vertex[0] = { float4(-0.5f, 0.5f, 0.5f) };
        Vertex[1] = { float4(0.5f, 0.5f, 0.5f) };
        Vertex[2] = { float4(0.5f, -0.5f, 0.5f) };
        Vertex[3] = { float4(-0.5f, -0.5f, 0.5f) };

        // 뒷면
        Vertex[4] = { float4::VectorRotationToDegreeXAxis(Vertex[0].POSITION, 180.f) };
        Vertex[5] = { float4::VectorRotationToDegreeXAxis(Vertex[1].POSITION, 180.f) };
        Vertex[6] = { float4::VectorRotationToDegreeXAxis(Vertex[2].POSITION, 180.f) };
        Vertex[7] = { float4::VectorRotationToDegreeXAxis(Vertex[3].POSITION, 180.f) };

        // 왼쪽
        Vertex[8] = { float4::VectorRotationToDegreeYAxis(Vertex[0].POSITION, -90.f) };
        Vertex[9] = { float4::VectorRotationToDegreeYAxis(Vertex[1].POSITION, -90.f) };
        Vertex[11] = { float4::VectorRotationToDegreeYAxis(Vertex[3].POSITION, -90.f) };
        Vertex[10] = { float4::VectorRotationToDegreeYAxis(Vertex[2].POSITION, -90.f) };

        // 오른쪽
        Vertex[12] = { float4::VectorRotationToDegreeYAxis(Vertex[0].POSITION, 90.f) };
        Vertex[13] = { float4::VectorRotationToDegreeYAxis(Vertex[1].POSITION, 90.f) };
        Vertex[14] = { float4::VectorRotationToDegreeYAxis(Vertex[2].POSITION, 90.f) };
        Vertex[15] = { float4::VectorRotationToDegreeYAxis(Vertex[3].POSITION, 90.f) };

        // 위
        Vertex[16] = { float4::VectorRotationToDegreeXAxis(Vertex[0].POSITION, -90.f) };
        Vertex[17] = { float4::VectorRotationToDegreeXAxis(Vertex[1].POSITION, -90.f) };
        Vertex[18] = { float4::VectorRotationToDegreeXAxis(Vertex[2].POSITION, -90.f) };
        Vertex[19] = { float4::VectorRotationToDegreeXAxis(Vertex[3].POSITION, -90.f) };

        // 아래
        Vertex[20] = { float4::VectorRotationToDegreeXAxis(Vertex[0].POSITION, 90.f) };
        Vertex[21] = { float4::VectorRotationToDegreeXAxis(Vertex[1].POSITION, 90.f) };
        Vertex[22] = { float4::VectorRotationToDegreeXAxis(Vertex[2].POSITION, 90.f) };
        Vertex[23] = { float4::VectorRotationToDegreeXAxis(Vertex[3].POSITION, 90.f) };

        GameEngineVertexBuffer::Create("Box", Vertex);
    }

    {
        std::vector<int> Index;
        Index.resize(36);
        for (int i = 0; i < 6; i++)
        {
            Index[0 + i * 6] = 0 + 4 * i;
            Index[1 + i * 6] = 1 + 4 * i;
            Index[2 + i * 6] = 2 + 4 * i;
            Index[3 + i * 6] = 0 + 4 * i;
            Index[4 + i * 6] = 2 + 4 * i;
            Index[5 + i * 6] = 3 + 4 * i;
        }

        GameEngineIndexBuffer::Create("Box", Index);
    }
}

void EngineRenderingPipeLine()
{
    GameEngineRenderingPipeLine* NewPipe = GameEngineRenderingPipeLine::Create("Color");
    NewPipe->SetInputAssembler1VertexBuffer("Rect");
    NewPipe->SetInputAssembler2IndexBuffer("Rect");
    NewPipe->SetVertexShader("Color.hlsl");
    NewPipe->SetRasterizer("EngineRasterizer");
    NewPipe->SetPixelShader("Color.hlsl");
}

void ShaderCompile()
{
    GameEngineDirectory Dir;

    Dir.MoveParentToExitsChildDirectory("Shader");
    Dir.Move("Shader");

    std::vector<GameEngineFile> Shaders = Dir.GetAllFile("hlsl");

    for (size_t i = 0; i < Shaders.size(); i++)
    {
        GameEngineShader::AutoCompile(Shaders[i].GetFullPath());
    }
}

void GameEngineCore::EngineResourcesInitialize()
{
    EngineInputLayOut();       // 정점의 설명서를 만듦.
    EngineMesh();              // 정점 버퍼와 인덱스 버퍼를 만듦.
    ShaderCompile();           // 쉐이더 파일들을 모두 찾아서, 컴파일을 진행.
    EngineRasterizer();        // Rasterizer 생성.
    EngineRenderingPipeLine(); // 새 랜더링 파이프라인 개체를 만들고, 해당 개체에 위에서 만든 정점 버퍼와 인덱스 버퍼를 저장.
}

void GameEngineCore::EngineResourcesDestroy()
{
    GameEngineRenderingPipeLine::ResourcesDestroy();

    GameEnginePixelShader::ResourcesDestroy();
    GameEngineVertexShader::ResourcesDestroy();

    GameEngineVertexBuffer::ResourcesDestroy();
    GameEngineIndexBuffer::ResourcesDestroy();
    GameEngineRenderTarget::ResourcesDestroy();
    GameEngineTexture::ResourcesDestroy();
    GameEngineRasterizer::ResourcesDestroy();
    GameEngineConstantBuffer::ResourcesDestroy();

    GameEngineDevice::Destroy();
}
