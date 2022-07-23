#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Temple0MonsterSpawn : public GameEngineActor
{
public:
	// constrcuter destructer
	Temple0MonsterSpawn();
	~Temple0MonsterSpawn();

	// delete Function
	Temple0MonsterSpawn(const Temple0MonsterSpawn& _Other) = delete;
	Temple0MonsterSpawn(Temple0MonsterSpawn&& _Other) noexcept = delete;
	Temple0MonsterSpawn& operator=(const Temple0MonsterSpawn& _Other) = delete;
	Temple0MonsterSpawn& operator=(Temple0MonsterSpawn&& _Other) noexcept = delete;

protected:

private:

};

