#include "PreCompile.h"
#include "ContentsCore.h"

#include "LoginLevel.h"
#include "TempleOfTime0.h"
#include "TempleOfTime1.h"
#include "TempleOfTime2.h"
#include "TempleOfTime3.h"

#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineShader.h>
#include <GameEngineCore/GameEngineSampler.h>
#include <GameEngineCore/GameEngineRenderingPipeLine.h>

#pragma comment(lib, "GameEngineBase.lib")

POINT  ContentsCore::mptMousePos;
float4 ContentsCore::mf4MousePos;
bool ContentsCore::mbCameraFollowing;

ContentsCore::ContentsCore() 
    : GameEngineCore()
{
    mbCameraFollowing = true;
}

ContentsCore::~ContentsCore() 
{
}

void ContentsCore::Start()
{
    CreateKeys();

    LoadTextures();

    LoadShaderFiles();

    CutAtlasTexture();

    CreateLevels();

    CreateRenderingPipeline();
}

void ContentsCore::Update(float _DeltaTime)
{
    GetCursorPos(&mptMousePos);
    ScreenToClient(GameEngineWindow::GetHWND(), &mptMousePos);
    mf4MousePos.x = (float)mptMousePos.x - (GameEngineWindow::GetScale().x / 2.f);
    mf4MousePos.y = -(float)mptMousePos.y + (GameEngineWindow::GetScale().y / 2.f);

    if (true == GameEngineInput::GetInst()->IsDown("CamOnOffToggle"))
    {
        mbCameraFollowing = !mbCameraFollowing;
    }
}

void ContentsCore::End()
{
}

void ContentsCore::LoadShaderFiles()
{
    /*GameEngineDirectory Dir;

    Dir.MoveParentToExitsChildDirectory("ContentsShader");
    Dir.Move("ContentsShader");

    std::vector<GameEngineFile> Shaders = Dir.GetAllFile("hlsl");

    for (size_t i = 0; i < Shaders.size(); i++)
    {
        GameEngineShader::AutoCompile(Shaders[i].GetFullPath());
    }*/
}

void ContentsCore::CreateRenderingPipeline()
{
    {
        /*GameEngineRenderingPipeLine* NewPipe = GameEngineRenderingPipeLine::Create("Cloud");
        NewPipe->SetVertexShader("Cloud.hlsl");
        NewPipe->SetPixelShader("Cloud.hlsl");*/
    }
}

void ContentsCore::CreateKeys()
{
    if (false == GameEngineInput::GetInst()->IsKey("CamLeft"))
    {
        GameEngineInput::GetInst()->CreateKey("CamOnOffToggle", VK_INSERT);
        GameEngineInput::GetInst()->CreateKey("CamLeft", VK_DELETE);
        GameEngineInput::GetInst()->CreateKey("CamRight", VK_NEXT);
        GameEngineInput::GetInst()->CreateKey("CamUp", VK_HOME);
        GameEngineInput::GetInst()->CreateKey("CamDown", VK_END);
    }

    if (false == GameEngineInput::GetInst()->IsKey("PlayerLeft"))
    {
        GameEngineInput::GetInst()->CreateKey("PlayerLeft", VK_LEFT);
        GameEngineInput::GetInst()->CreateKey("PlayerRight", VK_RIGHT);
        GameEngineInput::GetInst()->CreateKey("PlayerUp", VK_UP);
        GameEngineInput::GetInst()->CreateKey("PlayerDown", VK_DOWN);
        GameEngineInput::GetInst()->CreateKey("PlayerJump", VK_SPACE);
        GameEngineInput::GetInst()->CreateKey("PlayerDoubleJump", VK_CONTROL);
    }
}

void ContentsCore::LoadTextures()
{
    /*
    {
        D3D11_SAMPLER_DESC Desc = { D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_LINEAR, };
        Desc.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
        Desc.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
        Desc.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;
        Desc.MipLODBias = 0.0f;
        Desc.MaxAnisotropy = 1;
        Desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
        Desc.MinLOD = -FLT_MAX;
        Desc.MaxLOD = FLT_MAX;

        GameEngineSampler::Create("CloudSampler", Desc);
    }
    */

    LoadShaderFiles();
    CreateRenderingPipeline();
    LoadCharacterTextures();
    LoadItemTextures();
    LoadMapTextures();
    LoadMonsterTextures();
    LoadSkillTextures();
}

void ContentsCore::LoadCharacterTextures()
{
    GameEngineDirectory Dir;
    MoveTo(Dir, "Character");

    std::vector<GameEngineFile> Textures = Dir.GetAllFile();

    for (size_t i = 0; i < Textures.size(); i++)
    {
        GameEngineTexture::Load(Textures[i].GetFullPath());
    }


}

void ContentsCore::LoadItemTextures()
{
    GameEngineDirectory Dir;
    MoveTo(Dir, "Item");

    std::vector<GameEngineFile> Textures = Dir.GetAllFile();

    for (size_t i = 0; i < Textures.size(); i++)
    {
        GameEngineTexture::Load(Textures[i].GetFullPath());
    }
}

void ContentsCore::LoadMapTextures()
{
    GameEngineDirectory Dir;
    MoveTo(Dir, "Map");

    std::vector<GameEngineFile> Textures = Dir.GetAllFile();

    for (size_t i = 0; i < Textures.size(); i++)
    {
        GameEngineTexture::Load(Textures[i].GetFullPath());
    }
}

void ContentsCore::LoadMonsterTextures()
{
    GameEngineDirectory Dir;
    MoveTo(Dir, "Monster");

    std::vector<GameEngineFile> Textures = Dir.GetAllFile();

    for (size_t i = 0; i < Textures.size(); i++)
    {
        GameEngineTexture::Load(Textures[i].GetFullPath());
    }
}

