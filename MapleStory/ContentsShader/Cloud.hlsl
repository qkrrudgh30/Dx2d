#include "TransformData.hlsli"

struct Input
{
    float4 Pos : POSITION;
    float4 Tex : TEXCOORD;
};

struct Output
{
    float4 Pos : SV_POSITION;
    float4 PosLocal : POSITION;
    float4 Tex : TEXCOORD;
};

cbuffer AtlasData : register(b1)
{
    float2 TextureFramePos;
    float2 TextureFrameSize;
};

Output Cloud_VS(Input _Input)
{
    Output NewOutPut = (Output)0;
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.Pos.w = 1.0f;
    NewOutPut.PosLocal = _Input.Pos;

    NewOutPut.Tex.x = (_Input.Tex.x * TextureFrameSize.x) + TextureFramePos.x;
    NewOutPut.Tex.y = (_Input.Tex.y * TextureFrameSize.y) + TextureFramePos.y;

    return NewOutPut;
}

Texture2D CloudTex : register(t0);
SamplerState CloudSam : register(s0);
float4 Cloud_PS(Output _Input) : SV_Target0
{
    float4 res = CloudTex.Sample(CloudSam, _Input.Tex.xy);

    if (res.r <= 0.00001 && res.g <= 0.000001 && res.b <= 0.000001)
    {
        discard;
    }

    return res;
}
