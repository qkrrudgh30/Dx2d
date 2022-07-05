// <hide/>

// GameEngineVertexs.cpp

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
    const char* _SemanticName,
    DXGI_FORMAT _Format,
    unsigned int _Index,
    D3D11_INPUT_CLASSIFICATION _inputClass,
    unsigned int _InputSlot,
    unsigned int _InstanceDataStepRate
)
{
    D3D11_INPUT_ELEMENT_DESC LayOutDesc = { 0 };

    int Index = _Index;

    if (Index == -1)
    {
        if (SemanticIndexData.end() == SemanticIndexData.find(_SemanticName))
        {
            SemanticIndexData[_SemanticName] = -1;
        }

        Index = ++SemanticIndexData[_SemanticName];
    }

    LayOutDesc.SemanticName = _SemanticName;     // ex. "POSITION", "COLOR", "TANGENT", "NORMAL", ...
    LayOutDesc.SemanticIndex = Index;            // ex. "POSITION0", "POSITION1", ...
    LayOutDesc.Format = _Format;                 // ex. DXGI_FORMAT_R32G32B32A32_FLOAT 
    LayOutDesc.AlignedByteOffset = LayOutOffset;
    LayOutDesc.InputSlotClass = _inputClass;

    // 인스턴스 버퍼 세팅용
    LayOutDesc.InputSlot = _InputSlot;
    LayOutDesc.InstanceDataStepRate = _InstanceDataStepRate;
    LayOutOffset += FormatToByteScale(LayOutDesc.Format);

    InputLayOutDesc.push_back(LayOutDesc);
}
