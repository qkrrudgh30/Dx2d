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
    const std::string&          _Name,
    const void*                 _Data, 
    UINT                        _VertexSize,
    UINT                        _VertexCount,
    const GameEngineLayOutDesc& _LayOut
)
{
    GameEngineVertexBuffer* NewRes = CreateResName(_Name);  // 우리가 관리할 정점 버퍼 생성.
    NewRes->LayOutDesc = &_LayOut;                          // 정점 설명서를 정점 버퍼에도 세팅.
    NewRes->BufferCreate(_Data, _VertexSize, _VertexCount); // 그래픽 카드가 관리할 정점 버퍼 생성.
    return NewRes;
}

void GameEngineVertexBuffer::BufferCreate(const void* _Data, UINT _VertexSize, UINT _VertexCount)
{
    VertexSize = _VertexSize;
    VertexCount = _VertexCount;

    // 마치 그래픽 카드 속 공간을 예약하는 코드.
    D3D11_SUBRESOURCE_DATA Data; // 버퍼 혹은 텍스쳐 버퍼를 생성할 때, SUBRESOURCE_DATA 구조체 변수를 선언해서 그래픽 카드에 전달해야함.
    Data.pSysMem = _Data;                                // 땅문서
    BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;     // 땅의 용도
    BufferDesc.ByteWidth = _VertexSize * _VertexCount;   // 땅의 크기
    BufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT; // 땅의 용도변경 방법
    BufferDesc.CPUAccessFlags = 0;

    // 사용하지 않는 옵션.
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
        1, 
        &Buffer,
        &VertexSize,
        &OffSet);
}