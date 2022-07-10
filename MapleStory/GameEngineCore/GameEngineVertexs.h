// <hide/>

// GameEngineVertex.h

#pragma once

#include <GameEngineBase/GameEngineMath.h>

class GameEngineLayOutDesc
{
    friend class GameEngineInputLayOut;

public:
    unsigned int                          LayOutOffset;      // 정점 설명서의 크기. 이 크기를 기준으로 정렬됨.
    std::map<const char*, int>            SemanticIndexData; // "POSITION1", "POSITION2", ...가 가능해짐.
    std::vector<D3D11_INPUT_ELEMENT_DESC> InputLayOutDesc;   // 정점 설명서들.

public:
    GameEngineLayOutDesc()
        : LayOutOffset(0)
    {
    }

    void AddInputLayOut(
        const char*                _SemanticName,
        DXGI_FORMAT                _Format,
        unsigned int               _Index = -1,
        D3D11_INPUT_CLASSIFICATION _inputClass = D3D11_INPUT_PER_VERTEX_DATA,
        unsigned int               _InputSlot = 0,
        unsigned int               _InstanceDataStepRate = 0
    );

};

struct GameEngineVertex
{
public:
    static GameEngineLayOutDesc LayOut; // 정점의 설명서들을 관리할 정적 멤버.

public:
    float4 POSITION;
    float4 COLOR;
};
