// CharactersLevel.h

#pragma once

#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class CharactersLevel : GameEngineLevel
{
public:
	// constrcuter destructer
	CharactersLevel();
	~CharactersLevel();

	// delete Function
	CharactersLevel(const CharactersLevel& _Other) = delete;
	CharactersLevel(CharactersLevel&& _Other) noexcept = delete;
	CharactersLevel& operator=(const CharactersLevel& _Other) = delete;
	CharactersLevel& operator=(CharactersLevel&& _Other) noexcept = delete;

protected:

private:

};

