#include "PreCompile.h"
#include "ContentsCore.h"

#include "ContentsGUIWindow.h"
#include "ShortKeyGUIWindow.h"

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
#include <GameEngineCore/GameEngineFont.h>

#pragma comment(lib, "GameEngineBase.lib")

POINT  ContentsCore::mptMousePos;
float4 ContentsCore::mf4MousePos;
bool ContentsCore::mbCameraFollowing;

enum
{
    LEVEL1 =  1,
    LEVEL2 =  2,
    LEVEL3 =  3,
    LEVEL4 =  4,
    LEVEL5 =  5,
};

ContentsCore::ContentsCore() 
    : GameEngineCore()
    , mpContentsGUIWindow(nullptr)
    , mpMainGUIWindow(nullptr)
    , mpShortKeyGUIWindow(nullptr)
    , mnCurrentLevel(0)
    , mnNextLevel(0)
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

    GameEngineFont::Load("메이플스토리");

    mpMainGUIWindow = GameEngineGUI::CreateGUIWindow<GameEngineStatusWindow>("EngineStatus", nullptr);    
    mpContentsGUIWindow = GameEngineGUI::CreateGUIWindow<ContentsGUIWindow>("ContentsGUIWindow", nullptr);
    mpShortKeyGUIWindow = GameEngineGUI::CreateGUIWindow<ShortKeyGUIWindow>("ShortKeyGUIWindow", nullptr);

    

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

    ChangeLevelNumber();

    if (mnCurrentLevel != mnNextLevel)
    {
        if (LEVEL1 == mnNextLevel)
        {
            mSoundPlayer.Stop();
            mSoundPlayer = GameEngineSound::SoundPlayControl("Login.mp3", 10);
        }

        if (LEVEL2 == mnNextLevel || LEVEL3 == mnNextLevel)
        {
            if (LEVEL2 != mnCurrentLevel && LEVEL3 != mnCurrentLevel)
            {
                mSoundPlayer.Stop();
                mSoundPlayer = GameEngineSound::SoundPlayControl("Level12.mp3", 10);
            }
        }

        if (LEVEL4 == mnNextLevel || LEVEL5 == mnNextLevel)
        {
            if (LEVEL4 != mnCurrentLevel && LEVEL5 != mnCurrentLevel)
            {
                mSoundPlayer.Stop();
                mSoundPlayer = GameEngineSound::SoundPlayControl("Level34.mp3", 10);
            }
        }

        mSoundPlayer.Volume(0.1f);
        mnCurrentLevel = mnNextLevel;
    }

}

void ContentsCore::End()
{
}