void ContentsCore::LoadSkillTextures()
{
    GameEngineDirectory Dir;
    MoveTo(Dir, "Skill");

    std::vector<GameEngineFile> Textures = Dir.GetAllFile();

    for (size_t i = 0; i < Textures.size(); i++)
    {
        GameEngineTexture::Load(Textures[i].GetFullPath());
    }

    Dir.Move("WarriorLeap");
    GameEngineFolderTexture::Load(Dir.GetFullPath());
}

void ContentsCore::LoadUITextures()
{
    GameEngineDirectory Dir;
    MoveTo(Dir, "UI");

    std::vector<GameEngineFile> Textures = Dir.GetAllFile();

    for (size_t i = 0; i < Textures.size(); i++)
    {
        GameEngineTexture::Load(Textures[i].GetFullPath());
    }
}

void ContentsCore::LoadNumbersTextures()
{
    GameEngineDirectory Dir;
    MoveTo(Dir, "Numbers");

    std::vector<GameEngineFile> Textures = Dir.GetAllFile();

    for (size_t i = 0; i < Textures.size(); i++)
    {
        GameEngineTexture::Load(Textures[i].GetFullPath());
    }
}

void ContentsCore::MoveTo(GameEngineDirectory& _Dir, const std::string& _strForderName)
{
    _Dir.MoveParentToExitsChildDirectory("ContentsResources");
    _Dir.Move("ContentsResources");
    _Dir.Move("Texture");
    _Dir.Move(_strForderName);
}

void ContentsCore::CutAtlasTexture()
{
    /* Character */
    GameEngineTexture::Cut("CharacterAlert.png", 5, 1);
    GameEngineTexture::Cut("CharacterJump.png", 1, 1);
    GameEngineTexture::Cut("CharacterLadder.png", 2, 1);
    GameEngineTexture::Cut("CharacterProne.png", 1, 1);
    GameEngineTexture::Cut("CharacterproneStab.png", 2, 1);
    GameEngineTexture::Cut("CharacterRope.png", 2, 1);
    GameEngineTexture::Cut("CharacterSit.png", 1, 1);
    GameEngineTexture::Cut("CharacterStabT1.png", 3, 1);
    GameEngineTexture::Cut("CharacterStabT2.png", 3, 1);
    GameEngineTexture::Cut("CharacterStabTF.png", 4, 1);
    GameEngineTexture::Cut("CharacterStand.png", 5, 1);
    GameEngineTexture::Cut("CharacterSwingP1.png", 3, 1);
    GameEngineTexture::Cut("CharacterSwingP2.png", 3, 1);
    GameEngineTexture::Cut("CharacterSwingPF.png", 4, 1);
    GameEngineTexture::Cut("CharacterWalk.png", 6, 1);
    GameEngineTexture::Cut("CharacterDead.png", 4, 1);
    GameEngineTexture::Cut("FallTomb.png", 4, 1);

    /* Item */
    GameEngineTexture::Cut("BluePortion.png", 1, 1);
    GameEngineTexture::Cut("DodoItem.png", 1, 1);
    GameEngineTexture::Cut("Elixir.png", 1, 1);
    GameEngineTexture::Cut("MesoBag.png", 1, 1);
    GameEngineTexture::Cut("MesoBunch.png", 1, 1);
    GameEngineTexture::Cut("MesoPeny.png", 1, 1);
    GameEngineTexture::Cut("Monster1Item.png", 1, 1);
    GameEngineTexture::Cut("Monster2Item.png", 1, 1);
    GameEngineTexture::Cut("WhitePortion.png", 1, 1);

    /* Map */
    GameEngineTexture::Cut("LoginBackground.png", 1, 1);
    GameEngineTexture::Cut("LoginButton.png", 3, 1);
    GameEngineTexture::Cut("ExitButton.png", 3, 1);

    GameEngineTexture::Cut("Temple0BackGround.png", 1, 1);
    GameEngineTexture::Cut("Temple0Tile.png", 1, 1);
    GameEngineTexture::Cut("Temple0Cloud.png", 1, 1);

    GameEngineTexture::Cut("Temple1BackGround.png", 1, 1);
    GameEngineTexture::Cut("Temple1Tile.png", 1, 1);
    GameEngineTexture::Cut("Temple1Cloud.png", 1, 1);

    GameEngineTexture::Cut("Temple2BackGround.png", 1, 1);
    GameEngineTexture::Cut("Temple2Tile.png", 1, 1);
    GameEngineTexture::Cut("Temple2Cloud.png", 1, 1);

    GameEngineTexture::Cut("Temple3BackGround.png", 1, 1);
    GameEngineTexture::Cut("Temple3Tile.png", 1, 1);
    GameEngineTexture::Cut("Temple3Cloud.png", 1, 1);
    GameEngineTexture::Cut("Portal.png", 8, 1);
    GameEngineTexture::Cut("Veil.png", 8, 1);

    /* Monster */
    /* Numbers */
    /* Skill */
    /* UI */
    
    
    
    
}

void ContentsCore::CreateLevels()
{
    CreateLevel<LoginLevel>("LoginLevel");
    CreateLevel<TempleOfTime0>("TempleOfTime0");
    CreateLevel<TempleOfTime1>("TempleOfTime1");
    CreateLevel<TempleOfTime2>("TempleOfTime2");
    CreateLevel<TempleOfTime3>("TempleOfTime3");

    ChangeLevel("LoginLevel");
}
