// #include "myshader.hlsli"

// SV_POSITION 시맨틱
// 그래픽카드에게 이녀석은 이런 부류니까 니가 자동으로 처리하는 녀석이 있으면 하고.

// t1

// Create("TransformData");
#include "TransformHeader.fx"

// cbuffer Color : 
// TestColor;
struct Input
{
    float4 Pos : POSITION;
};

struct Output
{
    float4 Pos : SV_POSITION;
    
    float4 PosLocal : POSITION;
};

Output Color_VS(Input _Input)
{
    // 쉐이더의 경우에는 대부분의 상황에서 형변환이 가능하다.
    Output NewOutPut = (Output)0;
    // NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    
    
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    
    // float4x4 Test = WorldViewProjection;
    
    NewOutPut.Pos.w = 1.0f;
    
    NewOutPut.PosLocal = _Input.Pos;
    
    return NewOutPut;
}

cbuffer ResultColor : register(b8)
{
    float4 Color;
}

float4 Color_PS(Output _Input) : SV_Target0
{
    return Color;
}
