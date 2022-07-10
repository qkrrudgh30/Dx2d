// <hide/>

// GameEngineVertex.cpp

#include "PreCompile.h"
#include "GameEngineVertexs.h"

GameEngineLayOutDesc GameEngineVertex::LayOut;

unsigned int FormatToByteScale(DXGI_FORMAT _Format)
{
    switch (_Format)
    {
    case DXGI_FORMAT_UNKNOWN:
        MsgBoxAssert("Error with DXGI_FORMAT_UNKNOWN.");
        return -1;
    case DXGI_FORMAT_R32G32B32A32_TYPELESS:
    case DXGI_FORMAT_R32G32B32A32_FLOAT:
    case DXGI_FORMAT_R32G32B32A32_UINT:
    case DXGI_FORMAT_R32G32B32A32_SINT:
        return 16;
    default:
        break;
    }

    MsgBoxAssert("Error with unknown _Format's value");
    return -1;
}

void GameEngineLayOutDesc::AddInputLayOut(
    const char*                _SemanticName, 
    DXGI_FORMAT                _Format, 
    unsigned int               _Index, 
    D3D11_INPUT_CLASSIFICATION _inputClass,
    unsigned int               _InputSlot,
    unsigned int               _InstanceDataStepRate)
{
    D3D11_INPUT_ELEMENT_DESC LayOutDesc = { 0, }; // 현재 정점의 설명서 초기화.

    int Index = _Index;

    if (-1 == Index)                                                          // 1. 만약 해당 시멘틱 이름의 인덱스가 기본값으로 들어온다면,
    {
        if (SemanticIndexData.end() == SemanticIndexData.find(_SemanticName)) // 2. 게다가 해당 시멘틱 이름이 들어온적 없었다면,
        {
            SemanticIndexData[_SemanticName] = -1;                            // 3. -1로 저장해서 처음이라는 것을 지정함.
        }

        Index = ++SemanticIndexData[_SemanticName];                           // 4. 이로써, POSITION0가 있다면 다음부턴 1, 2, 3...
    }

    LayOutDesc.SemanticName = _SemanticName;     // ex. "POSITION", "COLOR", "TANGENT", "NORMAL", ...
    LayOutDesc.SemanticIndex = Index;            // ex. "POSITION0", "POSITION1", ...
    LayOutDesc.Format = _Format;                 // ex. DXGI_FORMAT_R32G32B32A32_FLOAT 
    LayOutDesc.AlignedByteOffset = LayOutOffset; // 이전 정점들의 총 크기
    LayOutDesc.InputSlotClass = _inputClass;     // 이전 정점의 크기

    // 인스턴스 버퍼 세팅용
    LayOutDesc.InputSlot = _InputSlot;
    LayOutDesc.InstanceDataStepRate = _InstanceDataStepRate;

    LayOutOffset += FormatToByteScale(LayOutDesc.Format); // 다음 정점의 설명서에 적힐 "이전 정점들의 총 크기"를 누적.

    InputLayOutDesc.push_back(LayOutDesc);                // 작성 완료된 정점의 설명서를 추가함.
}
