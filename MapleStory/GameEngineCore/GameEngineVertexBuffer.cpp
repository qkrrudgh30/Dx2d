// <hide/>

// GameEngineVertexBuffer.cpp

#include "PreCompile.h"
#include "GameEngineVertexBuffer.h"
#include <GameEngineBase/GameEngineString.h>

GameEngineVertexBuffer::GameEngineVertexBuffer()
    : Buffer(nullptr)
    , BufferDesc{}
{
}

GameEngineVertexBuffer::~GameEngineVertexBuffer()
{
}

GameEngineVertexBuffer* GameEngineVertexBuffer::Create(const std::string& _Name, const void* _Data, size_t _Size)
{
    GameEngineVertexBuffer* NewRes = CreateResName(_Name);

    D3D11_SUBRESOURCE_DATA Data;
    Data.pSysMem = _Data;                                        // 초기화용 데이터
    NewRes->BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;     // 버퍼의 랜더링적 용도
    NewRes->BufferDesc.ByteWidth = static_cast<UINT>(_Size);     // 할당 하려는 버퍼의 크기
    NewRes->BufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT; // 할당하려는 버퍼의 액세스 권한과 용도
    // BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_READ;
    NewRes->BufferDesc.CPUAccessFlags = 0;                       // CPU에서 액세스 할 수 있는지.
    NewRes->BufferDesc.MiscFlags = 0;
    NewRes->BufferDesc.StructureByteStride = 0;

    if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(&NewRes->BufferDesc, &Data, &NewRes->Buffer))
    {
        MsgBoxAssert("버텍스 버퍼 생성에 실패했습니다.");
    }

    return NewRes;
}
