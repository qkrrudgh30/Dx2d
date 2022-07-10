// <hide/>

// GameEngineTexture.h

#pragma once

#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineRes.h"

// 설명 : DX 관련 자원. 그래픽카드를 통해 랜더링될 도화지의 개념.
class GameEngineTexture : public GameEngineRes<GameEngineTexture>
{
public:
    // constrcuter destructer
    GameEngineTexture();
    ~GameEngineTexture();

    // delete Function
    GameEngineTexture(const GameEngineTexture& _Other) = delete;
    GameEngineTexture(GameEngineTexture&& _Other) noexcept = delete;
    GameEngineTexture& operator=(const GameEngineTexture& _Other) = delete;
    GameEngineTexture& operator=(GameEngineTexture&& _Other) noexcept = delete;

    // static
    static GameEngineTexture* Create(const std::string& _Name, ID3D11Texture2D* _Texture);
    static GameEngineTexture* Create(ID3D11Texture2D* _Texture);

    // Member
    ID3D11RenderTargetView* CreateRenderTargetView();

protected:

private:
    ID3D11Texture2D*        Texture2D;
    ID3D11RenderTargetView* RenderTargetView;

};