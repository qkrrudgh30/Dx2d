// <hide/>

// GameEngineDevice.h

#pragma once

// 설명 :
class GameEngineDevice
{
public:
    // constrcuter destructer
    GameEngineDevice() = delete; // 싱글톤 패턴을 위한 생성자 삭제
    ~GameEngineDevice();

    // delete Function
    GameEngineDevice(const GameEngineDevice& _Other) = delete;
    GameEngineDevice(GameEngineDevice&& _Other) noexcept = delete;
    GameEngineDevice& operator=(const GameEngineDevice& _Other) = delete;
    GameEngineDevice& operator=(GameEngineDevice&& _Other) noexcept = delete;

    static void CreateDevice();
    static void CreateSwapChain();
    static void Initialize();
    static void Destroy();

    static void RenderStart();
    static void RenderEnd();

    static ID3D11Device* GetDevice()
    {
        return Device_;
    }

    static ID3D11DeviceContext* GetContext()
    {
        return Context_;
    }

protected:

private:
    static ID3D11Device*                 Device_;
    static ID3D11DeviceContext*          Context_;
    static IDXGISwapChain*               SwapChain_;

    static class GameEngineRenderTarget* BackBufferTarget;

};

