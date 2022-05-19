// <hide/>

// Player.h

#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Player : public GameEngineActor
{
public:
    // constrcuter destructer
    Player();
    ~Player();

    // delete Function
    Player(const Player& _Other) = delete;
    Player(Player&& _Other) noexcept = delete;
    Player& operator=(const Player& _Other) = delete;
    Player& operator=(Player&& _Other) noexcept = delete;

protected:
    virtual void Start() override {}
    virtual void Update(float _DeltaTime) override {}
    virtual void End() override {}

private:
};