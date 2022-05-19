// <hide/>

// GameEngineLevel.h

#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineUpdateObject.h>
#include <list>
#include <map>

// 설명 :
class GameEngineActor;
class GameEngineLevel :
    public GameEngineNameObject,
    public GameEngineUpdateObject
{
    friend class GameEngineRenderer;
    friend class GameEngineCore; // 레벨이 현재까지 몇시간 동안 켜져 있었는지 시간을 잴 수 있게 함.

public:
    // constrcuter destructer
    GameEngineLevel();
    virtual ~GameEngineLevel() = 0;

    // delete Function
    GameEngineLevel(const GameEngineLevel& _Other) = delete;
    GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
    GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
    GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

protected:
    template<typename ActorType, typename GroupIndexType>
    GameEngineActor* CreateActor(GroupIndexType _ObjectGroupIndex)
    {
        return CreateActor<ActorType>(static_cast<int>(_ObjectGroupIndex));
    }

    template<typename ActorType>
    GameEngineActor* CreateActor(int _ObjectGroupIndex = 0)
    {
        GameEngineActor* NewActor = new ActorType();
        NewActor->SetLevel(this);
        NewActor->Start();

        // AllActors[_ObjectGroupIndex]게 사용하면
        // 없으면 만들어버리고 있으면
        // 찾아서 리턴해준다.
        std::list<GameEngineActor*>& Group = AllActors[_ObjectGroupIndex];

        Group.push_back(NewActor);

        return NewActor;
    }

private:
    std::map<int, std::list<GameEngineActor*>> AllActors;

    void ActorUpdate(float _DeltaTime);

private:
    std::map<int, std::list<class GameEngineRenderer*>> AllRenderer_;

    void PushRenderer(GameEngineRenderer* _Renderer);

    void Render(float _DeltaTime);

};

