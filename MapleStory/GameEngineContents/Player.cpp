// <hide/>

// Player.cpp

#include "PreCompile.h"
#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineContents/GlobalContentsValue.h>
#include <GameEngineCore/GameEngineDefaultRenderer.h>

#include <GameEngineCore/GameEngineRenderingPipeLine.h>
#include <GameEngineCore/GameEngineVertexShader.h>
#include <GameEngineCore/GameEngineConstantBuffer.h>
#include <GameEngineCore/GameEngineDevice.h>

Player::Player() 
    : Renderer(nullptr)
    , Speed(50.0f)
{
}

Player::~Player() 
{
}

void Player::Start()
{
    if (false == GameEngineInput::GetInst()->IsKey("PlayerLeft"))
    {
        GameEngineInput::GetInst()->CreateKey("PlayerLeft", VK_LEFT);
        GameEngineInput::GetInst()->CreateKey("PlayerRight", VK_RIGHT);
        GameEngineInput::GetInst()->CreateKey("PlayerUp", VK_UP);
        GameEngineInput::GetInst()->CreateKey("PlayerDown", VK_DOWN);
        GameEngineInput::GetInst()->CreateKey("PlayerForward", VK_HOME);
        GameEngineInput::GetInst()->CreateKey("PlayerBack", VK_END);
        GameEngineInput::GetInst()->CreateKey("Rot+", VK_DELETE);
        GameEngineInput::GetInst()->CreateKey("Rot-", VK_NEXT);
    }

    GetTransform().SetLocalScale({1, 1, 1});

    {
        Renderer = CreateComponent<GameEngineDefaultRenderer>();
        Renderer->GetTransform().SetLocalScale({ 100, 100, 100 });
        Renderer->SetPipeLine("Color");
        Renderer->PipeLineHelper.SetConstantBufferLink("ResultColor", Color);
    }
}

void Player::Update(float _DeltaTime)
{
    if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft"))
    {
        GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed * _DeltaTime);
    }

    if (true == GameEngineInput::GetInst()->IsPress("PlayerRight"))
    {
        GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed * _DeltaTime);
    }
    if (true == GameEngineInput::GetInst()->IsPress("PlayerUp"))
    {
        GetTransform().SetWorldMove(GetTransform().GetUpVector() * Speed * _DeltaTime);
    }
    if (true == GameEngineInput::GetInst()->IsPress("PlayerDown"))
    {
        GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed * _DeltaTime);
    }

    if (true == GameEngineInput::GetInst()->IsPress("PlayerForward"))
    {
        GetTransform().SetWorldMove(GetTransform().GetForwardVector() * Speed * _DeltaTime);
    }
    if (true == GameEngineInput::GetInst()->IsPress("PlayerBack"))
    {
        GetTransform().SetWorldMove(GetTransform().GetBackVector() * Speed * _DeltaTime);
    }

    if (true == GameEngineInput::GetInst()->IsPress("Rot+"))
    {
        Renderer->GetTransform().SetLocalRotate({ 0.0f, 0.0f, 360.0f * _DeltaTime });

        Color.x += 1.f * _DeltaTime;
    }
    if (true == GameEngineInput::GetInst()->IsPress("Rot-"))
    {
        Renderer->GetTransform().SetLocalRotate({ 0.0f, 0.0f, -360.0f * _DeltaTime });

        Color.x -= 1.f * _DeltaTime;
    }

}
