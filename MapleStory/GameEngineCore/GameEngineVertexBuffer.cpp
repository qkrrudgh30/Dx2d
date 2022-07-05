// <hide/>

// GameEngineVertexBuffer.cpp

#include "PreCompile.h"
#include "GameEngineVertexBuffer.h"
#include <GameEngineBase/GameEngineString.h>

GameEngineVertexBuffer::GameEngineVertexBuffer()
    : Buffer(nullptr)
    , BufferDesc{}
    , OffSet(0)
{
}

GameEngineVertexBuffer::~GameEngineVertexBuffer()
{
    if (nullptr != Buffer)
    {
        Buffer->Release();
    }
}

GameEngineVertexBuffer* GameEngineVertexBuffer::Create(
    const std::string& _Name,
    const void* _Data, UINT _VertexSize,
    UINT _VertexCount,
    const GameEngineLayOutDesc& _LayOut
)
{
    GameEngineVertexBuffer* NewRes = CreateResName(_Name);
    NewRes->LayOutDesc = &_LayOut;
    NewRes->BufferCreate(_Data, _VertexSize, _VertexCount);
    return NewRes;
}

void GameEngineVertexBuffer::BufferCreate(const void* _Data, UINT _VertexSize, UINT _VertexCount)
{
    VertexSize = _VertexSize;
    VertexCount = _VertexCount;

    D3D11_SUBRESOURCE_DATA Data;
    Data.pSysMem = _Data;
    BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    BufferDesc.ByteWidth = _VertexSize * _VertexCount;
    BufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
    BufferDesc.CPUAccessFlags = 0;

    // 추가 옵션인데 쓰지 않음.
    BufferDesc.MiscFlags = 0;
    BufferDesc.StructureByteStride = 0;

    if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(&BufferDesc, &Data, &Buffer))
    {
        MsgBoxAssert("버텍스 버퍼 생성에 실패했습니다.");
    }
}

void GameEngineVertexBuffer::Setting()
{
    if (nullptr == Buffer)
    {
        MsgBoxAssert("버텍스 버퍼에 문제가 있습니다.");
    }

    // 이 세팅은 1개의 매쉬를 그리는 세팅 세팅
    GameEngineDevice::GetContext()->IASetVertexBuffers(
        0, // 버텍스 버퍼를 이중포인터로 세팅해줬을대의 사용시작 인덱스
        1, &Buffer, &VertexSize, &OffSet);
}