void ContentsCore::ChangeLevelNumber()
{
    if (GameEngineString::ToUpperReturn("LoginLevel") == CurrentLevel->GetNameCopy()) {    mnNextLevel = LEVEL1; }
    if (GameEngineString::ToUpperReturn("TempleOfTime0") == CurrentLevel->GetNameCopy()) { mnNextLevel = LEVEL2; }
    if (GameEngineString::ToUpperReturn("TempleOfTime1") == CurrentLevel->GetNameCopy()) { mnNextLevel = LEVEL3; }
    if (GameEngineString::ToUpperReturn("TempleOfTime2") == CurrentLevel->GetNameCopy()) { mnNextLevel = LEVEL4; }
    if (GameEngineString::ToUpperReturn("TempleOfTime3") == CurrentLevel->GetNameCopy()) { mnNextLevel = LEVEL5; }
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
        GameEngineInput::GetInst()->CreateKey("DELETE", VK_DELETE);
        GameEngineInput::GetInst()->CreateKey("INSERT", VK_INSERT);
        GameEngineInput::GetInst()->CreateKey("CamRight", VK_NEXT);
        GameEngineInput::GetInst()->CreateKey("CamUp", VK_HOME);
        GameEngineInput::GetInst()->CreateKey("PrintDescription", VK_F1);
        GameEngineInput::GetInst()->CreateKey("CamOnOffToggle", VK_F2);
        GameEngineInput::GetInst()->CreateKey("PCMapOnOffToggle", VK_F3);
        GameEngineInput::GetInst()->CreateKey("PrintPixelColor", VK_F4);
        GameEngineInput::GetInst()->CreateKey("PrintPlayerWorldPosition", VK_F5);
        GameEngineInput::GetInst()->CreateKey("FreeCameraOnOff", VK_F6);
        GameEngineInput::GetInst()->CreateKey("LimitCameraMovingOnOff", VK_F7);
        GameEngineInput::GetInst()->CreateKey("NPCConversation", 'Y');
    }

    if (false == GameEngineInput::GetInst()->IsKey("PlayerLeft"))
    {
        GameEngineInput::GetInst()->CreateKey("PlayerLeft", VK_LEFT);
        GameEngineInput::GetInst()->CreateKey("PlayerRight", VK_RIGHT);
        GameEngineInput::GetInst()->CreateKey("PlayerUp", VK_UP);
        GameEngineInput::GetInst()->CreateKey("PlayerDown", VK_DOWN);
        GameEngineInput::GetInst()->CreateKey("PlayerJump", VK_SPACE);
        GameEngineInput::GetInst()->CreateKey("PlayerAttack1", 'F');
        GameEngineInput::GetInst()->CreateKey("PlayerAttack2", 'D');
        GameEngineInput::GetInst()->CreateKey("InventoryOnOff", 'I');
        GameEngineInput::GetInst()->CreateKey("GetItem", 'Z');
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
    LoadUITextures();
    LoadNumbersTextures();
    LoadSounds();
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

    // Dir.Move("WarriorLeap");
    // GameEngineFolderTexture::Load(Dir.GetFullPath());
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

    Dir.Move("LevelUp");
    GameEngineFolderTexture::Load(Dir.GetFullPath());
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

void ContentsCore::LoadSounds()
{
    GameEngineDirectory Dir;
    MoveTo(Dir, "..\\");
    Dir.Move("Sound");

    std::vector<GameEngineFile> Sounds = Dir.GetAllFile();

    for (size_t i = 0; i < Sounds.size(); i++)
    {
        GameEngineSound::LoadRessource(Sounds[i].GetFullPath());
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
    GameEngineTexture::Cut("CharacterLadderIdle.png", 1, 1);
    GameEngineTexture::Cut("CharacterLadderMove.png", 2, 1);
    GameEngineTexture::Cut("CharacterStab.png", 3, 1);
    GameEngineTexture::Cut("CharacterStabF.png", 4, 1);
    GameEngineTexture::Cut("CharacterStand.png", 5, 1);
    GameEngineTexture::Cut("CharacterSwing.png", 3, 1);
    GameEngineTexture::Cut("CharacterSwingF.png", 4, 1);
    GameEngineTexture::Cut("CharacterWalk.png", 6, 1);
    GameEngineTexture::Cut("CharacterDead.png", 1, 1);
    GameEngineTexture::Cut("FallTomb.png", 4, 1);

    /* Item */
    GameEngineTexture::Cut("WhitePortion.png", 1, 1);
    GameEngineTexture::Cut("BluePortion.png", 1, 1);
    GameEngineTexture::Cut("Elixir.png", 1, 1);
    GameEngineTexture::Cut("MesoBag.png", 4, 1);
    GameEngineTexture::Cut("MesoBunch.png", 4, 1);
    GameEngineTexture::Cut("MesoPeny.png", 4, 1);
    GameEngineTexture::Cut("Temple2MonsterItem.png", 1, 1);
    GameEngineTexture::Cut("Temple3MonsterItem.png", 1, 1);
    GameEngineTexture::Cut("Temple3BossItem.png", 1, 1);

    /* Map */
    GameEngineTexture::Cut("LoginBackground.png", 1, 1);
    GameEngineTexture::Cut("LoginButton.png", 3, 1);
    GameEngineTexture::Cut("ExitButton.png", 3, 1);

    GameEngineTexture::Cut("Temple0BackGround.png", 1, 1);
    GameEngineTexture::Cut("Temple0Tile.png", 1, 1);
    GameEngineTexture::Cut("Temple0TileP.png", 1, 1);
    GameEngineTexture::Cut("Temple0Cloud.png", 1, 1);

    GameEngineTexture::Cut("Temple1BackGround.png", 1, 1);
    GameEngineTexture::Cut("Temple1Tile.png", 1, 1);
    GameEngineTexture::Cut("Temple1TileP.png", 1, 1);
    GameEngineTexture::Cut("Temple1Cloud.png", 1, 1);

    GameEngineTexture::Cut("Temple2BackGround.png", 1, 1);
    GameEngineTexture::Cut("Temple2Tile.png", 1, 1);
    GameEngineTexture::Cut("Temple2TileP.png", 1, 1);
    GameEngineTexture::Cut("Temple2Cloud.png", 1, 1);

    GameEngineTexture::Cut("Temple3BackGround.png", 1, 1);
    GameEngineTexture::Cut("Temple3Tile.png", 1, 1);
    GameEngineTexture::Cut("Temple3TileP.png", 1, 1);
    GameEngineTexture::Cut("Temple3Cloud.png", 1, 1);
    GameEngineTexture::Cut("Portal.png", 8, 1);
    GameEngineTexture::Cut("Veil.png", 8, 1);

    /* Monster */
    GameEngineTexture::Cut("Temple2MonsterStand.png", 12, 1);
    GameEngineTexture::Cut("Temple2MonsterMove.png", 6, 1);
    GameEngineTexture::Cut("Temple2MonsterHitting1.png", 4, 1);
    GameEngineTexture::Cut("Temple2MonsterHitting2.png", 7, 1);
    GameEngineTexture::Cut("Temple2MonsterDie.png", 12, 1);
    GameEngineTexture::Cut("Temple2MonsterAttack1.png", 17, 1);
    GameEngineTexture::Cut("Temple2MonsterAttack2.png", 17, 1);
    GameEngineTexture::Cut("Temple2MonsterHitted.png", 1, 1);

    GameEngineTexture::Cut("Temple3MonsterStand.png", 12, 1);
    GameEngineTexture::Cut("Temple3MonsterMove.png", 12, 1);
    GameEngineTexture::Cut("Temple3MonsterHitting1.png", 4, 1);
    GameEngineTexture::Cut("Temple3MonsterHitting2.png", 7, 1);
    GameEngineTexture::Cut("Temple3MonsterDie.png", 17, 1);
    GameEngineTexture::Cut("Temple3MonsterAttack1.png", 35, 1);
    GameEngineTexture::Cut("Temple3MonsterAttack2.png", 23, 1);
    GameEngineTexture::Cut("Temple3MonsterHitted.png", 1, 1);

    GameEngineTexture::Cut("Temple3BossStand.png", 8, 1);
    GameEngineTexture::Cut("Temple3BossSkill1.png", 13, 1);
    GameEngineTexture::Cut("Temple3BossSkill2.png", 13, 1);
    GameEngineTexture::Cut("Temple3BossMove.png", 8, 1);
    GameEngineTexture::Cut("Temple3BossHitting1.png", 5, 1);
    GameEngineTexture::Cut("Temple3BossHitting2.png", 5, 1);
    GameEngineTexture::Cut("Temple3BossBullet1.png", 4, 1);
    GameEngineTexture::Cut("Temple3BossDie.png", 17, 1);
    GameEngineTexture::Cut("Temple3BossAttack1.png", 13, 1);
    GameEngineTexture::Cut("Temple3BossAttack2.png", 15, 1);
    GameEngineTexture::Cut("Temple3BossHitted.png", 1, 1);

    /* Numbers */
    /* Skill */
    GameEngineTexture::Cut("LeapAttack.png", 8, 1);
    GameEngineTexture::Cut("SlashBlast.png", 11, 1);
    GameEngineTexture::Cut("Hitting.png", 6, 1);
    GameEngineTexture::Cut("Clear.png", 1, 1);
    /* UI */
    GameEngineTexture::Cut("MenuButton.png", 3, 1);
    GameEngineTexture::Cut("InventoryBackGround.png", 1, 1);
    GameEngineTexture::Cut("StoreBuyButton.png", 3, 1);
    GameEngineTexture::Cut("StoreExitButton.png", 3, 1);
    GameEngineTexture::Cut("PopupMenuBackGround.png", 3, 1);

    // NPC
    GameEngineTexture::Cut("JohannaStand.png", 1, 1);
    GameEngineTexture::Cut("JohannaSay.png", 12, 1);
    GameEngineTexture::Cut("JohannaEye.png", 7, 1);
    
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
