// <hide/>

// Veil.h

#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <queue>

enum class VEIL_EFFECT
{
    NONE,
    FADE_IN,
    FADE_OUT,
};

// Ό³Έν :
class GameEngineDefaultRenderer;
class GameEngineSoundPlayer;
class Veil : public GameEngineActor
{
private:
    GameEngineDefaultRenderer*        mpRenderer;
    float4                            mf4Size;
    float4                            mf4Color;
    static VEIL_EFFECT                meVeilEffect;
    static std::queue<VEIL_EFFECT>    mqVeilEffectJobQueue; 

public:
    // Constrcutor & Destructor
    Veil();
    ~Veil();

    // Delete function
    Veil(const Veil& _Other) = delete;
    Veil(Veil&& _Other) noexcept = delete;
    Veil& operator=(const Veil& _Other) = delete;
    Veil& operator=(Veil&& _Other) noexcept = delete;

    void SetColor(float4 _fColor) { mf4Color = _fColor; }
    float4 GetColor() { return mf4Color; }

    static void SetVeilEffect(VEIL_EFFECT _VeilEffect) 
    { 
        mqVeilEffectJobQueue.push(_VeilEffect);
    }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

};

