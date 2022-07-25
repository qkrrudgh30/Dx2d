#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCore.h>

// ���� : ���α׷� ��ü�� �����ϰ� �Ѵ�.
class ContentsCore : public GameEngineCore
{
private:
    static POINT  mptMousePos;
    static float4 mf4MousePos;
    static bool   mbCameraFollowing;

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

