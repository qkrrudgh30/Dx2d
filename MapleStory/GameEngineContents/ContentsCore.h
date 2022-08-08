#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCore.h>

// 설명 : 프로그램 자체를 시작하게 한다.
class GameEngineStatusWindow;
class ContentsGUIWindow;
class ContentsCore : public GameEngineCore
{
private:
    static POINT  mptMousePos;
    static float4 mf4MousePos;
    static bool   mbCameraFollowing;
    GameEngineStatusWindow* mpMainGUIWindow;
    ContentsGUIWindow* mpContentsGUIWindow;

public:
    // constrcuter destructer
    ContentsCore(); 
    ~ContentsCore(); 

    // delete Function
    ContentsCore(const ContentsCore& _Other) = delete;
    ContentsCore(ContentsCore&& _Other) noexcept = delete;
    ContentsCore& operator=(const ContentsCore& _Other) = delete;
    ContentsCore& operator=(ContentsCore&& _Other) noexcept = delete;

    std::string GetWindowTitle() override
    {
        return "MapleStory";
    }

    static inline float4 GetMousePos()
    {
        return mf4MousePos;
    }

    static inline bool IsCameraFollowingOn()
    {
        return mbCameraFollowing;
    }

    GameEngineStatusWindow* GetGUIWindow() { return mpMainGUIWindow; }

    virtual float4 StartWindowSize() override { return { 1280.0f, 720.0f }; };
    virtual float4 StartWindowPosition() override { return { 0,0 }; };

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

    void ChangeLevelWithAlphaBlending();

private:
    void CreateKeys();
    void LoadTextures();
    void LoadShaderFiles();
    void CreateRenderingPipeline();

    void LoadCharacterTextures();
    void LoadItemTextures();
    void LoadMapTextures();
    void LoadMonsterTextures();
    void LoadSkillTextures();
    void LoadUITextures();
    void LoadNumbersTextures();
    void LoadSounds();

    void MoveTo(GameEngineDirectory& _Dir, const std::string& _strForderName);

    void CutAtlasTexture();

    void CreateLevels();

};

