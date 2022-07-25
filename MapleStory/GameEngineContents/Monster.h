#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class Monster : public GameEngineActor
{
protected:
	GameEngineTextureRenderer* mpRenderer;
	float                      Speed;
	float                      mfHP;
	float                      mfMP;
	unsigned int               muMeso;
	unsigned int               muPhysicalAttack;
	unsigned int               muMagicalAttack;

public:
	// constrcuter destructer
	Monster();
	~Monster();

	// delete Function
	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;

	void BeAttacked(unsigned int _Damage)
	{
		mfHP -= _Damage;
	}

	GameEngineTextureRenderer* GetRenderer() { return mpRenderer; }

protected:

private:

};

