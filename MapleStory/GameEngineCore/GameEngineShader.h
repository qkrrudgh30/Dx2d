// <hide/>

// GameEngineShader.h

#pragma once
#include <string>
#include <map>

enum class ShaderType
{
    Vertex,
    Pixel,
};

class ShaderResSetter
{
public:
    ShaderType   ShaderType;
    int          BindPoint;
    std::string* Name;
};

class GameEngineConstantBuffer;
class GameEngineConstantBufferSetter : public ShaderResSetter
{
public:
    GameEngineConstantBuffer* Res;
    const void*               SetData;         // 각자가 가진 정보에 대한 주소
    UINT                      Size;
    std::vector<char>         OriginalData;    // 자기메모리로 할당할 예정.

public:
    GameEngineConstantBufferSetter()
        : Res(nullptr)
        , SetData(nullptr)
        , Size(-1)
    {
    }

    void Setting() const;
};

// 설명 :
class GameEngineShader
{
    friend class GameEngineShaderResourcesHelper;

protected:
    ID3DBlob*   BinaryPtr;         // 컴파일된 바이너리 쉐이더 내용이 저장된 곳을 가리키는 포인터.
    std::string Version;           // 쉐이더 언어 버전.
    ShaderType  ShaderSettingType; // ?

private:
    std::string                                           EntryPoint;        // 쉐이더의 이름.
    std::map<std::string, GameEngineConstantBufferSetter> ConstantBufferMap; // 상수 버퍼 관리용.

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

    GameEngineConstantBufferSetter& GetConstantBufferSetter(std::string _Name);

protected:
    void CreateVersion(const std::string& _ShaderType, UINT _VersionHigh, UINT _VersionLow);

    void SetEntryPoint(const std::string& _EntryPoint)
    {
        EntryPoint = _EntryPoint;
    }

    void ShaderResCheck(); // 쉐이더에서 상수버퍼를 사용했는지 텍스처를 썼는지 체크하는 함수.

};
