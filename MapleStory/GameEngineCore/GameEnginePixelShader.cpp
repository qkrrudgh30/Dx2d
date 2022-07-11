// <hide/>

// GameEnginePixelShader.cpp

#include "PreCompile.h"
#include "GameEnginePixelShader.h"

GameEnginePixelShader::GameEnginePixelShader()
    : ShaderPtr(nullptr)
{
    ShaderSettingType = ShaderType::Pixel;
}

GameEnginePixelShader::~GameEnginePixelShader()
{
    if (nullptr != ShaderPtr)
    {
        ShaderPtr->Release();
        ShaderPtr = nullptr;
    }
}

GameEnginePixelShader* GameEnginePixelShader::Load(std::string _Path, std::string _EntryPoint, UINT _VersionHigh /*= 5*/, UINT _VersionLow /*= 0*/)
{
    return Load(_Path, GameEnginePath::GetFileName(_Path), _EntryPoint, _VersionHigh, _VersionLow);
}

GameEnginePixelShader* GameEnginePixelShader::Load(std::string _Path, std::string _Name, std::string _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0)
{
    GameEnginePixelShader* NewRes = CreateResName(_Name);
    NewRes->ShaderCompile(_Path, _EntryPoint, _VersionHigh, _VersionLow);
    return NewRes;
}

void GameEnginePixelShader::Setting()
{
    if (nullptr == ShaderPtr)
    {
        MsgBoxAssert("쉐이더 세팅 오류");
    }

    GameEngineDevice::GetContext()->PSSetShader(ShaderPtr, nullptr, 0);
}

void GameEnginePixelShader::ShaderCompile(std::string _Path, std::string _EntryPoint, UINT _VersionHigh, UINT _VersionLow)
{
    CreateVersion("ps", _VersionHigh, _VersionLow);
    SetEntryPoint(_EntryPoint);

    unsigned int Flag = 0;

#ifdef _DEBUG
    Flag = D3D10_SHADER_DEBUG;
#endif

    Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

    ID3DBlob* Error;

    std::wstring UnicodePath = GameEngineString::AnsiToUnicodeReturn(_Path);

    if (S_OK != D3DCompileFromFile(
        UnicodePath.c_str(),
        nullptr,
        nullptr,
        _EntryPoint.c_str(),
        Version.c_str(),
        Flag,
        0,
        &BinaryPtr,
        &Error)
        )
    {
        std::string ErrorText = reinterpret_cast<char*>(Error->GetBufferPointer());
        MsgBoxAssertString(ErrorText);
        return;
    }

    if (S_OK != GameEngineDevice::GetDevice()->CreatePixelShader(
        BinaryPtr->GetBufferPointer(),
        BinaryPtr->GetBufferSize(),
        nullptr,
        &ShaderPtr))
    {
        MsgBoxAssert("버텍스 쉐이더 핸들 생성에 실패했습니다.");
    }

    ShaderResCheck();
}
