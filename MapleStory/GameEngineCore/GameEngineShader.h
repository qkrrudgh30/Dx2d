// <hide/>

// GameEngineShader.h

#pragma once
#include <string>

// 설명 :
class GameEngineShader
{
protected:
    ID3DBlob*   BinaryPtr;  // 컴파일된 바이너리 쉐이더 내용이 저장된 곳을 가리키는 포인터.
    std::string Version;    // 쉐이더 언어 버전.

private:
    std::string EntryPoint; // 쉐이더의 이름.

public:
    // constrcuter destructer
    GameEngineShader();
    ~GameEngineShader();

    // delete Function
    GameEngineShader(const GameEngineShader& _Other) = delete;
    GameEngineShader(GameEngineShader&& _Other) noexcept = delete;
    GameEngineShader& operator=(const GameEngineShader& _Other) = delete;
    GameEngineShader& operator=(GameEngineShader&& _Other) noexcept = delete;

    static void AutoCompile(const std::string& _Path);

protected:
    void CreateVersion(const std::string& _ShaderType, UINT _VersionHigh, UINT _VersionLow);

    void SetEntryPoint(const std::string& _EntryPoint)
    {
        EntryPoint = _EntryPoint;
    }

};
