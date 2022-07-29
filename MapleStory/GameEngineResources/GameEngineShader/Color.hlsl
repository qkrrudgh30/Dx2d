// #include "myshader.hlsli"

// SV_POSITION �ø�ƽ
// �׷���ī�忡�� �̳༮�� �̷� �η��ϱ� �ϰ� �ڵ����� ó���ϴ� �༮�� ������ �ϰ�.

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
    // ���̴��� ��쿡�� ��κ��� ��Ȳ���� ����ȯ�� �����ϴ�.
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
