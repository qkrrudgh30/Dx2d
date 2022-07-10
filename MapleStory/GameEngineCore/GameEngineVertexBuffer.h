// <hide/>

// GameEngineVertexBuffer.h

#pragma once
#include <string>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineRes.h"
#include "GameEngineVertexs.h"

// 설명 :
class GameEngineVertexBuffer : public GameEngineRes<GameEngineVertexBuffer>
{
    friend GameEngineRes<GameEngineVertexBuffer>;

private:
    D3D11_BUFFER_DESC           BufferDesc;  // 버퍼의 설명서
    ID3D11Buffer*               Buffer;      // 버퍼 핸들러
    UINT                        VertexCount; // 정점 갯수
    UINT                        VertexSize;  // 정점의 크기
    UINT                        OffSet;      // 
    const GameEngineLayOutDesc* LayOutDesc;  // 정점의 설명서

public:
    template<typename VertexType>
    static GameEngineVertexBuffer* Create(const std::string& _Name, const std::vector<VertexType>& _Vertex)
    {
        //           버퍼이름   시작주소               정점의 크기                           정점의 갯수                   정점의 설명서    
        return Create(_Name, &_Vertex[0], static_cast<UINT>(sizeof(VertexType)), static_cast<UINT>(_Vertex.size()), VertexType::LayOut);
    }

    static GameEngineVertexBuffer* Create(const std::string& _Name, const void* _Data, UINT _VertexSize, UINT _VertexCount, const GameEngineLayOutDesc& _LayOut);

    const GameEngineLayOutDesc* GetLayOutDesc()
    {
        return LayOutDesc;
    }

    void Setting();                                                            // 만든 정점 버퍼를 그래픽 카드에 꽂기 위한 함수.

protected:
    void BufferCreate(const void* _Data, UINT _VertexSize, UINT _VertexCount); // 그래픽 카드에 정점 버퍼 생성 함수.

private:
    GameEngineVertexBuffer();
    ~GameEngineVertexBuffer();

    // delete Function
    GameEngineVertexBuffer(const GameEngineVertexBuffer& _Other) = delete;
    GameEngineVertexBuffer(GameEngineVertexBuffer&& _Other) noexcept = delete;
    GameEngineVertexBuffer& operator=(const GameEngineVertexBuffer& _Other) = delete;
    GameEngineVertexBuffer& operator=(GameEngineVertexBuffer&& _Other) noexcept = delete;
};

