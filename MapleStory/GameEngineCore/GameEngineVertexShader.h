// <hide/>

// GameEngineVertexShader.h

#pragma once
#include "GameEngineShader.h"
#include "GameEngineRes.h"

// 설명 :
class GameEngineInputLayOut;
class GameEngineVertexShader
    : public GameEngineShader
    , public GameEngineRes<GameEngineVertexShader>

{
    friend GameEngineInputLayOut;                 // 인풋 레이아웃을 작성시, 쉐이더를 알고있어야 함.
    friend GameEngineShader;                      // 부모 클래스에서 컴파일 예정.
    friend GameEngineRes<GameEngineVertexShader>; // 리소스 접근.

private:
    ID3D11VertexShader* ShaderPtr;

public:
    void Setting();

protected:
    void ShaderCompile(std::string _Path, std::string _EntryPoint, UINT _VersionHigh, UINT _VersionLow);

private:
    // constrcuter destructer
    GameEngineVertexShader();
    ~GameEngineVertexShader();

    // delete Function
    GameEngineVertexShader(const GameEngineVertexShader& _Other) = delete;
    GameEngineVertexShader(GameEngineVertexShader&& _Other) noexcept = delete;
    GameEngineVertexShader& operator=(const GameEngineVertexShader& _Other) = delete;
    GameEngineVertexShader& operator=(GameEngineVertexShader&& _Other) noexcept = delete;

    static GameEngineVertexShader* Load(std::string _Path, std::string _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0);

    static GameEngineVertexShader* Load(std::string _Path, std::string _Name, std::string _EntryPoint, UINT _VersionHigh, UINT _VersionLow);

};
