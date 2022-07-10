// <hide/>

// Color.hlsl

struct Input
{
    float4 Pos : POSITION;
    float4 Color : COLOR;
};

struct Output
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
};

/*
    InputAssembler1
    - InputLayout에서 만들어질 정점의 설명서를 작성함.
      "POSITION", "COLOR" 시멘틱 작성 즉, 정점마다 POSITION과 COLOR라는 두 가지 정보가 있다는 힌트
    - 정점을 만듦(GameEngineCore_Resources.cpp)
    - Buffer에 정점을 담음.
    - 아래 Input 구조체에 담기게 됨?
*/

Output Color_VS(Input _Input)       
{
/*
    Vertex Shader
    - 각 정점의 갯수만큼 실행됨.
    - World View Projection이 여기서 진행됨.
    - 각 정점에 어떤 연산을 가할지 결정하는 단계.
*/
    Output NewOutPut = (Output)0;
    NewOutPut.Pos = _Input.Pos;
    NewOutPut.Color = _Input.Color;

    return NewOutPut;
}

/*
    InputAssembler2
    - 위에서 처리된 정점을 재활용하기위한 Index Buffer가 있음. 
      이를 설정하는 단계.
    - Topology도 이때 정해져서, 기본 단위 도형을 결정하게 됨.
      우리는 삼각형으로 지정해서 작성할 예정.
*/

/*
    Tesselation (Hull Shader, Tessellator, Domain Shader) & Geometry Shader
    - 이 과정은 잠시 생략.
*/

/*
    Rasterizer
    - viewport transformation이 이 단계에서 진행됨.
    - w값(z값이 저장되어 있음)으로 나눠서 원근감을 표현하는 것도 진행.
*/

float4 Color_PS(Output _Input) : SV_Target0
{
    return _Input.Color;
}

/*
    Output Merser
    - Depth Stencil에 대한 처리 진행.

*/